#include "ApprovalTests.hpp"
#include "doctest/doctest.h"


#include "recently_used_list.h"


void LookupPages(Queue* q, Hash* hash, int pages[], int length)
{
    for (int i = 0; i < length ; i ++)
    {
        LookupPage(q, hash, pages[i]);
    }
}

void EXPECT_QUEUE_CONTENTS(int expected[], int actual[], int length)
{
    for (int i = 0; i < length ; i ++)
    {
        CHECK_MESSAGE(expected[i] == actual[i], "difference at index ", i);
    }
}

TEST_CASE ("Recently Used List") {
    Hash* hash = createHash(10);



    SUBCASE("Four elements") {
        int length = 4;
        Queue* q = createQueue(length);
        int pages[] = {1,2,3,1,4,5};
        LookupPages(q, hash, pages, 6);

        int expected[] = {5, 4, 1, 3};
        int actual[] = {0, 0, 0, 0};
        currentPageOrder(q, actual, length);
        EXPECT_QUEUE_CONTENTS(expected, actual, length);
    }

    SUBCASE("removeOneNotFromBack")
    {
        int length = 3;
        Queue* q = createQueue(length);

        int pages[] = {1,2,3,2,4,5};
        LookupPages(q, hash, pages, 6);

        int expected[] = {5, 4, 2};
        int actual[] = {0, 0, 0};
        currentPageOrder(q, actual, length);
        EXPECT_QUEUE_CONTENTS(expected, actual, length);
    }

    SUBCASE("oneElement")
    {
        Queue* q = createQueue(1);
        int length = 1;

        int pages[] = {1,2,3};
        LookupPages(q, hash, pages, 3);

        int expected[] = {3};
        int actual[] = {0};
        currentPageOrder(q, actual, length);
        EXPECT_QUEUE_CONTENTS(expected, actual, length);
    }
}


