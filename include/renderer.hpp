#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <cstdint>
#include <iostream>
#include <thread>
#include <vector>

#include <SDL_rect.h>
#include <SDL_render.h>
#include "vector.hpp"

class Window{
private:
    SDL_Window* _win;
    SDL_Renderer* _ren;
    int width;
    int height;
public:
    Window(int width = 800, int height = 600): width(width), height(height){
        this->_win= SDL_CreateWindow("tetris", 0, 0, width, height, 0);
        this->_ren= SDL_CreateRenderer(this->_win, 0, 0);
    }

    int get_height(){return this->height;}
    int get_width() {return this->width;}

    SDL_Renderer* get_renderer(){ return this->_ren; }
    SDL_Window* get_window(){ return this->_win; }
};

class Renderer{
protected:
    Window& _render_target;
public:
    Renderer(Window& win) : _render_target(win){}

    void present () {
        auto renderer = this->_render_target.get_renderer();
        SDL_RenderPresent(this->_render_target.get_renderer());
    }

    void set_color(Vector4<uint8_t> color){
        auto renderer = this->_render_target.get_renderer();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }

    void set_color(uint8_t r, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255){
        auto renderer = this->_render_target.get_renderer();
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }
};

enum Type{
    None = 0b000,
    Text = 0b001,
    Rect = 0b010,
    Bord = 0b100
};

class GridElement;
class GridRenderer;
class GridWriter{
public:
    virtual void write(GridRenderer& ) = 0;
};

class GridElement{
public:
    SDL_Rect _rect;
    Vector4<uint8_t> _fg_color;
    Vector4<uint8_t> _bg_color;

    char32_t character = ' ';
    Type t = Type::None;
};

class GridRender : public Renderer{
private: 
    static SDL_Texture CHARACTERS[256];


    Vector2<int> _size    = {60, 60}; // the size of the grid element
    Vector2<int> _count   = {10, 10}; // the amount of grid elements
    Vector2<int> _offset  = {0, 0};
    size_t _pos = 0;

    std::vector<GridElement> _buffer;
public:
    GridRender(
            Window& win,
            int x = 0, int y = 0,
            int w = 1, int h = 1,
            int xcount = 1, int ycount = 1
        ):
        Renderer(win),
        _offset(Vector2<int>{x, y}),
        _count(Vector2<int>{xcount, ycount})
    { }

    ~GridRender(){}
    Vector2<int> get_grid_size() { return this->_size; }
    void write(){}
};

#endif
