#include<renderer.h>

renderer::renderer(const char* name, int width, int height): 
    m_win( SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0), &SDL_DestroyWindow),
    m_ren( SDL_CreateRenderer(m_win.get(), -1, 0), &SDL_DestroyRenderer),
    m_close(false),
    m_height(height),
    m_width(width)
    {}

renderer::~renderer() {
    SDL_Quit();
}

void renderer::render() {

    SDL_PollEvent(&m_event);
    SDL_SetRenderDrawColor(m_ren.get(), 0x1A, 0x1A, 0x1A, 0xFF);
    SDL_RenderClear(m_ren.get());

    SDL_RenderPresent(m_ren.get());

};

const bool renderer::should_close() const{
    return m_event.type == SDL_QUIT;
}