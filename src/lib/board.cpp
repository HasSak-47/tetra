#include <cmath>

#include <board.h>
#include <piece.h>

#include <iostream>


board::board() {
    c = {0x10, 0x10, 0x10, 0xff};

    set_rectangles();
}

board::board(float x, float y, int w, int h) : 
    m_pos(x, y), m_units(w, h){
    c = {0x10, 0x10, 0x10, 0xff};

    set_rectangles();
}

board::~board(){}

void board::set_rectangles(){
    m_rects.clear();

    vec2i m_padding = ren.get_unit_dimentions();
    vec2i dem = ren.get_dimentions();
    vec2i unit = ren.get_unit();

    m_padding.x -= this->m_units.x;
    m_padding.y -= this->m_units.y;

    m_padding.x /= 2;
    m_padding.y /= 2;

    m_padding.x *= unit.x;
    m_padding.y *= unit.y;

    m_padding.x += (m_pos.x * (dem.x / 2));
    m_padding.y += ((-m_pos.y) * (dem.y / 2));


    SDL_Rect rec {m_padding.x, m_padding.y, m_units.x * unit.x, m_units.y * unit.y};
    m_rects.push_back(rec);
}