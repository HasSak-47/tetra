#include <cmath>

#include <board.h>
#include <piece.h>

#include <iostream>

placed parts[] {
    piece_color[0],
    piece_color[1],
    piece_color[2],
    piece_color[3],
    piece_color[4],
    piece_color[5],
    piece_color[6]
};

board::board(){}

board::board(float x, float y, int w, int h) :
    rect(x, y, w, h, color{0x20, 0x20, 0x28, 0xff}) {}

board::~board(){}

void board::set_rectangles(){
    auto unit = ren.get_unit();

    for(size_t i = 0; i < 7; ++i){
        parts[i].m_rects.clear();
    }

    for(size_t i = 0; i < 10; ++i)
    for(size_t j = 0; j < 16; ++j){
        if(tiles[i][j] == tile::empty) continue;
        size_t id = static_cast<size_t>(tiles[i][j]) - 1;

        std::unique_ptr<SDL_Rect> rc(new SDL_Rect {
            padding.x + (unit.x * (int)i),
            padding.y + (unit.y * (15 - (int)j)),
            unit.x,
            unit.y
        });

        parts[id].m_rects.push_back( std::move(rc) );
    }
}

placed::placed(color c) : renderee(c){

}

void placed::set_rectangles(){
    if(m_rects.size() == 0) return;
}