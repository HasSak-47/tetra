#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <iostream>

#include <condition_variable>
#include <future>
#include <memory>
#include <vector>

#include <SDL.h>

#include <unique_vector.h>
#include <complex.h>

struct color{
    uint8_t r = 0, g = 0, b = 0, a = 255;
};

//the class that will render and create windows
class renderer;
//classes that will be rendered whenever renderer renders something
class renderee;
//classes that will act on polled events
class interact;

class board;
class piece;
class rect;

class renderer{
private:
    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> m_win;
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> m_ren;
    std::promise<bool> promise_end;
    SDL_Event m_event = {};

    bool m_close = false;

    //height and width
    vec2i m_dimention = {0,0};

    //height and with in units
    vec2i m_unit_dimention = {0,0};

    //how big a square is
    vec2i m_unit = {0, 0};

    uint32_t delta_time = 0;
public:
    std::future<bool> ended;
    std::condition_variable ended_render;
    std::mutex render_mutex;

    bool rendering = true;
    
    renderer();
    renderer(const char* name, int width, int height);
    ~renderer();

    renderer(renderer&& other);
    renderer& operator=(renderer&& other);

    renderer(const renderer& other) = delete;

    void render();
    bool should_close();

    SDL_Event get_event();
    vec2i get_unit();
    vec2i get_dimentions();
    vec2i get_unit_dimentions();

    SDL_Renderer* get_renderer();

    //all the objects that will be rendered in the order
    std::vector<renderee*> renderees;

    void wait_for_render();
};

class renderee{
private:
    void render();
protected:
    unique_vector<SDL_Rect> m_rects;
    virtual void set_rectangles();
    color c = {};
    vec2f m_pos = {};

public:
    bool should_render = true;

    ~renderee();
    renderee();
    renderee(color col);
    renderee(float x, float y);
    renderee(float x, float y, color col);
    renderee(unique_vector<SDL_Rect> rects);
    renderee(unique_vector<SDL_Rect> rects, color col);

    renderee(renderee&& other);
    renderee(renderee& other) = delete;
    renderee& operator=(renderee&& other);

    void set_pos(float x, float y);

    friend class renderer;
};


class interact{
protected:
    renderer* m_rend;
public:
    void set_renderer(renderer* rend);

    virtual void act();
};

extern renderer ren;
extern bool end_game;
extern color piece_color[];
extern unsigned score;

#endif