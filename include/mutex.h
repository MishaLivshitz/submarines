#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>
#include "MyException.h"
#include "utils.h"


namespace advcpp{

class CondVar;

class Mutex: private UnCopyable
{


public:
    Mutex(pthread_mutexattr_t* a_attr = 0) throw(MyException);
    ~Mutex(); //destroying locked mutex is undefind behavior

    void Lock() throw(MyException);
    void UnLock() throw(MyException);

    class MutexUtil;

private:
    friend class CondVar;
    pthread_mutex_t* getPmutex();

private:
    pthread_mutex_t m_mutex;

};

class Mutex::MutexUtil
{
public:
    MutexUtil(Mutex&);
    ~MutexUtil();
private:

Mutex& m_mutexRef;

};


} // advcpp


#endif