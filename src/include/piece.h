#pragma once
#ifndef __PIECE_H__
#define __PIECE_H__
#include <renderer.h>
#include <complex.h>

class piece : public renderee, protected interact{
protected:
    void set_rectangles() override;
    void act() override;

    vec2i board_pos = {4, 15};
    vec2i pieces[4] = {};
    vec2i padding = {};
    board& m_board;
public:
    enum class side{
        left = -1, right = 1
    };

    std::mutex piece_mutex;
    static int speed;

    piece() = delete;

    piece(
        board& b,
        int x1, int y1,
        int x2, int y2,
        int x3, int y3,
        int x4, int y4,

        int cx, int cy,

        color col
    );

    piece(const piece& other);
    piece(piece&& other);

    piece& operator=(const piece& other);
    piece& operator=(piece&& other);

    void rotate();
    void loop();
    void move_down();
    void move_side(side s);
    void drop();
};

extern piece falling;
extern piece next;
extern piece saved;
extern const piece tetros[];

#endif