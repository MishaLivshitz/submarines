#ifndef TABLE_H
#define TABLE_H

#include <utility>
#include <iostream>
#include "utils.h"


template <typename T>
class Table: public UnCopyable
{

public:
    typedef enum {EMPTY = 0, MARKED, ALIVE, DEAD, DIRTY} CellStatus;
    typedef std::pair<CellStatus, T> Cell;
 
    virtual ~Table() = 0;
    virtual void print() const;
    
    Cell const* operator[](size_t a_row) const;
    Cell* operator[](size_t a_row);
    static int size();

protected:
    static int const s_size = 10;
    std::pair<CellStatus, T> m_table[s_size][s_size];

};

template <typename T>
int Table<T>::size()
{
    return s_size;
}

template <typename T>
Table<T>::~Table()
{

}

template <typename T>
typename Table<T>::Cell const* Table<T>::operator[](size_t a_row) const
{
    return m_table[a_row];
}

template <typename T>
typename Table<T>::Cell* Table<T>::operator[](size_t a_row)
{
    return m_table[a_row];
}

template <typename T>
void Table<T>::print() const
{
    for(size_t i = 0; i< s_size;++i)
    {
        std::cout << '|';
        for(size_t j = 0 ;j<s_size;++j)
        {
            switch(m_table[i][j].first)
            {
                case MARKED:
                case ALIVE:
                    std::cout << "*|";
                    break;

                case DEAD:
                    std::cout << "D|";
                    break;

                case DIRTY:
                    std::cout << "X|";
                    break;

                default:
                    std::cout << " |";
                    break;
            }
        }

        std::cout << std::endl;
    }
}

#endif