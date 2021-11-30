#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL.h>
#include <memory>
#include <array>
#include <iostream>
#include <complex.h>

class renderer;
class Board;
class piece;

struct color{
    uint8_t r = 0, g = 0, b = 0, a = 255;
};

extern std::array<const color* const, 6> colors;

class renderer{
private:
    //pointer to the window of the renderer
    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> m_win;

    //pointer to the renderer
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> m_ren;

    //last event polled
    SDL_Event m_event = {};

    //should the window close
    bool m_close = false;

    //height and width
    vec2i m_dimention = {0,0};

    //the padding to center the tetris board
    vec2i m_pad = {0,0};

    //how big a square is
    const int unit = 30;

protected:
public:
    renderer();
    renderer(const char* name, int width, int height);
    ~renderer();

    renderer(const renderer& other) = delete;
    renderer(renderer&& other);

    //renderer& operator=(const renderer& other);
    renderer& operator=(renderer&& other);

    uint32_t render();
    //to measure when the frame got rendered, when it ended, and how much it took
    uint32_t start, end, delta_time;
    const bool should_close() const;

    const SDL_Event get_event();
};

extern bool end_game;
extern Board board;
//extern renderer ren;

#endif