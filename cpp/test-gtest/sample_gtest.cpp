#include <gtest/gtest.h>


#include "recently_used_list.h"

using namespace std;
using namespace ::testing;

TEST(RecentlyUsedListTest, fourPages)
{
    int length = 4;
    Queue* q = createQueue(length);

    Hash* hash = createHash(10);

    // Let us look up pages 1, 2, 3, 1, 4, 5
    LookupPage(q, hash, 1);
    LookupPage(q, hash, 2);
    LookupPage(q, hash, 3);
    LookupPage(q, hash, 1);
    LookupPage(q, hash, 4);
    LookupPage(q, hash, 5);

    int expected[] = {5, 4, 1, 3};
    int actual[] = {0, 0, 0, 0};
    currentPageOrder(q, actual, length);
    for (int i = 0; i < length ; i ++) {
        EXPECT_EQ(expected[i], actual[i]);
    }
}

TEST(RecentlyUsedList, removeOneNotFromBack)
{
    int length = 3;
    Queue* q = createQueue(length);

    Hash* hash = createHash(10);

    LookupPage(q, hash, 1);
    LookupPage(q, hash, 2);
    LookupPage(q, hash, 3);
    LookupPage(q, hash, 2);
    LookupPage(q, hash, 4);
    LookupPage(q, hash, 5);

    int expected[] = {5, 4, 2};
    int actual[] = {0, 0, 0};
    currentPageOrder(q, actual, length);
    for (int i = 0; i < length ; i ++) {
        EXPECT_EQ(expected[i], actual[i]);
    }
}

TEST(RecentlyUsedList, oneElement)
{
    Queue* q = createQueue(1);

    Hash* hash = createHash(10);

    LookupPage(q, hash, 1);
    LookupPage(q, hash, 2);
    LookupPage(q, hash, 3);

    int expected[] = {3};
    int actual[] = {0};
    int length = 1;
    currentPageOrder(q, actual, length);
    for (int i = 0; i < length ; i ++) {
        EXPECT_EQ(expected[i], actual[i]);
    }
}