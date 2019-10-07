#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>
#include "Runnable.h"
#include "utils.h"
#include "ThreadCreateException.h"

namespace advcpp
{

class Thread: private UnCopyable
{

public:

    Thread(advcpp::Runnable& a_runnable) throw(advcpp::ThreadCreateException);
    ~Thread();

    bool operator== (pthread_t) const;

    void join();
    void detach();

private:
    static void* start(void*);


private:
    pthread_t m_thread;
    bool m_isJoined;
    bool m_isDetached;
};

}


#endif