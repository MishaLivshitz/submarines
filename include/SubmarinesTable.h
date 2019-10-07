#ifndef SUBMARINES_TABLE_H
#define SUBMARINES_TABLE_H

#include "Table.h"
#include "SharedPtr.h"
#include "Submarine.h"
#include <stdexcept>

class SubMarinesTable: public Table<SharedPtr<Submarine> >
{

public:

    typedef enum {DOWN, RIGHT} Direction;

    SubMarinesTable();
    ~SubMarinesTable();

    void addSubmarine(std::pair<size_t,size_t> a_start, Direction a_dir, SharedPtr<Submarine> const& a_submarine) throw(std::runtime_error);
    bool handleShot(size_t a_row, size_t a_col) throw(std::runtime_error);
    static const int* sizes();

private:
    bool checkValidty(std::pair<size_t,size_t> a_start, Direction a_dir ,size_t a_length) const;
    void makeDirty(std::pair<size_t,size_t> a_start, Direction a_dir);
    static const int S_SIZES[5];

};



#endif