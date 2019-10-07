#include "Submarine.h"


Submarine::Submarine(size_t a_length)
:m_length(a_length)
,m_numOfHits(0)
,m_isDead(false)
{

}

void Submarine::setHit()
{
    if(!m_isDead)
    {
        ++m_numOfHits;
    }

    if(m_length == m_numOfHits)
    {
        m_isDead = true;
    }
}

size_t Submarine::length() const
{
    return m_length;
}

bool Submarine::isDead() const
{   
    return m_isDead;
}