/* where ever *** used mean passed by reference, ** mean passed by value like const */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* for now not making it generic */
#define BOARD_SIZE 10
#define TOTAL_SHIPS 5

struct Board_Cell;
struct Ship_Cell;

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
void human_attack(struct Board_Cell ***computer_board, struct Ship_Cell ***computer_ships);
void computer_attack(struct Board_Cell **human_board, struct Ship_Cell **human_ships);
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

int main(int argc, char *argv[]) {
  struct Board_Cell **board;
  initialize_board(&board);
  display_board(board);
  struct Ship_Cell **ships;
  initialize_ships(&ships);
  display_ships(ships);
  human_place_ships(&board, &ships);
  display_board(board);
  display_ships(ships);
  return EXIT_SUCCESS;
}

struct Board_Cell {
  /* it will store in 1-based index, 0 show no ship/ship_part here */
  bool is_occupied;
  bool is_attacked;
  int ship_number;
  int ship_part_number;
};

struct Ship_Cell {
  bool destroyed;
};

void display_board(struct Board_Cell **board) {
  printf("The board:\n");
  for (int row_number = 1; row_number <= BOARD_SIZE; ++row_number) {
    for (int column_number = 1; column_number <= BOARD_SIZE; ++column_number) {
      printf("%d ", board[row_number - 1][column_number - 1].ship_part_number);
    }
    printf("\n");
  }
  printf("\n");
  return;
}

void display_ships(struct Ship_Cell **ships) {
  printf("The ships status:\n");
  for (int ship_number = 1; ship_number <= TOTAL_SHIPS; ++ship_number) {
    for (int ship_part_number = 1; ship_part_number <= ship_number; ++ship_part_number) {
      printf("%d ", ships[ship_number - 1][ship_part_number - 1].destroyed);
    }
    printf("\n");
  }
  printf("\n");
  return;
}

void allocate_memory(struct Board_Cell ***board, struct Ship_Cell ***ships) {
  initialize_board(board);
  initialize_ships(ships);
}

void initialize_board(struct Board_Cell ***board) {
  (*board) = malloc(BOARD_SIZE * (sizeof(struct Board_Cell *)));
  for (int row_number = 1; row_number <= BOARD_SIZE; ++row_number) {
    (*board)[row_number - 1] = malloc(BOARD_SIZE * sizeof(struct Board_Cell));
    for (int column_number = 1; column_number <= BOARD_SIZE; ++column_number) {
      (*board)[row_number - 1][column_number - 1].is_occupied = false;
      (*board)[row_number - 1][column_number - 1].ship_number = 0;
      (*board)[row_number - 1][column_number - 1].ship_part_number = 0;
      (*board)[row_number - 1][column_number - 1].is_attacked = false;
    }
  }
  return;
}

void initialize_ships(struct Ship_Cell ***ships) {
  (*ships) = malloc(TOTAL_SHIPS * (sizeof(struct Ship_Cell *)));
  for (int row_number = 1; row_number <= TOTAL_SHIPS; ++row_number) {
    (*ships)[row_number - 1] = malloc(TOTAL_SHIPS * sizeof(struct Ship_Cell));
    for (int column_number = 1; column_number < TOTAL_SHIPS; ++column_number) {
      (*ships)[row_number - 1][column_number - 1].destroyed = false;
    }
  }
  return;
}

void ship_place_selection(struct Board_Cell **board, int ship_length, int *row_number, int *column_number) {
  bool correctly_placed_ship = false;
  while (!correctly_placed_ship) {
    printf("row_number: ");
    scanf("%d", row_number);
    printf("column_number: ");
    scanf("%d", column_number);
    if (!valid_ship_bounds(board, ship_length, *row_number, *column_number)) {
      printf("The ship cannot fit inside the given space...\n");
    } else if (has_ship_part(board, ship_length, *row_number, *column_number)) {
      printf("The portion already contains a ship part...\n");
    } else {
      correctly_placed_ship = true;
    }
  }
  return;
}

