#include "mu_test.h"
#include "SubmarinesTable.h"

UNIT(Table_test)

    
    SubMarinesTable t;
    t.addSubmarine(std::make_pair<size_t,size_t>(4,4),SubMarinesTable::DOWN, SharedPtr<Submarine>(new Submarine(3)));
    t.addSubmarine(std::make_pair<size_t,size_t>(2,1),SubMarinesTable::RIGHT, SharedPtr<Submarine>(new Submarine(5)));
    
    ASSERT_THAT(t.handleShot(2,4));
    ASSERT_THAT(!t.handleShot(2,6));
    ASSERT_EQUAL(t[2][4].first,SubMarinesTable::DEAD);
    ASSERT_EQUAL(t[2][4].second->isDead(), false);
    ASSERT_THAT(!t.handleShot(7,8));
    ASSERT_EQUAL(t[7][8].first,SubMarinesTable::DIRTY);

    t.print();
END_UNIT

UNIT(kill_test)

    SubMarinesTable t;
    std::pair<size_t,size_t> start = std::make_pair<size_t,size_t>(4,4);
    size_t length = 3;
    t.addSubmarine(start, SubMarinesTable::DOWN, SharedPtr<Submarine>(new Submarine(length)));
    

    t.print();

    while(start.first < 7)
    {
        ASSERT_EQUAL(t[4][4].second->isDead(), false);
        t.handleShot(start.first,start.second);
        start.first+=1;
    }
    
    t.print();

    ASSERT_EQUAL(t[4][4].second->isDead(), true);

END_UNIT

UNIT(edge_submarine)


    SubMarinesTable t;
    std::pair<size_t,size_t> start = std::make_pair<size_t,size_t>(9,0);
    t.addSubmarine(start, SubMarinesTable::RIGHT, SharedPtr<Submarine>(new Submarine(5)));
    t.print();

END_UNIT

TEST_SUITE(Test of Table unit)

    IGNORE_TEST(Table_test)
    IGNORE_TEST(kill_test)
    TEST(edge_submarine)

END_SUITE