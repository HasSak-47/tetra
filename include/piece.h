#pragma once
#ifndef __PIECE_H__
#define __PIECE_H__
#include <renderer.h>

class piece : public renderee, public interact{
protected:
    void set_rectangles() override;
    void set_padding();

    vec2i pieces[4] = {};
    size_t type = 0;

    vec2i board_pos = {4, 15};
    vec2i padding = {};
    complexf axis = {};
    board& parent_board;

public:
    void act() override;

    enum class side{
        left = -1, right = 1
    };

    std::mutex piece_mutex;
    static int speed;

    piece();
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

#endif