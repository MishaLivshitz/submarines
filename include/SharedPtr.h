#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include "AtomicVal.h"
#include <cassert>
#include <algorithm>

template <typename T>
class SharedPtr
{

    typedef void (SharedPtr::*bool_type)() const;

public:
    
    explicit SharedPtr(T* = 0);
    SharedPtr(SharedPtr const&);

    template <typename D>
    SharedPtr(SharedPtr<D> const&);

    ~SharedPtr();

    operator bool_type() const;


    SharedPtr& operator=(SharedPtr const&);
    
    template <typename D>
    SharedPtr<T>& operator=(SharedPtr<D> const& _rhs);

    T* operator->() const;
    T& operator*() const;

    int counter() const;

private:
    void dummyFunc() const {};
    void swapCopy(SharedPtr& _rhs);

private:
    template <typename D>
    friend class SharedPtr;

    T* m_ptr;
    AtomicVal<int>* m_counter;

};

template <typename T>
SharedPtr<T>::operator SharedPtr<T>::bool_type() const
{
    return m_ptr!=0 ? &SharedPtr<T>::dummyFunc: 0;
}

template <typename T>
int SharedPtr<T>::counter() const
{
    return m_counter->value();
}

template <typename T>
SharedPtr<T>::SharedPtr(T* a_obj)
: m_ptr(a_obj)
{
    try
    {
        m_counter = new AtomicVal<int>(1);
    }
    catch(...)
    {
        delete m_ptr;
        throw;
    }
}

template <typename T>
template <typename D>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<D> const& a_rhs)
{
    SharedPtr<T> copy(a_rhs);
    copy.swapCopy(*this);

    return *this;
}

template <typename T>
template <typename D>
SharedPtr<T>::SharedPtr(SharedPtr<D> const& a_rhs)
: m_ptr(a_rhs.m_ptr)
, m_counter(a_rhs.m_counter)
{
    ++*m_counter;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr const& a_rhs)
: m_ptr(a_rhs.m_ptr)
, m_counter(a_rhs.m_counter)
{
    ++*m_counter;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{

    if(1 == m_counter->value())
    {
        delete m_ptr;
        delete m_counter;
    }
    else
    {
        --*m_counter;
    }
}

template <typename T>
void SharedPtr<T>::swapCopy(SharedPtr& _rhs)
{
    std::swap(m_ptr,_rhs.m_ptr);
    std::swap(m_counter,_rhs.m_counter);
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr const& a_rhs)
{
    SharedPtr copy(a_rhs);
    copy.swapCopy(*this);

    return *this;
}

template <typename T>
T* SharedPtr<T>::operator->() const
{
    assert(m_ptr != 0);
    return m_ptr;
}

template <typename T>
T& SharedPtr<T>::operator*() const
{
    assert(m_ptr != 0);
    return *m_ptr;
}



#endif
