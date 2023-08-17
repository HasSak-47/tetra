#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include <thread>
#include <iostream>
#include <vector>

#include <vector.hpp>
#include <renderer.hpp>

class Renderee{
protected:
    Renderer& _renderer;
public:
    Renderee(Renderer& render) : _renderer(render){}

    virtual void render() = 0;
};

namespace Renderees{
class ColoredSquare: public Renderee{
public:
    SDL_Rect _rectangle = {};
    int r, g, b, a;
    ColoredSquare(GridRender& render, int x = 0, int y = 0, int r = 0, int g = 0, int b = 0, int a = 255) :
        Renderee(render),
        r(r), b(b), g(g), a(a)
    {
        const auto grid_size = render.get_grid_size();
        this->_rectangle = {
            x * grid_size.x,
            y * grid_size.y,
            1 * grid_size.x,
            1 * grid_size.y,
        };

        
    }

    void render() override {
        auto render_ptr = this->_renderer.get_render();
        SDL_SetRenderDrawColor(render_ptr, r, g, b, a);
        SDL_RenderFillRect(render_ptr, &this->_rectangle);

    }
};
}

using namespace Renderees;

int main(){
    auto render = GridRender();

    std::vector<ColoredSquare> squares = {};
    for(int indx = 0; indx < 100; ++indx){
        Vector2<int> pos = {indx % 10, indx / 10};

        ColoredSquare(render, pos.x, pos.y, pos.x * 25, pos.y * 25).render();
        render.render();
        std::this_thread::sleep_for(std::chrono::duration<float>(0.1));
    }

    render.render();
    std::this_thread::sleep_for(std::chrono::duration<float>(1));
}
