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

renderee::renderee(){
    std::cout << "default renderee constructor\n";
}

renderee::renderee(float x, float y) : 
    m_pos{x, y}{
    std::cout << "float x, float y, renderee constructor\n";
}

renderee::~renderee(){
    std::cout << "renderee destructor\n";
}


renderee::renderee(unique_vector<SDL_Rect> rects) : renderee(){
    std::cout << "std::vector<SDL_Rect> rects, renderee constructor\n";
    this->m_rects = move_unique_vector(rects);
    
}

renderee::renderee(color col) :  renderee() {
    std::cout << "color col, renderee constructor\n";
    this->c = {col.r, col.g, col.b, col.a};
}


renderee::renderee(float x, float y, color col) : renderee(x, y) {
    std::cout << "float x, float y, color col, renderee constructor\n";
    this->c = {col.r, col.g, col.b, col.a};
}

renderee::renderee(unique_vector<SDL_Rect> rects, color col) : renderee(){
    std::cout << "std::vector<SDL_Rect> rects, color col, renderee constructor\n";
    this->c = {col.r, col.g, col.b, col.a};
    this->m_rects = move_unique_vector(rects);
}


void renderee::set_rectangles() {}

renderee::renderee(renderee&& other){
    std::cout << "renderee move contructor";
    this->m_rects = std::move(other.m_rects);

    this->c = std::move(other.c);
}

renderee& renderee::operator=(renderee&& other){
    std::cout << "renderee move assign operator";
    if(this == &other) return *this;

   this->m_rects = std::move(other.m_rects);

    this->c = std::move(other.c);

    return *this;
}

void renderee::set_pos(float x, float y){
    m_pos = {x, y};
}

void interact::act(){}