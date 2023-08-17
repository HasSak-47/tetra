#include <cmath>

#include <board.h>
#include <piece.h>

#include <iostream>

//since a renderee can only use a color I set one part for each color
//each part is a color of the board that isn't the background
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

void board::set_rectangles(){
    vec2i unit = ren.get_unit();
    
    //clears all the set values
    for(size_t i = 0; i < 7; ++i){
        parts[i].m_rects.clear();
    }

    //pushes all rectangles to the appropiate class
    for(size_t i = 0; i < 10; ++i)
    for(size_t j = 0; j < 16; ++j){
        if(tiles[i][j] == tile::empty) continue;
        //determines what color it should be
        size_t id = static_cast<size_t>(tiles[i][j]) - 1;

        //creates the pointer to the data
        std::unique_ptr<SDL_Rect> rc(new SDL_Rect {
            padding.x + (unit.x * (int)i),
            padding.y + (unit.y * (15 - (int)j)),
            unit.x,
            unit.y
        });

        //pushes the rectangle to the appropiate color 
        parts[id].m_rects.push_back( std::move(rc) );
    }
}

board::tile& board::operator[](vec2i coords){
    return tiles[coords.x][coords.y];
}

//the placed rectangles are not set by itself but by the board
void placed::set_rectangles(){}
