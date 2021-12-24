#include <renderer.h>

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

renderee::renderee(renderee&& other){
    this->m_rects = std::move(other.m_rects);
    this->c = std::move(other.c);
}

void renderee::render(){
    if(!should_render) return;
    set_rectangles();

    SDL_Renderer* sdl_rend = ren.get_renderer();
    for(auto& rect : m_rects){ //for each rect it is set to draw
        SDL_SetRenderDrawColor(sdl_rend, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(sdl_rend, rect.get());
    }
}

void renderee::set_pos(float x, float y){
    m_pos = {x, y};
}

//this function is called by all the renderee instances and the render function isn't virtual
void renderee::set_rectangles() {}