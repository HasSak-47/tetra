#include <iostream>
#include <thread>

#include <renderer.h>

bool end_game = true;

int main(){
    ren = renderer("test1", 720, 600);

    std::vector<SDL_Rect> rects;
    rects.push_back({30, 30, 30, 30});

    renderee part(rects);

    std::vector<std::thread> threads;

    threads.push_back(std::thread(&renderer::render, &ren));

    for(auto& thr : threads){
        thr.join();
    }


    std::cout << "start\n";
    std::cout << "end!\n";
    return 0;
}