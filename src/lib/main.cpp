#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <future>

#include <renderer.h>
#include <piece.h>

std::mutex sync_mutex;
std::promise<bool> ended;

void game_loop(){
    SDL_Init(SDL_INIT_VIDEO);

    renderer ren("test0", 720, 600);
    uint32_t delta = 16;

    while(!ren.should_close()){
        std::unique_lock<std::mutex> u_lock(sync_mutex);
        delta = ren.render();
        u_lock.unlock();

        while(delta < 16 && !ren.should_close()) {
            delta = SDL_GetTicks() - ren.start;
        }
        //system("clear");
        //std::cout.precision(3);
        //std::cout << "fps: " << 1000.0f / delta_time << '\n';
    }
}

void piece_falling(){
    uint32_t start = SDL_GetTicks(), end = 0, delta_time = 0;
    while(!end_game){
        end = SDL_GetTicks();
        delta_time = end - start;
        if(delta_time  < 1000) continue;
        std::cout << "delta_time: " << delta_time << '\n';
        start = end;
        end = SDL_GetTicks();
        falling.update(delta_time);
    }
}

int main(){
    std::cout << "start\n";
    std::vector<std::thread> threads;
    std::future<bool> future = ended.get_future();

    threads.push_back(std::thread(game_loop));
    threads.push_back(std::thread(piece_falling));
    for(auto& thread : threads){
        thread.join();
    }
    return 0;
}