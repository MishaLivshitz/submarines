#include "mu_test.h"
#include "Submarine.h"

UNIT(submarine_test)

    const size_t size = 5;
    Submarine s(size);

    while (!s.isDead())
    {
        ASSERT_THAT(!s.isDead());
        s.setHit();
    }

    ASSERT_THAT(s.isDead());


END_UNIT

TEST_SUITE(Test of submarine unit)

    TEST(submarine_test)

END_SUITE