#pragma once
#ifndef __PIECE_DATA_H__
#define __PIECE_DATA_H__
#include <complex.h>
#include <stddef.h>

struct piece_data{
    vec2i pieces[4] = {};
    size_t type = 0;
};

#endif