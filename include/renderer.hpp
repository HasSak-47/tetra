#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

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

    virtual void present() = 0;
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

class GridRender;

class GridWriter{
    virtual void write(GridRender& renderer) = 0;
};

class GridElement : public GridWriter{
protected:
    SDL_Rect _rect;
public:
    Vector4<int> fg_color = {};
    Vector4<int> bg_color = {};

    char32_t character = ' ';
    Type t = Type::None;

    GridElement() {}
    GridElement& set_bg_color(int r, int g = 0, int b = 0, int a = 255){
        bg_color.r = r;
        bg_color.g = g;
        bg_color.b = b;
        bg_color.a = a;

        return *this;
    }

    GridElement& set_type(Type t){
        this->t = t;
        return *this;
    }

    GridElement& operator=(const GridElement& other) {
        this->fg_color = other.fg_color;
        this->bg_color = other.bg_color;
        this->character = other.character;
        this->t= other.t;

        return *this;
    }

    void write(GridRender& renderer) override{

    }
};



class GridRender : public Renderer{
private: 
    Vector2<int> _size    = {60, 60}; // the size of the grid element
    Vector2<int> _count   = {10, 10}; // the amount of grid elements
    Vector2<int> _offset  = {0, 0};
    // std::vector<GridElement> _buffer;
    size_t _pos = 0;
    static SDL_Texture CHARACTERS[256];
    SDL_Rect _buffer = {};
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

    void present () override {
        auto renderer = this->_render_target.get_renderer();
        SDL_RenderPresent(this->_render_target.get_renderer());
    }

    void draw_rect(size_t x, size_t y, size_t w, size_t h){
        this->_buffer.x = x;
        this->_buffer.y = x;
        this->_buffer.w = x;
        this->_buffer.h = x;
        SDL_RenderDrawRect(this->_render_target.get_renderer(), &this->_buffer);
    }

    Vector2<int> get_grid_size() { return this->_size; }
};

#endif
