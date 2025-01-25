//
// Merve Karacaoglu 32282
//

#ifndef UNTITLED2_BOARD_H
#define UNTITLED2_BOARD_H

#include <string>
using namespace std;

class Board
{
public:
    Board(const int & size, const int & lengthN);
    ~Board();
    void print_board();
    bool put_piece(char piece, int col);
    void turn_board_clockwise();
    char get_game_status();

private:
    bool check(char piece, int row,int col, int r, int c);

    int board_size;
    int N;
    char** matrix;

};






#endif //UNTITLED2_BOARD_H