bool valid_ship_bounds(struct Board_Cell **board, int ship_length, int row_number, int column_number) {
  if (!((row_number > 0 && row_number <= BOARD_SIZE) && (column_number > 0 && column_number <= BOARD_SIZE))) {
    return false;
  }
  /* for now placing the ships only in horizontal direction */
  if ((column_number + ship_length - 1) <= BOARD_SIZE) {
    return true;
  } else {
    return false;
  }
}

bool has_ship_part(struct Board_Cell **board, int ship_length, int row_number, int column_number) {
  /* (ship_length-1) in the loop as the it start from the current_column so one index would be merged */
  for (int current_column = column_number; current_column <= (column_number + (ship_length - 1)); ++current_column) {
    if (board[row_number - 1][current_column - 1].is_occupied == true) {
      return true;
    }
  }
  return false;
}

void place_ship(struct Board_Cell ***board, int ship_length, int row_number, int column_number) {
  for (int current_column = column_number; current_column <= (column_number + (ship_length - 1)); ++current_column) {
    (*board)[row_number - 1][current_column - 1].is_occupied = true;
    (*board)[row_number - 1][current_column - 1].ship_number = ship_length;
    (*board)[row_number - 1][current_column - 1].ship_part_number = current_column - column_number + 1;
  }
  return;
}

void human_place_ships(struct Board_Cell ***board, struct Ship_Cell ***ships) {
  printf("Place all your %d ships on the board...\n", TOTAL_SHIPS);
  for (int ship_number = 1; ship_number <= TOTAL_SHIPS; ++ship_number) {
    printf("Place your %d size ship...\n", ship_number);
    int row_number, column_number;
    ship_place_selection(*board, ship_number, &row_number, &column_number);
    place_ship(board, ship_number, row_number, column_number);
  }
  printf("Correctly placed all the ships...\n");
  return;
}

void human_attack(struct Board_Cell ***computer_board, struct Ship_Cell ***computer_ships) {
  int row_number, column_number;
  printf("row_number: ");
  scanf("%d", &row_number);
  printf("column_number: ");
  scanf("%d", &column_number);
}

bool is_bounded_attack(struct Board_Cell **human_board, int row_number, int column_number) {
  if ((row_number > 0 && row_number <= BOARD_SIZE) && (column_number > 0 && column_number <= BOARD_SIZE)) {
    return true;
  } else {
    return false;
  }
}

bool is_cell_already_attacked(struct Board_Cell **board, int row_number, int column_number) {
  if (board[row_number - 1][column_number - 1].is_attacked == false) {
    return true;
  } else {
    return false;
  }
}

bool is_attack_on_ship(struct Board_Cell **board, int row_number, int column_number) {
  if (board[row_number - 1][column_number - 1].is_occupied == true) {
    return true;
  } else {
    return false;
  }
}

bool is_ship_destroyed(struct Ship_Cell **ships, int ship_number, int ship_length) {
  for (int ship_part_number = 1; ship_part_number <= ship_length; ++ship_part_number) {
    if (ships[ship_number - 1][ship_part_number - 1].destroyed == false) {
      return false;
    }
  }
  return true;
}

bool is_game_over(struct Ship_Cell **opponents_ships) {
  for (int ship_number = 1; ship_number <= TOTAL_SHIPS; ++ship_number) {
    if (is_ship_destroyed(opponents_ships, ship_number, ship_number)) {
      return false;
    }
  }
  return true;
}

void destroy_memory(struct Board_Cell ***board, struct Ship_Cell ***ships) {
  destroy_board(board);
  destroy_ships(ships);
}

void destroy_board(struct Board_Cell ***board) {
  for (int row_number = 1; row_number <= BOARD_SIZE; ++row_number) {
    free((*board)[row_number - 1]);
    (*board)[row_number - 1] = NULL;
  }
  free(*board);
  *board = NULL;
  board = NULL;
}

void destroy_ships(struct Ship_Cell ***ships) {
  for (int row_number = 1; row_number <= TOTAL_SHIPS; ++row_number) {
    free((*ships)[row_number - 1]);
    (*ships)[row_number - 1] = NULL;
  }
  free(*ships);
  *ships = NULL;
  ships = NULL;
}
