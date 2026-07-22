/* where ever *** used mean passed by reference, ** mean passed by value like
 * const */
#include "main.h"
// #include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  srand(time(NULL));
  start_game();
  return EXIT_SUCCESS;
}

void display_board(struct Board_Cell **board)
{
  printf("The board:\n");
  for (int row_number = 1; row_number <= BOARD_SIZE; ++row_number)
  {
    for (int column_number = 1; column_number <= BOARD_SIZE; ++column_number)
    {
      if (board[row_number - 1][column_number - 1].is_occupied &&
          board[row_number - 1][column_number - 1].is_attacked)
      {
        printf("* ");
      }
      else
      {
        printf(". ");
      }
      // printf("%d ", board[row_number - 1][column_number -
      // 1].ship_part_number);
    }
    printf("\n");
  }
  printf("\n");
  return;
}

void display_ships(struct Ship_Cell **ships)
{
  printf("The ships status:\n");
  for (int ship_number = 1; ship_number <= TOTAL_SHIPS; ++ship_number)
  {
    for (int ship_part_number = 1; ship_part_number <= ship_number; ++ship_part_number)
    {
      printf("%d ", ships[ship_number - 1][ship_part_number - 1].destroyed);
    }
    printf("\n");
  }
  printf("\n");
  return;
}

void allocate_memory(struct Board_Cell ***board, struct Ship_Cell ***ships)
{
  initialize_board(board);
  initialize_ships(ships);
}

void initialize_board(struct Board_Cell ***board)
{
  (*board) = malloc(BOARD_SIZE * (sizeof(struct Board_Cell *)));
  for (int row_number = 1; row_number <= BOARD_SIZE; ++row_number)
  {
    (*board)[row_number - 1] = malloc(BOARD_SIZE * sizeof(struct Board_Cell));
    for (int column_number = 1; column_number <= BOARD_SIZE; ++column_number)
    {
      (*board)[row_number - 1][column_number - 1].is_occupied = false;
      (*board)[row_number - 1][column_number - 1].ship_number = 0;
      (*board)[row_number - 1][column_number - 1].ship_part_number = 0;
      (*board)[row_number - 1][column_number - 1].is_attacked = false;
    }
  }
  return;
}

void initialize_ships(struct Ship_Cell ***ships)
{
  (*ships) = malloc(TOTAL_SHIPS * (sizeof(struct Ship_Cell *)));
  for (int ship_number = 1; ship_number <= TOTAL_SHIPS; ++ship_number)
  {
    (*ships)[ship_number - 1] = malloc(ship_number * sizeof(struct Ship_Cell));
    for (int ship_part_number = 1; ship_part_number <= ship_number; ++ship_part_number)
    {
      (*ships)[ship_number - 1][ship_part_number - 1].destroyed = false;
    }
  }
  return;
}

void ship_place_selection(struct Board_Cell **board, int ship_length, int *row_number, int *column_number)
{
  bool correctly_placed_ship = false;
  while (!correctly_placed_ship)
  {
    printf("row_number: ");
    scanf("%d", row_number);
    printf("column_number: ");
    scanf("%d", column_number);
    if (!valid_ship_bounds(board, ship_length, *row_number, *column_number))
    {
      printf("The ship cannot fit inside the given space...\n");
    }
    else if (has_ship_part(board, ship_length, *row_number, *column_number))
    {
      printf("The portion already contains a ship part...\n");
    }
    else
    {
      correctly_placed_ship = true;
    }
  }
  return;
}

