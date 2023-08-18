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
    int width = 800;
    int height = 600;
public:
    Window(){
        this->_win= SDL_CreateWindow("tetris", 0, 0, width, height, 0);
        this->_ren= SDL_CreateRenderer(this->_win, 0, 0);
    }

    int get_height(){return this->height;}
    int get_width(){return this->width;}

    SDL_Renderer* get_renderer(){ return this->_ren; }
    SDL_Window* get_window(){ return this->_win; }

};

class Renderer{
protected:
    Window& _render_target;
public:
    Renderer(Window& win) : _render_target(win){}
    virtual void present() = 0;
};

enum Type{
    None = 0b000,
    Text = 0b001,
    Rect = 0b010,
    Bord = 0b100
};

class GridRender;

class GridElement{
protected:
    SDL_Rect _rect;
public:
    Vector4<int> fg_color = {};
    Vector4<int> bg_color = {};

    char32_t character = ' ';
    Type t = (Type)0;

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


    friend class GridRender;
};


class GridWriter{
    virtual void write(GridRender& renderer) = 0;
};

class GridRender : public Renderer{
private: 
    Vector2<int> _size    = {60, 60}; // the size of the grid element
    Vector2<int> _count   = {10, 10}; // the amount of grid elements
    Vector2<int> _offset  = {0, 0};
    std::vector<GridElement> _buffer;
    size_t _pos = 0;
    static SDL_Texture CHARACTERS[256];
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
    {
        int delta_x = w;
        int delta_y = h;
        int step_x = delta_x / xcount;
        int step_y = delta_y / ycount;

        int grid_count = xcount * ycount;

        this->_size = Vector2<int>{step_x, step_y};
        this->_buffer.resize(grid_count);
        for(int i = 0; i < grid_count; ++i){
            int x = i % this->_count.x;
            int y = i / this->_count.x;

            this->_buffer[i]._rect = {
                this->_offset.x + x * this->_size.x,
                this->_offset.y + y * this->_size.y,
                this->_size.x,
                this->_size.y
            };
        }
    }

    ~GridRender(){}

    void present () override {
        auto renderer = this->_render_target.get_renderer();
        for(const auto& element : this->_buffer){
            auto color = element.bg_color;
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            if((element.t & Type::Rect) != 0)
                SDL_RenderFillRect(renderer, &element._rect);
            else if((element.t & Type::Bord) != 0)
                SDL_RenderDrawRect(renderer, &element._rect);
        }
        SDL_RenderPresent(this->_render_target.get_renderer());
    }

    void write(GridElement element){

        this->_buffer[_pos]= element;
        SDL_SetRenderDrawColor(this->_render_target.get_renderer(), element.bg_color.r, element.bg_color.g, element.bg_color.b, element.bg_color.a);
        this->_pos++;
        this->_pos %= this->_buffer.size();
    }

    void write_at(GridElement element, int x, int y){
        int _pos = x + y * this->_count.x;
        this->_buffer[_pos]= element;
    }

    Vector2<int> get_grid_size() { return this->_size; }
};

#endif
