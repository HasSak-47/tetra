#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

#include <renderer.h>

std::mutex sync_mutex;

void game_loop(renderer& ren){
    uint32_t start = 0, end = 0, delta_time = 0;
    while(!ren.should_close()){
        std::unique_lock<std::mutex> lock(sync_mutex);
        lock.lock();
        uint32_t start = SDL_GetTicks();

        ren.render();

        uint32_t end = SDL_GetTicks();
        uint32_t delta_time = end - start;
        
        lock.release();

        if(delta_time < 16) std::this_thread::sleep_for( std::chrono::milliseconds(16 - delta_time) );
        delta_time = SDL_GetTicks() - start;
        system("clear");
        std::cout << "fps: " << 1000.0f / delta_time << '\n';
    }
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);

    renderer ren("test0", 100, 100);

    std::vector<std::thread> threads;
    threads.push_back(std::thread(game_loop, ren));

    return 0;
}