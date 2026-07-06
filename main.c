#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* for now not making it generic */
#define BOARD_SIZE 10
#define SHIPS_NUMBER 5

struct Board_Cell;
struct Ship_Cell;
struct name;

/* initialization functions must be called first */
void initialize_board(struct Board_Cell **board);
void initialize_ships(struct Ship_Cell **ships);

/* ship_placement and validation */
void place_ships(struct Board_Cell **board, struct Ship_Cell **ships);
void validate_ship_placement(struct Board_Cell **board, struct Ship_Cell **ships, int row_number, int column_number);

/* main game for turn and hitting on ship */
void human_make_move(struct Board_Cell **computer_board, struct Ship_Cell **computer_ships);
void computer_make_move(struct Board_Cell **human_board, struct Ship_Cell **human_ships);
bool check_ship_destroyed(struct Ship_Cell **ships);
bool check_game_over(struct Ship_Cell **player_1_ships, struct Ship_Cell **player_2_ships);

/* utility functions */
void display_board(const struct Board_Cell **board);
void display_ships(const struct Ship_Cell **ships);
void menu(const struct Board_Cell **board, const struct Ship_Cell **ships);

int main(int argc, char *argv[]) {
  return EXIT_SUCCESS;
}
