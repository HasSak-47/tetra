#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <iostream>

#include <condition_variable>
#include <memory>
#include <vector>
#include <array>


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

    //height and with in units
    vec2i m_unit_dimention = {0,0};

    //how big a square is
    vec2i m_unit = {0, 0};

    uint32_t delta_time = 0;

public:
    std::condition_variable ended_render;
    std::mutex render_mutex;

    bool rendering = false;
    
    renderer();
    renderer(const char* name, int width, int height);
    ~renderer();

    renderer(renderer&& other);
    renderer& operator=(renderer&& other);

    //renderer& operator=(const renderer& other);
    renderer(const renderer& other) = delete;

    //it renders a frame and tells the time it took
    void render();
    //to measure when the frame got rendered, when it ended, and how much it took
    bool should_close();

    SDL_Event get_event();
    vec2i get_unit();
    vec2i get_dimentions();
    vec2i get_unit_dimentions();

    SDL_Renderer* get_renderer();

    //all the objects that will be rendered in the order
    std::vector<renderee*> renderees;
};

class renderee{
private:
    void render();
protected:
    std::vector<SDL_Rect> m_rects;
    virtual void set_rectangles();
    color c = {};

    bool should_render = true;

public:

    ~renderee();
    renderee();

    renderee(renderee&& other);
    renderee(renderee& other) = delete;

    renderee& operator=(renderee&& other);

    renderee(std::vector<SDL_Rect> rects);
    renderee(std::vector<SDL_Rect> rects, color col);
    renderee(color col);

    friend class renderer;
};

class interact{
protected:
    SDL_KeyboardEvent event;
public:
};

extern renderer ren;
extern bool end_game;

#endif