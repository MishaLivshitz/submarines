
#include "mutex.h"
#include "cassert"
#include "cerrno"
#include <sstream>

namespace advcpp{


class MutexUtil;

Mutex::Mutex(pthread_mutexattr_t* a_attr) throw(MyException)
{
    int e = pthread_mutex_init(&m_mutex, a_attr);
    if(0 != e)
    {
        std::stringstream err;
        err << "pthread_mutex_init failed with error: #" << e;
        throw EXCEPTION(MyException, err.str().c_str());
    }
}

Mutex::~Mutex()
{
    int e;
    e = pthread_mutex_destroy(&m_mutex);
    assert(e != EINVAL);
    assert(e != EBUSY);
    
}

void Mutex::Lock() throw(MyException)
{
    int e;
    e = pthread_mutex_lock(&m_mutex);
    assert(e != EBUSY);
    assert(e != EINVAL);

    // if(e == EDEADLK)
    // {
    //     throw EXCEPTION(MyException, "Already owned the mutex");
    // }
}

void Mutex::UnLock() throw(MyException)
{
    int e;
    e = pthread_mutex_unlock(&m_mutex);
    assert(e != EBUSY);
    assert(e != EINVAL);

    // if(e == EPERM)
    // {
    //     throw EXCEPTION(MyException, "Does not own the mutex");
    // }
}

pthread_mutex_t* Mutex::getPmutex()
{
    return &m_mutex;
}


Mutex::MutexUtil::MutexUtil(Mutex& a_mtxRef)
:m_mutexRef(a_mtxRef)
{
    m_mutexRef.Lock();
}

Mutex::MutexUtil::~MutexUtil()
{
    m_mutexRef.UnLock();
}


} /*advcpp */