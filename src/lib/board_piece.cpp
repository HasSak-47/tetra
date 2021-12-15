#include <board.h>
#include <piece.h>

#include <chrono>
#include <random>
#include <future>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <cmath>

const piece tetros[] = {{
        playfield, // I shape
        "../data/piece/I_piece"
    },{
        playfield, // o shape
         0, 0,
         1, 0,
         0, 1,
         1, 1,
         3, 14,
        1,
         -0.5f, -0.5f
    },{
        playfield, //s shape
        -1, 0,
         0, 0,
         0, 1,
         1, 1,
         4, 14,
        2
    },{
        playfield, //z shape
        -1, 1,
         0, 0,
         0, 1,
         1, 0,
         4, 14,
        3
    },{
        playfield,  //j shape
        -1, 0,
         0, 0,
         0, 1,
         0, 2,
         4, 13,
        4
    },{
        playfield, //l shape
         0, 0,
         0, 1,
         0, 2,
         1, 0,
         4, 13,
        5
    },{
        playfield, //t shape
         0, 0,
         1, 0,
         2, 0,
         1, 1,
         4, 14,
        6
    }
};

piece::piece(
    board& b,
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    int x4, int y4,

    int cx, int cy,

    size_t type,
    float ax, float ay
) : 
    m_board(b),
    renderee(0, 0, piece_color[type]),
    piece_data {
        vec2i(x1, y1),
        vec2i(x2, y2),
        vec2i(x3, y3),
        vec2i(x4, y4),
        type
    },
    board_pos{cx, cy},
    padding(b.get_padding()),
    axis{ax, ay}
{
    should_render = false;
}

piece::piece(board& b, std::string path) : 
    m_board(b),
    renderee(0, 0){
    std::ifstream in_file(path);

    std::stringstream lines[7] = {};
    size_t index = 0;
    for(size_t i = 0; i < 10; ++i){
        std::string line = {};
        getline(in_file, line);
        if(line.size() == 0) continue;
        lines[index++] << line;
    }

    for(size_t i = 0; i < 4; ++i){
        lines[i] >> pieces[i].x >> pieces[i].y;
    }

    lines[4] >> board_pos.x >> board_pos.y;
    lines[5] >> type;
    c = piece_color[type];

    lines[6] >> axis.x >> axis.y;
    should_render = false;
}

bool board::evaluate_next(piece& p){
    bool free = true;
    for(auto& pc : p.pieces){
        vec2i pos = {p.board_pos.x + pc.x, p.board_pos.y + pc.y};
        if(tiles[pos.x][pos.y - 1] != tile::empty || pos.y == 0) {
            free = false;
            break;
        }
    }

    if(!free){
        score += p.board_pos.y + 1;
        for(auto& pc : p.pieces){
            vec2i pos = {p.board_pos.x + pc.x, p.board_pos.y + pc.y};
            tiles[pos.x][pos.y] = static_cast<tile>(p.type + 1) ;
        }


        size_t cleared_lines = 0;
        std::vector<size_t> lines_to_delete;
        for(size_t j = 0; j < 16; ++j){
            bool complete = true;
            for(size_t i = 0; i < 10; ++i){
                if(tiles[i][j] == tile::empty){
                    complete = false;
                    break;
                }
            }

            if(complete) {
                lines_to_delete.push_back(j);
                cleared_lines++;
            }
        }
        if(cleared_lines > 0) {
            score += ((cleared_lines * cleared_lines + 1) / 2) * 100;
            std::reverse(lines_to_delete.begin(), lines_to_delete.end());

            size_t line = 0;
            tile tiles_copy[10][16] = {};
            for(size_t i = 0; i < 16; ++i){
                if(i == lines_to_delete.back()) {
                    lines_to_delete.pop_back();
                    continue;
                }
                for(size_t j = 0; j < 10; ++j)
                    tiles_copy[j][line] = tiles[j][i];

                line++;
            }

            for(size_t i = 0; i < 10; ++i) {
                for(size_t j = 0; j < 16; ++j){
                    tiles[i][j] = tiles_copy[i][j];
                }
            }
        }
    }

    return free;
}

static const complexf rotator = {0, -1};
void piece::rotate() {
    if(this->type == 1) return; 

    vec2i max = {}, min = {};
    vec2i rot_pieces[4] = {};
    
    for(size_t i = 0; i < 4; ++i)
        rot_pieces[i] = this->pieces[i];

    vec2i new_center = board_pos;

    for(auto& pc : rot_pieces){
        complexf data = complexf(pc.x,pc.y) + axis;
        data *= rotator;
        data.x = ceil(data.x); data.y = ceil(data.y);

        pc = {(int)data.x, (int)data.y};

        if(pc.x + new_center.x > max.x) max.x = pc.x + new_center.x; 
        else if(pc.x + new_center.x < min.x) min.x = pc.x + new_center.x;

        if(pc.y + new_center.y > max.y) max.y = pc.y + new_center.y; 
        else if(pc.y < min.y + new_center.y) min.y = pc.y + new_center.y; 
    }

    if(max.x > 9) new_center.x -= max.x - 9;
    else if(min.x < 0) new_center.x -= min.x;

    if(max.y > 15) new_center.y -= max.y - 15;
    else if(min.y < 0) new_center.y -= min.y;

    for(vec2i& pc : rot_pieces){
        vec2i pos = {pc.x + new_center.x, pc.y + new_center.y};
        if(m_board.tiles[pos.x][pos.y] != board::tile::empty)
            return;
    }

    board_pos = new_center;
    for(size_t i = 0; i < 4; ++i){
        this->pieces[i] = rot_pieces[i];
    }
}

void piece::move_down() {
    if(m_board.evaluate_next(*this))
        --board_pos.y;
    else
        *this = tetros[get_next()];

}

void piece::move_side(side s) {
    bool colition = false;
    for(auto& pc : pieces){
        vec2i pos = {pc.x + board_pos.x, pc.y + board_pos.y};
        if(pos.x == ((s == side::left)? 0 : 9) || m_board.tiles[pos.x + (int)s][pos.y] != board::tile::empty){
            colition = true;
            break;
        }
    }
    if(colition) return;
    this->board_pos.x += (int)s;
}

void piece::drop() {

}

void piece::set_padding(){
    this->padding = m_board.get_padding();
}
