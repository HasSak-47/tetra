#include <iostream>
#include <thread>

#include <renderer.h>
#include <rect.h>
#include <board.h>
#include <piece.h>

#include <chrono>

bool end_game = true;
renderer ren("test1", 720, 600);
board playfield(0, 0, 10, 16);
rect preview(-0.6, 0, 4, 8, color {0x90, 0x90, 0x92, 0xff});
int main(){
    piece p(
        playfield, 
        -1, 1,
         0, 1,
         1, 1,
         2, 1,
         4, 14,
        piece_color[0]
    );
    ren.renderees.push_back(&playfield);
    ren.renderees.push_back(&preview);
    ren.renderees.push_back(&p);

    std::cout << "start\n";

    ren.render();
    //std::vector<std::thread> threads;
    //threads.push_back(std::thread(&renderer::render, &ren));
    //for(auto& thr : threads){
    //    thr.join();
    //}

    std::cout << "end!\n";
    return 0;
}