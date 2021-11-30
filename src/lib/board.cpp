#include <board.h>
#include <piece.h>

Board board;

bool Board::evaluate(piece& p){
    bool place = false;
    for(auto& sq : p.pieces){ //it loops throught out all the blocks of the pieces anc checks if their next position will be inhabitated
        vec2i pos = {sq.x + p.center.x, sq.y + p.center.y}; //the center isn't ther rotations center it is the offset that the piece has to (0,0)
        if(pos.y == 0 || m_board[pos.x][pos.y - 1] == Board::states::n){ // this checks if next position of each block (aka the one below them) is already occupated
            place = true; //the place need to be placed if not it will clip with the already placed pieces
            break;
        }
    }

    return place;
}

Board::states* Board::operator[](size_t index){
    return m_board[index];
}

Board::states* Board::operator[](int index){
    return m_board[index];
}
