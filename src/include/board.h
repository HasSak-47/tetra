#pragma once
#ifndef _BOARD_H__
#define _BOARD_H__
#include <renderer.h>
#include <vector>

class Board{
public:
    //each states corresponds to a piece and n means empty
    enum states{ n = 0, l, s, z, t, j, i };
private: 
    states m_board[10][16] = {};

    void place(const piece& p);

public:
    bool evaluate(const piece& p);

    unsigned score = 0;
    void save_score();

    std::vector<unsigned> get_scoreboard();

    states* operator[](size_t index);
    states* operator[](int index);
};
#endif