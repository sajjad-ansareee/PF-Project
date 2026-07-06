#include "board_cell.h"

/* -1 indicates the cell contains no ship part */
Board_Cell::Board_Cell()
    : ship_number(-1), ship_part_number(-1), has_ship_part(false) {}
