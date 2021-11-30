#pragma once
#ifndef _BOARD_H__
#define _BOARD_H__
#include <renderer.h>

class board{
private:
protected:
public:
    enum class tile {
        empty, i, j, l, t, s, z
    };

    board();

    tile tiles[10][16] = {};

    bool place_piece(piece& p);
};

extern board playfield;

#endif