#include <renderer.h>

void renderee::render(){
    if(!should_render) return;
    set_rectangles();

    SDL_Renderer* sdl_rend = ren.get_renderer();
    for(auto& rect : m_rects){
        SDL_SetRenderDrawColor(sdl_rend, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(sdl_rend, rect.get());
    }
}

renderee::renderee(){}

renderee::renderee(float x, float y) : 
    m_pos{x, y}{}

renderee::~renderee(){}

renderee::renderee(color col) :  renderee() {
    this->c = {col.r, col.g, col.b, col.a};
}


renderee::renderee(float x, float y, color col) : renderee(x, y) {
    this->c = {col.r, col.g, col.b, col.a};
}

void renderee::set_rectangles() {}

renderee::renderee(renderee&& other){
    this->m_rects = std::move(other.m_rects);
    this->c = std::move(other.c);
}

void renderee::set_pos(float x, float y){
    m_pos = {x, y};
}

void interact::act(){}

void interact::set_renderer(renderer* rend){
    this->m_rend = rend;
}