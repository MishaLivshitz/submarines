#include "Thread.h"
#include "cerrno"
#include <sstream>
#include <cassert>

namespace advcpp
{
    
Thread::Thread(Runnable& a_runnable) throw(ThreadCreateException)
: m_isJoined(false)
, m_isDetached(false)
{
    int e = pthread_create(&m_thread, 0, Thread::start, &a_runnable);

    if(0!=e)
    {
        std::stringstream err;
        err << "pthread_create failed with error: #" << e;
        throw EXCEPTION(ThreadCreateException, err.str().c_str());
    }
    
}

Thread::~Thread()
{
    assert(m_isDetached || m_isJoined);
}

void Thread::join()
{
    assert(!m_isDetached && !m_isJoined);

    int e = pthread_join(m_thread, 0);
    assert(e!=EINVAL && e!=ESRCH);
    m_isJoined = true;
    
}

void Thread::detach()
{
    assert(!m_isDetached && !m_isJoined);

    int e = pthread_detach(m_thread);
    assert(e!=EINVAL && e!=ESRCH);
    m_isDetached = true;

}

void* Thread::start(void* a_obj)
{
    Runnable* r = static_cast<Runnable*>(a_obj);
    r->run();

    return 0;
}

bool Thread::operator== (pthread_t a_rhs) const
{
    return pthread_equal(a_rhs, m_thread);
    //return a_rhs == m_thread;
}

}   // advcpp
