#pragma once
#ifndef __PIECE_H__
#define __PIECE_H__
#include <renderer.h>
#include <piece_data.h>

class piece : public renderee, public interact, protected piece_data{
protected:
    void set_rectangles() override;
    void set_padding();

    vec2i board_pos = {4, 15};
    vec2i padding = {};
    board& m_board;
    complexf axis = {};

public:
    void act() override;

    enum class side{
        left = -1, right = 1
    };

    std::mutex piece_mutex;
    static int speed;

    piece();

    piece(
        board& b,
        int x1, int y1,
        int x2, int y2,
        int x3, int y3,
        int x4, int y4,

        int cx, int cy,
        size_t type,

        float ax = 0.0f, float ay = 0.0f
    );
    piece(board& b, std::string file_path);

    piece(const piece& other);
    piece(piece&& other);

    piece& operator=(const piece& other);

    void rotate();
    void loop();
    void move_down();
    void move_side(side s);
    void drop();

    friend class board;
};

void generate_piece_queue();
size_t get_next();

extern piece falling;
extern size_t next, saved;
extern const piece tetros[];

void set_pieces();
piece& get_saved();

#endif