#include <renderer.h>

std::vector<renderee*> renderee::renderees;

void renderee::render(){
    SDL_Renderer* sdl_rend = ren.get_renderer();
    for(auto& rect : m_rects){
        SDL_SetRenderDrawColor(sdl_rend, c.r, c.g, c.b, c.a);
        SDL_RenderFillRect(sdl_rend, &rect);
    }
}

renderee::renderee(){
    renderees.push_back(this);
}

renderee::~renderee(){}


renderee::renderee(std::vector<SDL_Rect> rects) : renderee(){
    this->m_rects = std::move(rects);
    
}

renderee::renderee(color col) :  renderee() {
}

renderee::renderee(std::vector<SDL_Rect> rects, color col) {
    this->c = {col.r, col.g, col.b, col.a};
    this->m_rects = std::move(rects);

}


void renderee::set_rectangles(){}


renderee::renderee(renderee&& other){
    this->m_rects = std::move(other.m_rects);

    this->c = std::move(other.c);
}

renderee& renderee::operator=(renderee&& other){
    if(this == &other) return *this;

   this->m_rects = std::move(other.m_rects);

    this->c = std::move(other.c);

    return *this;
}