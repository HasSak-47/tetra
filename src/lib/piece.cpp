#include <piece.h>
#include <random>
#include <thread>
#include <ctime>

int piece::speed = 250;

color piece_color[] = {
    {0x55, 0x55, 0xff}, //blue
    {0x55, 0xff, 0x55}, //green
    {0x55, 0xff, 0xff}, //cyan
    {0xff, 0x55, 0x55}, //red
    {0xff, 0x55, 0xff}, //purple
    {0xff, 0xff, 0x55}, //yellow
    {0xff, 0xff, 0xff}  //white
};

std::mutex gen_mutex;

static size_t uses = 0;
static size_t order[7] = {};

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

void generate_piece_queue(){
    generate_orders(order);
    generator = std::minstd_rand0(static_cast<unsigned long>(time(0)));
    while(!end_game){
        std::lock_guard<std::mutex> lock(gen_mutex);

        if(uses > 6){
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

void piece::act(){
    std::cout << "act thread: " << std::this_thread::get_id() << '\n';
    bool cont = true;
    uint32_t start = 0;
    SDL_Keycode prev;
    while(!end_game){
        if(m_rend->get_event().type == SDL_KEYDOWN && (cont || prev != m_rend->get_event().key.keysym.sym)){
            std::lock_guard<std::mutex> piece_lock(this->piece_mutex);
            start = SDL_GetTicks();

            prev = m_rend->get_event().key.keysym.sym;
            switch (m_rend->get_event().key.keysym.sym){
            case SDLK_DOWN:
                move_down();
                break;

            case SDLK_SPACE:
                drop();
                break;
            case SDLK_LEFT:
                move_side(side::left);
                break;
            case SDLK_RIGHT:
                move_side(side::right);
                break;
            case SDLK_UP:
                rotate();
                break;
            default:
                break;
            }

            cont = false;
        }
        else 
        if(m_rend->get_event().type == SDL_KEYUP){
            cont = true;
        }
    }
}

void piece::loop(){
    set_padding();
    *this = tetros[get_next()];

    uint32_t start = SDL_GetTicks(), end = SDL_GetTicks();

    std::cout << "loop thread: " << std::this_thread::get_id() << '\n';

    while(!end_game){
        {
            this->m_rend->wait_for_render();
            end = SDL_GetTicks();
            if(end - start < speed) continue;
            start = end;

            std::lock_guard<std::mutex> piece_lock(this->piece_mutex);
            move_down();
        }
        std::unique_lock<std::mutex> ren_lock(ren.render_mutex);
        ren.ended_render.wait(ren_lock, []{return ren.rendering || end_game;});
        ren_lock.unlock();
    }

    std::cout << "ended falling loop\n";
}

void piece::set_rectangles(){
    auto unit = ren.get_unit();

    this->m_rects.clear();

    std::unique_ptr<SDL_Rect> ptr;
    for(auto& p : pieces){
        vec2i pos = {
            padding.x + unit.x * (board_pos.x + p.x),
            padding.y + unit.y * ( 15 - (board_pos.y + p.y) )
        };

        ptr = std::unique_ptr<SDL_Rect>(new SDL_Rect {pos.x, pos.y, unit.x, unit.y});
        this->m_rects.push_back(std::move(ptr));
    }
}

piece& piece::operator=(const piece& other){
    if(this == &other) return *this;

    for(size_t i = 0; i < 4; ++i){
        this->pieces[i] = other.pieces[i];
    }
    this->c.r = other.c.r;
    this->c.g = other.c.g;
    this->c.b = other.c.b;
    this->c.a = other.c.a;

    this->board_pos = other.board_pos;
    this->type = other.type;
    this->axis = other.axis;

    return *this;
}

piece::piece() : 
    m_board(tetros[0].m_board),
    renderee(0, 0, piece_color[tetros[0].type]),
    board_pos(),
    piece_data(),
    padding() {
    should_render = true;
}

piece::piece(const piece& other) : 
    m_board(other.m_board){
    *this = other;
}
