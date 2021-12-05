#include <piece.h>
#include <random>
#include <thread>

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

void piece::act(){
    std::cout << "act thread: " << std::this_thread::get_id() << '\n';
    bool cont = true;
    uint32_t start = 0;
    SDL_Keycode prev;
    while(!end_game){
        if(m_rend->get_event().type == SDL_KEYDOWN && (cont || prev != m_rend->get_event().key.keysym.sym)){
            std::lock_guard<std::mutex> piece_lock(this->piece_mutex);
            start = SDL_GetTicks();

            //sstr << "pressed key\n";
            //dout.print(sstr);

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
    *this = tetros[0];

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
    this->piece_t = other.piece_t;

    return *this;
}
