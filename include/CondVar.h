#ifndef CONDVAR_H
#define CONDVAR_H

#include <pthread.h>
#include "mutex.h"
#include "utils.h"

namespace advcpp{


class CondVar: public UnCopyable
{
public:
    CondVar(Mutex& a_mutex) throw (MyException);
    ~CondVar();

    void signal();

    template<typename P>
    void wait(P predicate);

private:

    pthread_mutex_t* m_pMutex;
    pthread_cond_t m_condVar;

};

template<typename P>
void CondVar::wait(P predicate)
{
    while(predicate())
    {
        pthread_cond_wait(&m_condVar, m_pMutex);
    }
    //consider exceptions
}


} //advcpp



#endif