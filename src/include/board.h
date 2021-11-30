#pragma once
#ifndef _BOARD_H__
#define _BOARD_H__
#include <renderer.h>
#include <rect.h>

class board : public rect{
protected:
    void place_piece(piece& p);
public:
    enum class tile {
        empty, i, j, l, t, s, z
    };

    board();
    board(float x, float y, int w, int h);
    ~board();

    tile tiles[10][16] = {};

    bool evaluate_next(piece& p);
    friend class renderer;
};

extern board playfield;

#endif