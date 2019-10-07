#ifndef ATOMIC_VAL_H
#define ATOMIC_VAL_H

#include "utils.h"


template <typename T>
class AtomicVal: private UnCopyable
{
public:
   
    AtomicVal(T a_val = 0);

    AtomicVal<T>& operator++();
    T operator++(int);

    AtomicVal<T>& operator--();
    T operator--(int);

    AtomicVal<T>& operator+=(AtomicVal<T> const& _rhs);
    AtomicVal<T>& operator-=(AtomicVal<T> const& _rhs);

    bool testAndSet(int a_cond);

    operator T();

    T value() const;
    
private:
    T m_val;
};

template <typename T>
bool AtomicVal<T>::testAndSet(int a_cond)
{
    return  __sync_lock_test_and_set(&m_val, a_cond);
}


template <typename T>
AtomicVal<T>::AtomicVal(T a_val)
:m_val(a_val)
{

}

template <typename T>
T AtomicVal<T>::value() const
{
    return  __sync_add_and_fetch(const_cast<T*>(&m_val), 0);
}

template <typename T>
AtomicVal<T>& AtomicVal<T>::operator++()
{
    __sync_add_and_fetch(&m_val,1);
    return *this;
}

template <typename T>
T AtomicVal<T>::operator++(int)
{
    AtomicVal<T> temp(*this);
   __sync_fetch_and_add(&m_val,1);
   return temp;
}

template <typename T>
AtomicVal<T>& AtomicVal<T>::operator--()
{
    __sync_sub_and_fetch(&m_val,1);
    return *this;
}

template <typename T>
T AtomicVal<T>::operator--(int)
{   
    AtomicVal<T> temp(*this);
    __sync_fetch_and_sub(&m_val, 1);
    return temp;
}

template <typename T>
AtomicVal<T>& AtomicVal<T>::operator+=(AtomicVal<T> const& _rhs)
{
    __sync_add_and_fetch(&m_val, _rhs.value());
    return *this;
}

template <typename T>
AtomicVal<T>& AtomicVal<T>::operator-=(AtomicVal<T> const& _rhs)
{
    __sync_sub_and_fetch(&m_val, _rhs.value());
    return *this;
}

template <typename T>
AtomicVal<T>::operator T()
{
    return value();
}



#endif

