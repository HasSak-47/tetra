#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include <thread>
#include <iostream>
#include <vector>

#include <vector.hpp>
#include <renderer.hpp>

int main(){
    auto window = Window();
    int x = 10;
    int y = 16;
    int target = 16;
    float mulx = 255.0 / x;
    float muly = 255.0 / y;
    auto render = GridRender(window, 100, 100, 600, 500, x, y);

    auto start = std::chrono::system_clock::now();
    for(int indx = 0; indx < x * y; ++indx){
        Vector2<int> pos = {indx % x, indx / x};
        render.write(GridElement().set_bg_color(pos.x * mulx, pos.y * muly, 0, 0).set_type(Type::Rect));

        render.present();
    }

    render.present();
    std::this_thread::sleep_for(std::chrono::duration<float>(10));
}
