#include <board.h>
#include <piece.h>

piece::piece(
    board& b,
    int x1, int y1,
    int x2, int y2,
    int x3, int y3,
    int x4, int y4,

    int cx, int cy,

    color col
) : 
    m_board(b),
    renderee(0, 0, col),
    board_pos{cx, cy},
    pieces{ 
        {x1, y1},
        {x2, y2},
        {x3, y3},
        {x4, y4},
    },
    padding(b.get_padding())
{
    should_render = true;
}


bool board::evaluate_next(piece& p){
    return false;
}

void piece::rotate() {

}

void piece::move_down() {

}

void piece::move_side(side s) {

}

void piece::drop() {

}
