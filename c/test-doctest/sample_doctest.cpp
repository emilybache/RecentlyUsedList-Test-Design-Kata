#include "doctest/doctest.h"


#include "recently_used_list.h"

void lookupPages(Queue* q, Hash* hash, int pages[], int pagesCount) {
    for (int i = 0; i < pagesCount; ++i) {
        LookupPage(q, hash, pages[i]);
    }
}

void ExpectQueueContents(Queue* q, int expected[], int length) {
    int actual[length];
    memset(actual, 0, length*sizeof(expected[0]));
    currentPageOrder(q, actual, length);
    for (int i = 0; i < length ; i ++) {
        CHECK(expected[i] == actual[i]);
    }
}

TEST_CASE ("Recently Used List") {
    Hash* hash = createHash(10);
    SUBCASE("Four elements") {
        int length = 4;
        Queue* q = createQueue(length);

        int pages[] = {1, 2, 3, 1, 4, 5};
        lookupPages(q, hash, pages, 6);


        int expected[] = {5, 4, 1, 3};
        ExpectQueueContents(q, expected, length);
    }

    SUBCASE("removeOneNotFromBack")
    {
        int length = 3;
        Queue* q = createQueue(length);

        int pages[] = {1, 2, 3, 2, 4, 5};
        lookupPages(q, hash, pages, 6);


        int expected[] = {5, 4, 2};
        ExpectQueueContents(q, expected, length);

    }

    SUBCASE("oneElement")
    {
        int length = 1;
        Queue* q = createQueue(length);

        int pages[] = {1, 2, 3};
        lookupPages(q, hash, pages, 3);


        int expected[] = {3};
        ExpectQueueContents(q, expected, length);
    }
}


