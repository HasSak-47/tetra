#include <board.h>
#include <piece.h>

#include <chrono>
#include <random>
#include <future>

piece tetros[] = {
    {
        playfield, 
        -1, 1,
         0, 1,
         1, 1,
         2, 1,

         4, 14,
        0
    },

    {
        playfield, 
         0, 0,
         1, 0,
         0, 1,
         1, 1,

         4, 14,
        0
    },

    {
        playfield, 
        -1, 0,
         0, 0,
         1, 0,
         0, 1,

         4, 14,
        0
    },

    {
        playfield, 
        -1, 1,
         0, 1,
         1, 1,
         2, 1,
         4, 14,
        0
    },

        {
        playfield, 
        -1, 1,
         0, 1,
         1, 1,
         2, 1,
         4, 14,
        0
    },

        {
        playfield, 
        -1, 1,
         0, 1,
         1, 1,
         2, 1,
         4, 14,
        0
    },

        {
        playfield, 
        -1, 1,
         0, 1,
         1, 1,
         2, 1,
         4, 14,
        0
    }
};

static std::default_random_engine generator;
static std::uniform_int_distribution<size_t> distribution(0,6);

static std::future<size_t> next_piece;
static std::promise<size_t> next_p;

static piece& first = tetros[0];

static void generate_orders(size_t order[6]){
    for(size_t i = 0; i < 6; ++i){
        bool unique = true;
        do{
            order[i] = distribution(generator);
            for(size_t j = 0; j < i; ++j) if(order[i] == order[j]) unique = false;
        }while(!unique);
    }
}

std::mutex gen_mutex;

static size_t uses = 0;
static size_t current = 0;
static size_t order[6] = {};
void generate_piece_queue(){

    next_piece = next_p.get_future();

    generate_orders(order);
    while(!end_game){
        std::lock_guard<std::mutex> lock(gen_mutex);

        if(uses > 6){
            generate_orders(order);
            uses = 0;
        }

       next_p.set_value(order[uses]);
    }
}

size_t get_next(){
    std::lock_guard<std::mutex> lock(gen_mutex);
    uses++;

    return next_piece.get();
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
    padding{b.get_padding().x + b.get_padding().y}
{
    generator = std::minstd_rand0(std::chrono::system_clock::now().time_since_epoch().count());
    should_render = false;
}

piece::piece() : 
    m_board(first.m_board),
    renderee(0, 0, piece_color[first.piece_t]),
    board_pos(first.board_pos),
    pieces(first.pieces),
    padding{first.padding.x, first.padding.y} {
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
    std::lock_guard<std::mutex> piece_lock(this->piece_mutex);
    if(m_board.evaluate_next(*this)){
        board_pos.y--;
    }
    else{
        *this = tetros[0];
    }

}

void piece::move_side(side s) {

}

void piece::drop() {

}

void piece::set_padding(){
    this->padding = m_board.get_padding();
}