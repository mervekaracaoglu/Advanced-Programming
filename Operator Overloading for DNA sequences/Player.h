//
// Merve Karacaoglu 32282
//

#ifndef UNTITLED2_PLAYER_H
#define UNTITLED2_PLAYER_H
#include <iostream>
#include "Board.h"

using namespace std;

class Player
{
public:
    Player(Board & board,char p);
    bool put(int col);
    void turn_board();
    bool is_winner();
    [[nodiscard]] char get_symbol() const;


private:
    Board & myBoard;
    char piece;
};

#endif //UNTITLED2_PLAYER_H
