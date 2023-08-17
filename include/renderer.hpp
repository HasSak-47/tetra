#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <SDL_render.h>
#include "vector.hpp"

class Renderer{
public:
    virtual SDL_Renderer* get_render() = 0;
};

class GridRender : public Renderer{
private: 
    SDL_Window* _win;
    SDL_Renderer* _ren;
    const Vector2<int> _grid_size = {60, 60};
    const Vector2<int> _square_count = {10, 10};
public:
    GridRender(){
        this->_win= SDL_CreateWindow("tetris", 0, 0, 600, 600, 0);
        this->_ren= SDL_CreateRenderer(this->_win, 0, 0);
    }

    ~GridRender(){
        SDL_DestroyRenderer(this->_ren);
        SDL_DestroyWindow(this->_win);
    }


    void render(){ SDL_RenderPresent(this->_ren); }

    Vector2<int> get_grid_size() { return this->_grid_size; }

    SDL_Renderer* get_render() override {
        return this->_ren;
    }
};

#endif
