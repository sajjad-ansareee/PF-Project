#ifndef BOARD_CELL_H
#define BOARD_CELL_H

#include <stdbool.h>

struct Board_Cell {
  /* it will store in 1-based index, 0 show no ship/ship_part here */
  bool is_occupied;
  bool is_attacked;
  int ship_number;
  int ship_part_number;
};

#endif