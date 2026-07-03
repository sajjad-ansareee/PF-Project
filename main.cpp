/*
	Two (n*n) size Matrices for each player
	Initialize ships on the Matrix
	Each player makes a move
	After every move check if cell contains ship part
	If cell contain ship part destroy the part and display to user
	After every part destroy check if that ship destroyed if destroyed display to user
	After every ship destroy check if the game is over
	The game is over when any of the player destroyes all ships of the opponent player
*/

#include <iostream>
#include <vector>

using namespace std;

#define BOARD_SIZE 10
#define SHIPS_NUMBER 5

class Board_Cell
{
public:
	Board_Cell() : ship_number(nullptr), ship_part_number(nullptr), has_ship_part(false) {}

private:
	u_int8_t *ship_number;
	u_int8_t *ship_part_number;
	bool has_ship_part;
};

int main(int argc, char *argv[])
{
	return 0;
}