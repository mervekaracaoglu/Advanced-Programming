//
// Merve Karacaoglu 32282
//
#include <iostream>
using namespace std;
#include "Board.h"

Board::Board(const int &size, const int &lengthN) //parametric constructor
{
    board_size = size;
    N = lengthN;
    matrix = new char*[board_size];
    for (int i = 0; i < board_size; i++)
    {
        matrix[i] = new char[board_size];
    }
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            matrix[i][j] = '-';
        }
    }
}

Board::~Board() //destructor
{
    for (int i = 0; i < board_size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Board::print_board()
{
    cout << endl;
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;

}

bool Board::put_piece(char piece, int col)
{
    if(col < 0 || col >= board_size) //check if col value is inside the board
    {
        return false;
    }
    for(int row = board_size -1; row >= 0; --row) //traverse from the bottom of the column to top of the column row by row to find an empty place to put the piece in
    {
        if(matrix[row][col]== '-')
        {
            matrix[row][col] = piece;
            return true;
        }
    }
    return false;
}

void Board::turn_board_clockwise()
{
    char** rotated_matrix = new char*[board_size];
    for(int i = 0; i < board_size; i++) //create a new matrix to rotate it
    {
        rotated_matrix[i] = new char[board_size];
    }

    for (int i = 0; i < board_size; i++) //fill matrix as rotated
    {
        for (int j = 0; j < board_size; j++)
        {
            rotated_matrix[j][board_size - i - 1] = matrix[i][j];
        }
    }

    for (int i = 0; i < board_size; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    matrix = rotated_matrix;

    for(int col = 0; col < board_size; col++) //apply gravity to board
    {
        int newRow = board_size -1;
        for(int row = board_size -1; row >= 0; row--)
        {
            if(matrix[row][col] != '-')
            {
                matrix[newRow][col] = matrix[row][col];
                if(newRow != row)
                {
                    matrix[row][col] = '-';

                }
                newRow--;
            }
        }

    }
}

char Board::get_game_status()
{
    char winner = '-';
    for(int i = 0; i < board_size; i++)
    {
        for(int j = 0; j <= board_size - N; j++)
        {
            char horizontal = matrix[i][j];
            if(horizontal != '-' && check(horizontal, i, j, 0, 1)) //check horizontally
            {
                if(winner != '-' && winner != horizontal)
                {
                    return 'D';
                }
                winner = horizontal;
            }
            char vert = matrix[j][i]; //check vertically
            if(vert != '-' && check(vert, j, i, 1, 0))
            {
                if(winner != '-' && winner != vert)
                {
                    return 'D';
                }
                winner = vert;
            }
        }
    }
    for(int i = 0; i <= board_size - N; i++) //check diagonally from left to right and right to left
    {
        for(int j = 0; j <= board_size - N; ++j)
        {
            char diagonal = matrix[i][j];

            if(diagonal != '-' && check(diagonal, i, j, 1, 1))
            {
                if(winner != '-' && winner != diagonal)
                {
                    return 'D';
                }
                winner = diagonal;
            }
            char diagonal1 = matrix[i][board_size - j - 1];
            if(diagonal1 != '-' && check(diagonal1, i, board_size-j-1, 1, -1))
            {
                if(winner != '-' && winner != diagonal1)
                {
                    return 'D';
                }
                winner = diagonal1;
            }
        }
    }
    bool isFull = true; //check if board is full
    for(int i = 0; i < board_size;++i)
    {
        for(int j = 0; j < board_size; ++j)
        {
            if(matrix[i][j] == '-')
            {
                isFull = false;
            }
        }
    }
    if(winner != '-')
    {
        return winner;
    }
    else if(isFull)
    {
        return 'D';
    }
    else
    {
        return '-';
    }


}

bool Board::check(char piece, int row, int col, int r, int c) //check the lines for horizontal, vertical and diagonal
{
    for(int n = 0; n < N; ++n)
    {
        if(matrix[row + n * r][col + n * c] != piece)
        {
            return false;
        }
    }
    return true;
}








