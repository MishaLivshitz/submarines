#include "SubmarinesTable.h"


const int SubMarinesTable::S_SIZES[5] = {2,3,3,4,5};

const int* SubMarinesTable::sizes()
{
    return S_SIZES;
}

SubMarinesTable::SubMarinesTable()
:Table()
{

}

SubMarinesTable::~SubMarinesTable()
{

}

bool SubMarinesTable::handleShot(size_t a_row, size_t a_col) throw(std::runtime_error)
{
    if(a_row >= s_size || a_col >= s_size)
    {
        throw std::runtime_error("Not in range");
    }

    if(m_table[a_row][a_col].first == ALIVE)
    {
        m_table[a_row][a_col].second->setHit();
        m_table[a_row][a_col].first = DEAD;
        return true;
    }
    else
    {
        m_table[a_row][a_col].first = DIRTY;
    }
    

    return false;
}

void SubMarinesTable::addSubmarine( std::pair<size_t,size_t> a_start, Direction a_dir,
                                    SharedPtr<Submarine> const& a_submarine) throw(std::runtime_error)
{

    size_t length = a_submarine->length();
    if(!checkValidty(a_start,a_dir,length))
    {
        throw std::runtime_error("Wrong input");
    }

    switch (a_dir)
    {
    case DOWN:
        makeDirty(a_start,a_dir);
        for(size_t i  = a_start.first; length > 0; ++i, --length)
        {
            m_table[i][a_start.second].first = ALIVE; 
            m_table[i][a_start.second].second = a_submarine;

            if(a_start.second-1 < s_size)
            {
                m_table[i][a_start.second-1].first = DIRTY; 
            }
            if(a_start.second+1 < s_size)
            {
                m_table[i][a_start.second+1].first = DIRTY;
            }
        }
        a_start.first+=a_submarine->length()+1;
        makeDirty(a_start,a_dir);
        break;
    
    case RIGHT:
        makeDirty(a_start,a_dir);
        for(size_t i = a_start.second; length > 0; ++i , --length)
        {
            m_table[a_start.first][i].first = ALIVE; 
            m_table[a_start.first][i].second = a_submarine; 

            if(a_start.first-1 < s_size)
            {
                m_table[a_start.first-1][i].first = DIRTY; 
            }
            if(a_start.first+1 < s_size)
            {
                m_table[a_start.first+1][i].first = DIRTY;
            }
        }

        a_start.second+=a_submarine->length()+1;
        makeDirty(a_start,a_dir);
        break;
    }

}

bool SubMarinesTable::checkValidty(std::pair<size_t,size_t> a_start, Direction a_dir, size_t a_length) const
{
    if(a_start.first > s_size || a_start.second > s_size)
    {
        return false;
    }

    switch (a_dir)
    {
    case DOWN:
        for(size_t i  = a_start.first; a_length > 0; ++i, --a_length)
        {
            if(m_table[i][a_start.second].first != EMPTY || i >= s_size)
            {
                return false;
            }
        }
        break;
    
    case RIGHT:
        for(size_t i = a_start.second; a_length > 0; ++i , --a_length)
        {
            if(m_table[a_start.first][i].first != EMPTY || i >= s_size)
            {
                return false;
            } 
        }
        break;
    }

    return true;
}

void SubMarinesTable::makeDirty(std::pair<size_t,size_t> a_start, Direction a_dir)
{
    size_t iterations = 3;
    switch (a_dir)
    {
    case RIGHT:
        if(a_start.second-1 <s_size)
        {
            for(size_t i  = a_start.first - 1; iterations > 0; ++i, --iterations)
            {
                if(m_table[i][a_start.second-1].first != DIRTY && i < s_size)
                {
                    m_table[i][a_start.second-1].first = DIRTY;
                }
            }
            break;
        }
    
    case DOWN:
        if(a_start.first-1 <s_size)
        {
            for(size_t i = a_start.second-1; iterations > 0; ++i , --iterations)
            {
                if(m_table[a_start.first-1][i].first != DIRTY && i < s_size)
                {
                    m_table[a_start.first-1][i].first = DIRTY;
                } 
            }
            break;
        }
    }
}