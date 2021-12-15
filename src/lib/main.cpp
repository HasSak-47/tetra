#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <map>

#include <renderer.h>
#include <rect.h>
#include <board.h>
#include <piece.h>

#include <chrono>

struct name_score{
    std::string& name;
    unsigned& total;
};

bool end_game = false;
unsigned score = 0;
renderer ren("test1", 720, 540);
board playfield(0, 0, 10, 16);

std::string player_name;
std::stringstream result;
std::map<std::string, unsigned> scores;
std::vector<name_score> sc;

void get_place(){
    bool ended = ren.ended.get();

    std::cout << "I used it!\n";
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
        std::string name = {};
        int score_v = {};
        score_file >> name >> score_v;
        scores[name] = score_v;
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

    std::cout << "please write your name:\n";
    std::cin >> player_name;
    std::cout << "player " << player_name << " this was your score: " << score << '\n';

    std::cout << "ended program (hopefully) without issues!\n";
    return 0;
}