bool valid_ship_bounds(struct Board_Cell **board, int ship_length, int row_number, int column_number)
{
  if (!((row_number > 0 && row_number <= BOARD_SIZE) && (column_number > 0 && column_number <= BOARD_SIZE)))
  {
    return false;
  }
  /* for now placing the ships only in horizontal direction */
  if ((column_number + ship_length - 1) <= BOARD_SIZE)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool has_ship_part(struct Board_Cell **board, int ship_length, int row_number, int column_number)
{
  /* (ship_length-1) in the loop as the it start from the current_column so one
   * index would be merged */
  for (int current_column = column_number; current_column <= (column_number + (ship_length - 1)); ++current_column)
  {
    if (board[row_number - 1][current_column - 1].is_occupied == true)
    {
      return true;
    }
  }
  return false;
}

void place_ship(struct Board_Cell ***board, int ship_length, int row_number, int column_number)
{
  for (int current_column = column_number; current_column <= (column_number + (ship_length - 1)); ++current_column)
  {
    (*board)[row_number - 1][current_column - 1].is_occupied = true;
    (*board)[row_number - 1][current_column - 1].ship_number = ship_length;
    (*board)[row_number - 1][current_column - 1].ship_part_number = current_column - column_number + 1;
  }
  return;
}

void human_place_ships(struct Board_Cell ***board, struct Ship_Cell ***ships)
{
  printf("Place all your %d ships on the board...\n", TOTAL_SHIPS);
  for (int ship_number = 1; ship_number <= TOTAL_SHIPS; ++ship_number)
  {
    printf("Place your %d size ship...\n", ship_number);
    int row_number, column_number;
    ship_place_selection(*board, ship_number, &row_number, &column_number);
    place_ship(board, ship_number, row_number, column_number);
  }
  printf("Correctly placed all the ships...\n");
  return;
}

void computer_ship_place_selection(struct Board_Cell **board, int ship_length, int *row_number, int *column_number)
{
  bool correctly_placed = false;
  while (!correctly_placed)
  {
    /* using 1-based indexing */
    *row_number = (rand() % BOARD_SIZE) + 1;
    *column_number = (rand() % BOARD_SIZE) + 1;
    if (!valid_ship_bounds(board, ship_length, *row_number, *column_number))
    {
      /* the selected place cannot fit the ship */
    }
    else if (has_ship_part(board, ship_length, *row_number, *column_number))
    {
      /* place already contains a ship part */
    }
    else
    {
      correctly_placed = true;
    }
  }
  return;
}

void computer_place_ships(struct Board_Cell ***board, struct Ship_Cell ***ships)
{
  for (int ship_length = 1; ship_length <= TOTAL_SHIPS; ++ship_length)
  {
    int row_number, column_number;
    computer_ship_place_selection(*board, ship_length, &row_number, &column_number);
    place_ship(board, ship_length, row_number, column_number);
  }
  return;
}

void human_attack(struct Board_Cell ***board, struct Ship_Cell ***ships)
{
  int row_number, column_number;
  get_correct_attack(*board, &row_number, &column_number);
  if (is_attack_on_ship(*board, row_number, column_number))
  {
    printf("You hit the ship...\n");
    int ship_number = (*board)[row_number - 1][column_number - 1].ship_number;
    int ship_part_number = (*board)[row_number - 1][column_number - 1].ship_part_number;
    (*ships)[ship_number - 1][ship_part_number - 1].destroyed = true;
    if (is_ship_destroyed(*ships, ship_number, ship_number) == true)
    {
      printf("You destroyed the ship...\n");
      if (is_game_over(*ships))
      {
        printf("You won the game...\n");
      }
      else
      {
        printf("Game not over yet...\n");
      }
    }
  }
  else
  {
    printf("You missed the ship...\n");
  }
  (*board)[row_number - 1][column_number - 1].is_attacked = true;
}

void get_correct_attack(struct Board_Cell **board, int *row_number, int *column_number)
{
  bool is_correct_cell_attacked = false;
  while (!is_correct_cell_attacked)
  {
    printf("row_number: ");
    scanf("%d", row_number);
    printf("column_number: ");
    scanf("%d", column_number);
    if (is_bounded_attack(board, *row_number, *column_number) == false)
    {
      printf("Attack out of bounds of the board...\n");
    }
    else if (is_cell_already_attacked(board, *row_number, *column_number) ==
             true)
    {
      printf("Cell is already attacked...\n");
    }
    else
    {
      is_correct_cell_attacked = true;
    }
  }
  return;
}

bool is_bounded_attack(struct Board_Cell **human_board, int row_number, int column_number)
{
  if ((row_number > 0 && row_number <= BOARD_SIZE) && (column_number > 0 && column_number <= BOARD_SIZE))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool is_cell_already_attacked(struct Board_Cell **board, int row_number, int column_number)
{
  if (board[row_number - 1][column_number - 1].is_attacked == false)
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool is_attack_on_ship(struct Board_Cell **board, int row_number, int column_number)
{
  if (board[row_number - 1][column_number - 1].is_occupied == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool is_ship_destroyed(struct Ship_Cell **ships, int ship_number, int ship_length)
{
  for (int ship_part_number = 1; ship_part_number <= ship_length;
       ++ship_part_number)
  {
    if (ships[ship_number - 1][ship_part_number - 1].destroyed == false)
    {
      return false;
    }
  }
  return true;
}

bool is_game_over(struct Ship_Cell **opponents_ships)
{
  for (int ship_number = 1; ship_number <= TOTAL_SHIPS; ++ship_number)
  {
    if (is_ship_destroyed(opponents_ships, ship_number, ship_number) == false)
    {
      return false;
    }
  }
  return true;
}

void destroy_memory(struct Board_Cell ***board, struct Ship_Cell ***ships)
{
  destroy_board(board);
  destroy_ships(ships);
}

void destroy_board(struct Board_Cell ***board)
{
  for (int row_number = 1; row_number <= BOARD_SIZE; ++row_number)
  {
    free((*board)[row_number - 1]);
    (*board)[row_number - 1] = NULL;
  }
  free(*board);
  *board = NULL;
  board = NULL;
}

void destroy_ships(struct Ship_Cell ***ships)
{
  for (int row_number = 1; row_number <= TOTAL_SHIPS; ++row_number)
  {
    free((*ships)[row_number - 1]);
    (*ships)[row_number - 1] = NULL;
  }
  free(*ships);
  *ships = NULL;
  ships = NULL;
}

void start_game(void)
{
  struct Board_Cell **player1_board;
  struct Board_Cell **player2_board;
  // display_board(board);
  struct Ship_Cell **player1_ships;
  struct Ship_Cell **player2_ships;
  allocate_memory(&player1_board, &player1_ships);
  allocate_memory(&player2_board, &player2_ships);
  /* ships placement */
  /* players place ships on their own board */
  human_place_ships(&player1_board, &player1_ships);
  human_place_ships(&player2_board, &player2_ships);
  /* moves */
  char move = 'a';
  while (true)
  {
    if (move == 'a')
    {
      /* the attack is made on the opponents ships */
      printf("player1_attack...\n");
      human_attack(&player2_board, &player2_ships);
      move = 'b';
    }
    else if (move == 'b')
    {
      printf("player2_attack...\n");
      human_attack(&player1_board, &player1_ships);
      move = 'a';
    }
    printf("player1_board...\n");
    display_board(player1_board);
    printf("player2_board...\n");
    display_board(player2_board);
    if (is_game_over(player1_ships) || is_game_over(player2_ships))
    {
      display_ships(player1_ships);
      display_ships(player2_ships);
      break;
    }
  }
  /* destroy allocated memory */
  destroy_memory(&player1_board, &player1_ships);
  destroy_memory(&player2_board, &player2_ships);
  return;
}
