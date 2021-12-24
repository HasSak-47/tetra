#include <algorithm>
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

bool end_game = false;
unsigned score = 0;
renderer ren("test1", 720, 540);
board playfield(0, 0, 10, 16);

std::map<std::string, unsigned> scores_map;
std::vector<std::string> order;

void sort_scores();
bool in_map(std::map<std::string, unsigned>& _map, std::string& str);

int main(){
    std::cout << "starting game...\n";

    //loading all scores and names
    std::fstream score_file("../data/scores.txt");

    if(!score_file.is_open()){
        std::cout << "couldn't find file ../data/scores.txt\n";
        return -1;
    }

    while(!score_file.eof()){
        std::string name_score;
        unsigned score_score;

        std::string line;
        getline(score_file, line);

        if(line.size() == 0) continue; 

        std::stringstream line_stream(line);

        line_stream >> name_score >> score_score;
        scores_map[name_score] = score_score;
        order.push_back(name_score);
    }

    std::cout << "total scores loaded: " << scores_map.size() << '\n';

    //starting game loop
    piece falling;
    std::cout << "setting rendered objects...\n";
    falling.rend = &ren;
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
    threads.push_back(std::thread(sort_scores));
    for(auto& thr : threads){
        thr.join();
    }
    SDL_Quit();
    
    std::string name;
    std::string messages[] = {
        "what is your name?\n",
        "name already used!\n"
    };
    size_t mess = 0;
    do{
        std::cout << messages[mess];
        std::cin >> name;
        mess = 1;
    }while(!in_map(scores_map, name));

    score_file.close();

    std::ofstream score_f("../data/scores.txt");

    std::cout << name << " your score is " << score << '\n'; 
    score_f << name << " " << score << "\n";

    size_t max_show = order.size() > 3 ? 3 : order.size();
    std::cout << "total scores that are going to show up: " << max_show << '\n';
    for(size_t i = 0; i < max_show; ++i){
        std::cout << "place " << i << " : " << order[i] << '\n'; 
    }

    std::cout << "ended threads\n";
    std::cout << "ended program (hopefully) without issues!\n";
    return 0;
}

//sorts all the scores in the scores vector
void sort_scores(){
    bool ended = ren.ended.get();
    std::cout << "sorting scores...\n";
    std::vector <std::string> new_order;
    std::map <std::string, unsigned> new_map;

    std::sort(order.begin(), order.end(), [=](const std::string& a, const std::string& b){
        return scores_map[a] < scores_map[b];
    });
}

//checks if string is in the map
bool in_map(std::map<std::string, unsigned>& _map, std::string& str){
    return _map.find(str) == _map.end();
}
