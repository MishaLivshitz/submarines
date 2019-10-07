
#include "mu_test.h"
#include <pthread.h>

#include "mutex.h"
#include "Increment.h"
#include "AtomicInc.h"
#include "AtomicVal.h"
#include "MyException.h"


struct Params
{
    advcpp::Mutex m_mutex;
    int* num;
    int size;
};

void* t1(void* _param)
{
    Params* p= static_cast<Params*>(_param);

    for(int i = 0; i < p->size; ++i)
    {   
        
        p->m_mutex.Lock();
        std::cout << *p->num << " t1 \n";
        ++(*p->num);
        p->m_mutex.UnLock();
    
    }
    return 0;
}

void* t2(void* _param)
{
    Params* p= static_cast<Params*>(_param);

    for(int i = 0; i < p->size; ++i)
    {   
        p->m_mutex.Lock();
        std::cout << *p->num << " t2 \n";
        --(*p->num);
        p->m_mutex.UnLock();
    }

    return 0;
}

UNIT(create)

   
    int const size = 100000;
    int i = 0;
    pthread_t thread[2];

    try{
        Params params;
        params.num = &i;
        params.size = size;
        pthread_create(&thread[0], 0, t1, &params);
        pthread_create(&thread[1], 0, t2, &params);
        pthread_join(thread[0], 0);
        pthread_join(thread[1], 0);
    }
    catch (MyException& e)
    {
        std::cerr << e.what() <<'\n';
    }
    



    ASSERT_EQUAL(i,0);

END_UNIT


UNIT(with_class)

    try{

    size_t const size = 200000;
    Incrementor<int> inc(size);

    pthread_t thread[2];

    pthread_create(&thread[0], 0, Incrementor<int>::IncActivator, &inc);
    pthread_create(&thread[1], 0, Incrementor<int>::IncActivator, &inc);

    pthread_join(thread[0], 0);
    pthread_join(thread[1], 0);

    ASSERT_EQUAL(inc.val(),size*2);
    }
    catch (MyException& e)
    {
        std::cerr << e.what() <<'\n';
    }

END_UNIT

UNIT(with_atomic_class)


    size_t const size = 200000;
    advcpp::AtomicInc<int> inc(size);

    pthread_t thread[2];

    pthread_create(&thread[0], 0, advcpp::AtomicInc<int>::IncActivator, &inc);
    pthread_create(&thread[1], 0, advcpp::AtomicInc<int>::IncActivator, &inc);

    pthread_join(thread[0], 0);
    pthread_join(thread[1], 0);

    ASSERT_EQUAL(inc.val(), size*2);

END_UNIT


TEST_SUITE(Mutex Test)

    TEST(create)
    TEST(with_class)
    TEST(with_atomic_class)

END_SUITE
