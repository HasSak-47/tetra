#include <iostream>
#include <thread>

#include <renderer.h>
#include <board.h>

#include <chrono>

bool end_game = true;
renderer ren("test1", 720, 600);
board playfield(0, 0, 10, 16);
board preview(-0.7, 0.2, 4, 8);
int main(){
    ren.renderees.push_back(&playfield);
    ren.renderees.push_back(&preview);

    std::cout << "start\n";
    std::vector<std::thread> threads;
    threads.push_back(std::thread(&renderer::render, &ren));

    for(auto& thr : threads){
        thr.join();
    }


    std::cout << "end!\n";
    return 0;
}