
#include "mu_test.h"
#include "Thread.h"
#include "Increment.h"




UNIT(thread_create)

    size_t const size = 3000;
    Incrementor<int> inc(size);

    try
    {
        advcpp::Thread t(inc);
        advcpp::Thread t1(inc);
        advcpp::Thread t2(inc);
        t.join();
        t1.join();
        t2.join();
        ASSERT_EQUAL(inc.val(), size*3);
    }
    catch(advcpp::ThreadCreateException e)
    {
        std::cout << e.what()<<'\n';
    }


END_UNIT


TEST_SUITE(Thread class test)

    TEST(thread_create)

END_SUITE

