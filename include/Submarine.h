#ifndef SUBMARINE_H
#define SUBMARINE_H

#include <cstddef> /* size_t*/

class Submarine
{
public:
    Submarine(size_t a_length);
    void setHit();
    bool isDead() const;
    size_t length() const;

private:
    
    size_t  m_length;
    size_t  m_numOfHits;
    bool    m_isDead;
};




#endif