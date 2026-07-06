#pragma once
#include "board_cell.h"
#include <vector>

using namespace std;

#define BOARD_SIZE 10

class Board
{
public:
    /* default constructor */
    Board();

private:
    vector<vector<Board_Cell>> table;
};
