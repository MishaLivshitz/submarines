#ifndef WAITABLE_QUEUE_H
#define WAITABLE_QUEUE_H

#include "mutex.h"
#include "CondVar.h"
#include <queue>

namespace advcpp{


template <typename T>
class WaitableQueue: private std::queue<T>
{

public:

    WaitableQueue();

    void enqueue(T const& a_item);
    void dequeue(T& a_item);
    size_t size() const;
    bool empty() const;

private:
    bool isEmpty();

private:

    class Predicate;
    mutable Mutex m_locker;
    CondVar m_condVar;
};


template <typename T>
class WaitableQueue<T>::Predicate
{
public:
    Predicate(WaitableQueue<T>& a_wq);
    bool operator()() const;

    private:
        WaitableQueue<T>& m_wq; 
};

template <typename T>
WaitableQueue<T>::WaitableQueue()
:m_condVar(m_locker)
{

}

template <typename T>
void WaitableQueue<T>::enqueue(T const& a_item)
{
    
    {
        Mutex::MutexUtil m(m_locker);    
        this->push(a_item);
		m_condVar.signal();
    }

    
    
}

template <typename T>
void WaitableQueue<T>::dequeue(T& a_item)
{
    Mutex::MutexUtil m(m_locker);
    m_condVar.wait(Predicate(*this));
    a_item = this->front();
    this->pop();
}

template <typename T>
size_t WaitableQueue<T>::size() const
{
    size_t size;
    {
        Mutex::MutexUtil m(m_locker);
        size = std::queue<T>::size();
    }

    return size;
}

template <typename T>
bool WaitableQueue<T>::empty() const
{
    bool r;
    {
        Mutex::MutexUtil m(m_locker);
        r = isEmpty();
    }   

    return r; 
}

template <typename T>
bool WaitableQueue<T>::isEmpty()
{
    return std::queue<T>::empty();
}

template <typename T>
bool WaitableQueue<T>::Predicate::operator()() const
{
    return m_wq.isEmpty();
}

template <typename T>
WaitableQueue<T>::Predicate::Predicate(WaitableQueue<T>& a_wq)
: m_wq(a_wq)
{

}

} // advcpp

#endif
