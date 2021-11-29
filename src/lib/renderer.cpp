#include <renderer.h>
#include <piece.h>

bool board[10][16] = {};
bool end_game = false;

renderer::renderer() : m_win(nullptr, &SDL_DestroyWindow), m_ren(nullptr, &SDL_DestroyRenderer){}

renderer::renderer(const char* name, int width, int height): 
    m_win( SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0), &SDL_DestroyWindow),
    m_ren( SDL_CreateRenderer(m_win.get(), -1, 0), &SDL_DestroyRenderer),
    m_close(false),
    m_dimention{width, height}{

    std::cout << "height in units: " << (height / unit) << '\n';
    std::cout << "width in units: " << (width / unit) << '\n';

    m_pad.x = ((width / unit) - 10) / 2;
    m_pad.y = ((height / unit) - 16) / 2;
}

renderer::~renderer() {
    SDL_Quit();
}

renderer::renderer(renderer&& other) :
    m_win(std::move(other.m_win)),
    m_ren(std::move(other.m_ren)),
    m_close(other.m_close),
    m_dimention (other.m_dimention),
    m_event(std::move(other.m_event))
    {}

renderer& renderer::operator=(renderer&& other) {
    if(this == &other) return *this;

    m_win    = ( std::move(other.m_win) );
    m_ren    = ( std::move(other.m_ren) );
    m_close  = ( std::move(other.m_close) );
    m_event  = ( std::move(other.m_event) );

    m_dimention = other.m_dimention;

    return *this;
}

uint32_t renderer::render() {
    start = SDL_GetTicks();

    SDL_PollEvent(&m_event);
    SDL_SetRenderDrawColor(m_ren.get(), 0x1a, 0x1a, 0x1a, 0x88);
    SDL_RenderClear(m_ren.get());

    if(m_event.type == SDL_QUIT) end_game = true;

    SDL_Rect block = {m_pad.x * unit, m_pad.y * unit, unit * 10, unit * 16};
    SDL_SetRenderDrawColor(m_ren.get(), 0x0a, 0x0a, 0x0a, 0xff);
    SDL_RenderFillRect(m_ren.get(), &block);

    SDL_SetRenderDrawColor(m_ren.get(), falling.c.r, falling.c.g, falling.c.b, falling.c.a);
    block.h = unit, block.w = unit;
    for(auto& square : falling.pieces){
        block.x = unit * (falling.center.x + square.x + m_pad.x);
        block.y = unit * ((15 - falling.center.y) + square.y + m_pad.y);
        SDL_RenderFillRect(m_ren.get(), &block);
    }

    SDL_SetRenderDrawColor(m_ren.get(), 0x99, 0x99, 0x99, 0x99);
    block.h = unit, block.w = unit;
    for(size_t i = 0; i < 10; ++i)
    for(size_t j = 0; j < 16; ++j){
        if(!board[i][j]) continue;
        block.x = unit * (+i + m_pad.x);        
        block.y = unit * (15 - j + m_pad.y);
        SDL_RenderFillRect(m_ren.get(), &block);
    }

    SDL_RenderPresent(m_ren.get());

    end = SDL_GetTicks();
    return delta_time =  end - start;
};

const bool renderer::should_close() const{
    return m_event.type == SDL_QUIT;
}