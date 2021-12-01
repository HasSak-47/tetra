#pragma once
#ifndef _BOARD_H__
#define _BOARD_H__
#include <renderer.h>
#include <rect.h>

class board : public rect{
protected:
    void place_piece(piece& p);
    void set_rectangles() override;
public:
    enum class tile {
        empty, i, o, j, l, t, s, z
    };

    board();
    board(float x, float y, int w, int h);
    ~board();

    tile tiles[10][16] = {};

    bool evaluate_next(piece& p);
    friend class renderer;
};

class placed : public renderee{
protected:
    void set_rectangles() override;
public:
    placed(color c);

    friend class board;
};

extern placed parts[];
extern board playfield;

#endif