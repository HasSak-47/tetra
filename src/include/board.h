#pragma once
#ifndef _BOARD_H__
#define _BOARD_H__
#include <renderer.h>

class board : public renderee{
private:
    void set_rectangles() override;
protected:
    vec2f m_pos = {};
    vec2i m_units = {};
public:
    enum class tile {
        empty, i, j, l, t, s, z
    };

    board();
    board(float x, float y, int w, int h);
    ~board();

    tile tiles[10][16] = {};

    bool place_piece(piece& p);
    friend class renderer;
};

extern board playfield;

#endif