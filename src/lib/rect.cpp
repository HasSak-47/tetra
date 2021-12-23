#include <rect.h>

rect::rect() : 
    rect(0,0,0,0, {0x00, 0x00, 0x00, 0x00}){
}

rect::rect(float x, float y, int w, int h, color col) :
    renderee(x, y, col), size{w, h}, padding(ren.get_unit_dimentions()) {
    vec2i dem = ren.get_dimentions();
    vec2i unit = ren.get_unit(); 
    //all of this math is to set the center of the rectangle in 0.0f, 0.0f
    //and then move it to the position x, y
    padding.x -= this->size.x;
    padding.y -= this->size.y;

    padding.x /= 2;
    padding.y /= 2;

    padding.x *= unit.x;
    padding.y *= unit.y;

    padding.x += (m_pos.x * (dem.x / 2));
    padding.y += ((-m_pos.y) * (dem.y / 2));
    
    int width = size.x * unit.x;
    int height = size.y * unit.y;

    std::unique_ptr<SDL_Rect> rec(new SDL_Rect {padding.x, padding.y, width, height});
    this->m_rects.push_back(std::move(rec));
}

rect::~rect(){}
void rect::set_rectangles(){}

vec2i rect::get_padding(){
    return padding;
}