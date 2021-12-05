#include <board.h>
#include <piece.h>

#include <chrono>
#include <random>
#include <future>

const piece tetros[] = {{
        playfield, // I shape
        -1, 1,
         0, 1,
         1, 1,
         2, 1,

         4, 14,
        0
    },{
        playfield, // o shape
         0, 0,
         1, 0,
         0, 1,
         1, 1,

         3, 14,
        1
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

static std::default_random_engine generator;
static std::uniform_int_distribution<size_t> distribution(0,6);

static void generate_orders(size_t order[6]){
    for(size_t i = 0; i < 6; ++i){
        bool unique = true;
        do{
            unique = true;
            order[i] = distribution(generator);
            for(size_t j = 0; j < i; ++j){
                if(order[i] == order[j]) {
                    unique = false;
                    break;
                }
            } 
            if(!unique) continue;
        }while(!unique);
    }
}

std::mutex gen_mutex;

static size_t uses = 0;
static size_t order[7] = {};

void generate_piece_queue(){
    generate_orders(order);
    while(!end_game){
        std::lock_guard<std::mutex> lock(gen_mutex);

        if(uses > 7){
            generate_orders(order);
            uses = 0;
        }
        else continue;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

size_t get_next(){
    std::lock_guard<std::mutex> lock(gen_mutex);
    return order[uses++];
}

piece::piece(
    board& b,
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    int x4, int y4,

    int cx, int cy,

    size_t type
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
    piece_t(type)
{
    should_render = false;
}

piece::piece() : 
    m_board(tetros[0].m_board),
    renderee(0, 0, piece_color[tetros[0].piece_t]),
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
            tiles[pos.x][pos.y] = static_cast<tile>(p.piece_t + 1) ;
        }
    }

    return free;
}

void piece::rotate() {

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
        //std::cout << "colition : " << pos.x << " : " <<  (((s == side::left)? 0 : 15)) << " : " << (m_board.tiles[pc.x + (int)s][pc.y] != board::tile::empty) << '\n';
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