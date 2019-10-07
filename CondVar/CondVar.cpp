#include "CondVar.h"
#include <cassert>
#include "cerrno"
#include "MyException.h"
#include <sstream>

namespace advcpp{


CondVar::CondVar(Mutex& a_mutex) throw (MyException)
:m_pMutex(a_mutex.getPmutex())
{
    int e = pthread_cond_init(&m_condVar,0);
    
    if(e!=0)
    {
        std::stringstream err;
        err << "pthread_cond_init failed with error: #" << e;
        throw EXCEPTION(MyException, err.str().c_str());
    }
}

CondVar::~CondVar()
{
    int e = pthread_cond_destroy(&m_condVar);
    assert(e != EINVAL && e != EBUSY);
   
}

void CondVar::signal()
{
    int e = pthread_cond_signal(&m_condVar);
    assert(e == 0);
}

}// advcpp