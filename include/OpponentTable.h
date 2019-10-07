#ifndef OPPPONENT_TABLE
#define OPPPONENT_TABLE

#include "Table.h"

class OpponentTable: Table<bool>
{
public:
    ~OpponentTable();
    void setCell(size_t a_row, size_t a_col, CellStatus a_status);

};





#endif