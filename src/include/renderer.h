#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL.h>
#include <memory>
#include <iostream>
#include <complex.h>

class renderer;
class piece;

struct color{
    uint8_t r = 0, g = 0, b = 0, a = 0;
};

class renderer{
private:
    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> m_win;
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> m_ren;
    SDL_Event m_event;

    bool m_close;
    vec2i m_dimention;
    vec2i m_pad;

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
    uint32_t start, end, delta_time;
    const bool should_close() const;

    SDL_Keycode get_key();
};

extern bool end_game;
extern bool board[10][16];
//extern renderer ren;

#endif