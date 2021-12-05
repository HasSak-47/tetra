#include <iostream>
#include <thread>

#include <renderer.h>
#include <rect.h>
#include <board.h>
#include <piece.h>

#include <chrono>

bool end_game = false;
renderer ren("test1", 720, 600);
board playfield(0, 0, 10, 16);
rect preview(-0.6, 0, 4, 8, color {0x15, 0x15, 0x17, 0xff});

int main(){
    std::cout << "start\n";
    piece falling;
    std::cout << "setting rendered objects...\n";
    falling.set_renderer(&ren);
    ren.renderees.push_back(&playfield);
    ren.renderees.push_back(&preview);
    ren.renderees.push_back(&falling);

    for(size_t i = 0; i < 7; ++i){
        ren.renderees.push_back(&parts[i]);
    }

    std::cout << "starting threads...\n";
    std::vector<std::thread> threads;
    threads.push_back(std::thread(generate_piece_queue));
    threads.push_back(std::thread(&renderer::render, &ren));
    threads.push_back(std::thread(&piece::loop, &falling));
    threads.push_back(std::thread(&piece::act, &falling));
    for(auto& thr : threads){
        thr.join();
    }

    std::cout << "end!\n";
    return 0;
}