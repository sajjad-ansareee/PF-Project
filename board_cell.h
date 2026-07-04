#pragma once

class Board_Cell
{
public:
    Board_Cell();

private:
    int ship_number;
    int ship_part_number;
    bool has_ship_part;
};