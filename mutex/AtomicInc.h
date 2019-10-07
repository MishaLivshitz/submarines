#ifndef ATOMIC_INC
#define ATOMIC_INC

#include <cstddef>
#include "AtomicVal.h"

namespace advcpp
{
template<typename T>
class AtomicInc
{

public:
    AtomicInc(size_t a_size = 1, T a_val = 0);

    AtomicInc<T>& operator++();
    T val() const;

    static void* IncActivator(void*);



private:
    size_t m_size;
    AtomicVal<T> m_val;
};


template<typename T>
T AtomicInc<T>::val() const
{
    return m_val.value();
}

template<typename T>
AtomicInc<T>::AtomicInc(size_t a_size, T a_val)
: m_size(a_size)
, m_val(a_val)
{

}

template<typename T>
AtomicInc<T>& AtomicInc<T>::operator++()
{
    for(size_t i = 0; i < m_size; ++i)
    {
        ++m_val;
    }
    return *this;
}

template<typename T>
void* AtomicInc<T>::IncActivator(void* _params)
{
    AtomicInc<T>* self = static_cast<AtomicInc<T>*>(_params);
    self->operator++();

    return 0;
}

}

#endif