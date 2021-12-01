#include <piece.h>
#include <random>
#include <thread>

int piece::speed = 250;

color piece_color[] = {
    {0x55, 0x55, 0xff},
    {0x55, 0xff, 0x55},
    {0xff, 0xff, 0xff},
    {0xff, 0x55, 0x55},
    {0xff, 0x55, 0xff},
    {0xff, 0xff, 0x55},
    {0xff, 0xff, 0xff}
};

void piece::act(){
    bool acted = false;
    while(!end_game){
        {
            std::lock_guard<std::mutex> lock(this->piece_mutex);
            this->event = ren.get_event().key;

            if(this->event.type == SDL_KEYUP) continue;

            switch (this->event.keysym.sym){
            case SDLK_DOWN:
                move_down();
                acted = true;
                break;

            case SDLK_SPACE:
                drop();
                acted = true;
                break;
            case SDLK_LEFT:
                move_side(side::left);
                acted = true;
            case SDLK_UP:
                rotate();
                acted = true;
                break;
            default:
                break;
            }

        }   
        if(acted) std::this_thread::sleep_for(std::chrono::milliseconds(this->speed / 4));

    }
}

void piece::loop(){
    set_padding();
    *this = tetros[0];

    uint32_t start = SDL_GetTicks(), end = SDL_GetTicks();

    while(!end_game){
        {
            std::unique_lock<std::mutex> ren_lock(ren.render_mutex);
            ren.ended_render.wait(ren_lock, []{return !ren.rendering || end_game;});
            end = SDL_GetTicks();
            if(end - start < speed) continue;
            start = end;

            ren_lock.unlock();
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

    this->board_pos = other.board_pos;
    this->piece_t = other.piece_t;

    return *this;
}
