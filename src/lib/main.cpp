#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <chrono>
#include <map>

#include <renderer.h>
#include <rect.h>
#include <board.h>
#include <piece.h>

struct name_score{
    std::string name;
    unsigned& total;
};

bool end_game = false;
unsigned score = 0;
renderer ren("test1", 720, 540);
board playfield(0, 0, 10, 16);

std::vector<name_score> scores;
std::map<std::string, unsigned> scores_map;

void get_place(){
    bool ended = ren.ended.get();
    std::cout << "I had no idea how to put this so it prints this :p\n";
    
}

int main(){
    std::cout << "starting game...\n";

    //loading all scores and names
    std::ifstream score_file("../data/scores.txt");

    if(!score_file.is_open()){
        std::cout << "couldn't find file ../data/scores.txt\n";
        return -1;
    }

    while(!score_file.eof()){
        std::string name_score;
        unsigned score_score;

        score_file >> name_score >> score_score;
        scores_map[name_score] = score_score;
        scores.push_back({name_score, scores_map[name_score]});
    }

    std::cout << "total scores loaded: " << scores.size() << '\n';

    //starting game loop
    piece falling;
    std::cout << "setting rendered objects...\n";
    falling.set_renderer(&ren);
    ren.renderees.push_back(&playfield);
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
    threads.push_back(std::thread(get_place));
    for(auto& thr : threads){
        thr.join();
    }
    SDL_Quit();
    
    std::cout << "ended threads\n";
    std::cout << "ended program (hopefully) without issues!\n";
    return 0;
}