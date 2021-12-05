#include <board.h>
#include <piece.h>

#include <chrono>
#include <random>
#include <future>
#include <fstream>
#include <algorithm>

#include <cmath>

const piece tetros[] = {{
        playfield, // I shape
        -1, 1,
         0, 1,
         1, 1,
         2, 1,
         4, 14,
        0,
        -0.5f, -0.5f
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
    board_pos{cx, cy},
    pieces{ 
        {x1, y1},
        {x2, y2},
        {x3, y3},
        {x4, y4},
    },
    padding(b.get_padding()),
    m_color(type),
    axis{ax, ay}
{
    should_render = false;
}

piece::piece(board& b, std::string path) : 
    m_board(b){
    std::ifstream in_file(path);
    
}

piece::piece() : 
    m_board(tetros[0].m_board),
    renderee(0, 0, piece_color[tetros[0].m_color]),
    board_pos(tetros[0].board_pos),
    pieces(tetros[0].pieces),
    padding(tetros[0].padding) {
    should_render = true;
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
        for(auto& pc : p.pieces){
            vec2i pos = {p.board_pos.x + pc.x, p.board_pos.y + pc.y};
            tiles[pos.x][pos.y] = static_cast<tile>(p.m_color + 1) ;
        }
    }

    

    return free;
}

static const complexf rotator = {0, -1};



void piece::rotate() {
    if(this->m_color == 1) return; 

    piece copy = *this;

    vec2i max = {}, min = {};
    for(auto& pc : pieces){
        complexf data = complexf(pc.x,pc.y) + axis;
        data *= rotator;
        data.x = ceil(data.x); data.y = ceil(data.y);

        pc = {(int)data.x, (int)data.y};

        if(pc.x + board_pos.x> max.x) max.x = pc.x + board_pos.x; 
        else if(pc.x + board_pos.x < min.x) min.x = pc.x + board_pos.x;

        if(pc.y > max.y + board_pos.y) max.y = pc.y + board_pos.y; 
        else if(pc.y < min.y + board_pos.y) min.y = pc.y + board_pos.y; 
    }
    if(max.x > 9) board_pos.x -= max.x - 9;
    if(min.x < 0) board_pos.x -= min.x;

    if(max.y > 15) board_pos.y -= max.y - 15;
    if(min.y < 0) board_pos.y -= min.y;

    /*
    for(auto& pc : pieces){
        vec2i pos = {pc.x + board_pos.x, pc.y + board_pos.y};

        if(this->m_board.tiles[pos.x][pos.y] != board::tile::empty){

        }
    }
    */
}

void piece::move_down() {
    if(m_board.evaluate_next(*this)){
        board_pos.y--;
    }
    else{
        *this = tetros[get_next()];
        if(m_board.tiles[4][15] != board::tile::empty) 
            end_game = true;
    }

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

void board::set_rectangles(){
    auto unit = ren.get_unit();

    for(size_t i = 0; i < 7; ++i){
        parts[i].m_rects.clear();
    }

    for(size_t i = 0; i < 10; ++i)
    for(size_t j = 0; j < 16; ++j){
        if(tiles[i][j] == tile::empty) continue;
        size_t id = static_cast<size_t>(tiles[i][j]) - 1;

        std::unique_ptr<SDL_Rect> rc(new SDL_Rect {
            padding.x + (unit.x * (int)i),
            padding.y + (unit.y * (15 - (int)j)),
            unit.x,
            unit.y
        });

        parts[id].m_rects.push_back( std::move(rc) );
    }
}