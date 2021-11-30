#include <cmath>

#include <board.h>
#include <piece.h>

#include <iostream>

board::board(){}

board::board(float x, float y, int w, int h) :
    rect(x, y, w, h, color{0xA0, 0xA0, 0xA8, 0xff}) {}

board::~board(){}
