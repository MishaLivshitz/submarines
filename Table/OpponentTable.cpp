#include "OpponentTable.h"


OpponentTable::~OpponentTable()
{
    
}

void OpponentTable::setCell(size_t a_row, size_t a_col, CellStatus a_status)
{
    m_table[a_row][a_col].first = a_status;
    m_table[a_row][a_col].second = true;
}