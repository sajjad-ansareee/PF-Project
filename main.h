#ifndef MAIN_H
#define MAIN_H
#include "board_cell.h"
#include "ship_cell.h"
#include <stdbool.h>

/* for now not making it generic */
#define BOARD_SIZE 10
#define TOTAL_SHIPS 5

/* initialization functions must be called first */
void allocate_memory(struct Board_Cell ***board, struct Ship_Cell ***ships);
void initialize_board(struct Board_Cell ***board);
void initialize_ships(struct Ship_Cell ***ships);

/* ship_placement and validation */
void human_place_ships(struct Board_Cell ***board, struct Ship_Cell ***ships);
void computer_place_ships(struct Board_Cell ***board, struct Ship_Cell ***ships);
/* this will first make sure the selected place can have the ship */
void ship_place_selection(struct Board_Cell **board, int ship_length, int *row_number, int *column_number);
bool valid_ship_bounds(struct Board_Cell **board, int ship_length, int row_number, int column_number);
bool has_ship_part(struct Board_Cell **board, int ship_length, int row_number, int column_number);
/* once the place has been chosen correctly simply place the ship */
void place_ship(struct Board_Cell ***board, int ship_length, int row_number, int column_number);

/* main game for turn and hitting on ship */
void human_attack(struct Board_Cell ***board, struct Ship_Cell ***ships);
void computer_attack(struct Board_Cell **board, struct Ship_Cell **ships);
/* this function will make sure to get the correct cell for attack */
void get_correct_attack(struct Board_Cell **board, int *row_number, int *column_number);
bool is_bounded_attack(struct Board_Cell **board, int row_number, int column_number);
bool is_cell_already_attacked(struct Board_Cell **board, int row_number, int column_number);
bool is_attack_on_ship(struct Board_Cell **board, int row_number, int column_number);
bool is_ship_destroyed(struct Ship_Cell **ships, int ship_number, int ship_length);
bool is_game_over(struct Ship_Cell **opponents_ships);

/* destruction of the allocated memory */
void destroy_memory(struct Board_Cell ***board, struct Ship_Cell ***ships);
void destroy_board(struct Board_Cell ***board);
void destroy_ships(struct Ship_Cell ***ship);

/* utility functions */
void display_board(struct Board_Cell **board);
void display_ships(struct Ship_Cell **ships);
void menu(const struct Board_Cell **board, const struct Ship_Cell **ships);

/* main game loop */
void start_game(void);

#endif
