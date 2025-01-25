//
// Merve Karacaoglu 32282
//

#include "Player.h"

Player::Player(Board &board, char p)
: myBoard(board), piece(p)
{}

bool Player::put(int col)
{
    return myBoard.put_piece(piece, col);
}

void Player::turn_board()
{
    myBoard.turn_board_clockwise();
}

bool Player::is_winner()
{
    return myBoard.get_game_status() == piece;
}

char Player::get_symbol() const
{
    return piece;
}


