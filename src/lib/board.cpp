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

placed::placed(color c) : renderee(c){

}

void placed::set_rectangles(){
    if(m_rects.size() == 0) return;
}