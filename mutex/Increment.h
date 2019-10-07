#ifndef INCREMENTOR_H
#define INCREMENTOR_H

#include <cstddef>
#include "mutex.h"

template<typename T>
class Incrementor
{

public:
    Incrementor(size_t a_size = 1);

    T& operator++();
    T const & val() const;

    static void* IncActivator(void*);



private:
    size_t m_size;
    T m_val;
    advcpp::Mutex m_locker;
};


template<typename T>
T const& Incrementor<T>::val() const
{
    return m_val;
}

template<typename T>
Incrementor<T>::Incrementor(size_t a_size)
: m_size(a_size)
, m_val()
{

}

template<typename T>
T& Incrementor<T>::operator++()
{

    for(size_t i = 0; i < m_size; ++i)
    {
        m_locker.Lock();
        ++m_val;
        m_locker.UnLock();
    }

    return m_val;
}

template<typename T>
void* Incrementor<T>::IncActivator(void* _params)
{
    Incrementor<T>* self = static_cast<Incrementor<T>*>(_params);
    self->operator++();

    return 0;
}

#endif