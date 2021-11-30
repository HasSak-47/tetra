#include <piece.h>
#include <board.h>
#include <thread>
#include <random>
#include <mutex>

static std::default_random_engine gen;
static std::uniform_int_distribution<size_t> dist(1, 6);
static std::mutex piece_mutex;

const color piece::l_color = {0x00, 0x00, 0xff};
const color piece::s_color = {0x00, 0xff, 0x00};
const color piece::z_color = {0xff, 0xff, 0xff};
const color piece::t_color = {0xff, 0x00, 0x00};
const color piece::j_color = {0xff, 0x00, 0xff};
const color piece::i_color = {0xff, 0xff, 0x00};

const piece tetros[7] = {};
piece falling;

bool piece::input(SDL_Keycode input){
    static complexi rotators[] =  {{0, 1}, {0, -1}};
    bool evaluated = false;
    std::lock_guard<std::mutex> lock(piece_mutex);

    switch (static_cast<keys>(input)){
    case keys::left:
        rotate(rotators[0]);
        evaluated = true;
        break;

    case keys::right:
        rotate(rotators[1]);    
        evaluated = true;
        break;

    case keys::down:
        evaluated = true;
        evaluate_down();
        break;
    
    default:
        break;
    };

    return evaluated;
}

void piece::rotate(complexi rotator){}


void piece::evaluate_down(){
    std::cout << "checking down\n";
    //this assumes that the piece will not be placed
    bool place = false;
    for(auto& sq : pieces){ //it loops throught out all the blocks of the pieces anc checks if their next position will be inhabitated
        vec2i pos = {sq.x + center.x, sq.y + center.y}; //the center isn't ther rotations center it is the offset that the piece has to (0,0)
        if(pos.y == 0 || board[pos.x][pos.y - 1] == Board::states::n){ // this checks if next position of each block (aka the one below them) is already occupated
            place = true; //the place need to be placed if not it will clip with the already placed pieces
            break;
        }
    }

    if(place){
        for(auto& sq : pieces){ //if it has to be placed it writes in the board the current position
            vec2i new_pos = {sq.x + center.x, sq.y + center.y};
            board[new_pos.x][new_pos.y] = static_cast<Board::states>(type + 1);
        }

        for(auto& sq : pieces){
            vec2i pos = {sq.x + center.x, sq.y + center.y}; //if the position in which pieces spawn is used the game ends
            if(board[pos.x][15] == 1){
                end_game = true;
                return;
            }
        }
    }
    else {
        center.y--; //move the offset by negative one
    }
}

bool piece::update(uint32_t delta_time){
    if(delta_time < speed) return false; //checks if it has to be updated
    std::lock_guard<std::mutex> lock(piece_mutex);
    evaluate_down();

    return true;
}