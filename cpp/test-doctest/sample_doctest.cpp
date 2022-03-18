#include "ApprovalTests.hpp"
#include "doctest/doctest.h"


#include "recently_used_list.h"

static Queue *createAndFillQueue(Hash *hash, int queue_length, int *pages, int pages_length) {
    Queue* q = createQueue(queue_length);
    for (int i = 0; i < pages_length; i++) {
        LookupPage(q, hash, pages[i]);
    }
    return q;
}

void EXPECT_QUEUE_CONTENTS(int expected[], int actual[], int length)
{
    for (int i = 0; i < length ; i ++)
    {
        CHECK_MESSAGE(expected[i] == actual[i], "difference at index ", i);
    }
}

TEST_CASE ("Recently Used List")
{
    Hash* hash = createHash(10);

    SUBCASE("Four elements") {
        int queue_length = 4;
        int pages[] = {1,2,3,1,4,5};
        int pages_length = 6;

        Queue *q = createAndFillQueue(hash, queue_length, pages, pages_length);

        int expected[] = {5, 4, 1, 3};
        int actual[] = {0, 0, 0, 0};
        currentPageOrder(q, actual, queue_length);
        EXPECT_QUEUE_CONTENTS(expected, actual, queue_length);
    }

    SUBCASE("removeOneNotFromBack")
    {
        int queue_length = 3;

        int pages[] = {1,2,3,2,4,5};
        int pages_length = 6;

        Queue* q = createAndFillQueue(hash, queue_length, pages, pages_length);

        int expected[] = {5, 4, 2};
        int actual[] = {0, 0, 0};
        currentPageOrder(q, actual, queue_length);
        EXPECT_QUEUE_CONTENTS(expected, actual, queue_length);
    }

    SUBCASE("oneElement")
    {
        int queue_length = 1;
        int pages[] = {1,2,3};
        int pages_length = 3;

        Queue* q = createAndFillQueue(hash, queue_length, pages, pages_length);

        int expected[] = {3};
        int actual[] = {0};
        currentPageOrder(q, actual, queue_length);
        EXPECT_QUEUE_CONTENTS(expected, actual, queue_length);
    }
}






