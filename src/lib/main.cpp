#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <future>

#include <renderer.h>
#include <piece.h>

static std::condition_variable condition;
static std::mutex sync_mutex;
static SDL_Event event;
static bool ended = false;
static renderer ren;

void game_loop(){
    SDL_Init(SDL_INIT_VIDEO);

    uint32_t delta = 16;
    ren = renderer("test0", 720, 600);

    while(!ren.should_close()){
        {
            std::lock_guard<std::mutex> u_lock(sync_mutex);
            //std::cout << "started rendering\n";
            delta = ren.render();
            event = ren.get_event();
            //std::cout << "rendering ended\n";
        }
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
        std::lock_guard<std::mutex> u_lock(sync_mutex);

        end = SDL_GetTicks();
        delta_time = end - start;
        if(!falling.update(delta_time)) {
            continue;
        }
        start = end;
        end = SDL_GetTicks();
    }
}

void process_input(){
    while(!end_game){
        std::lock_guard<std::mutex> u_lock(sync_mutex);
        if(event.key.type == SDL_KEYUP) continue;
        if(!falling.input(event.key.keysym.sym)) continue;

        u_lock.~lock_guard();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(){
    std::cout << "start\n";
    std::vector<std::thread> threads;

    threads.push_back(std::thread(game_loop));
    threads.push_back(std::thread(piece_falling));
    threads.push_back(std::thread(process_input));
    for(auto& thread : threads){
        thread.join();
    }

    SDL_Quit();
    std::cout << "end!\n";
    return 0;
}