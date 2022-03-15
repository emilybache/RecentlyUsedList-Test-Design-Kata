#include <gtest/gtest.h>

#include "recently_used_list.h"

using namespace std;
using namespace ::testing;


class RecentlyUsedListTest : public Test {
protected:
    void SetUp() override {
        hash = createHash(10);
    }
    Queue* q;
    Hash* hash;

    void LookupPages(int pages[], int length)
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
            EXPECT_EQ(expected[i], actual[i]);
        }
    }
};


TEST_F(RecentlyUsedListTest, fourPages)
{
    int length = 4;
    q = createQueue(length);

    int pages[] = {1,2,3,1,4,5};
    LookupPages(pages, 6);

    int expected[] = {5, 4, 1, 3};
    int actual[] = {0, 0, 0, 0};
    currentPageOrder(q, actual, length);
    EXPECT_QUEUE_CONTENTS(expected, actual, length);
}

TEST_F(RecentlyUsedListTest, removeOneNotFromBack)
{
    int length = 3;
    q = createQueue(length);

    int pages[] = {1,2,3,2,4,5};
    LookupPages(pages, 6);

    int expected[] = {5, 4, 2};
    int actual[] = {0, 0, 0};
    currentPageOrder(q, actual, length);
    EXPECT_QUEUE_CONTENTS(expected, actual, length);
}

TEST_F(RecentlyUsedListTest, oneElement)
{
    int length = 1;
    q = createQueue(length);

    int pages[] = {1,2,3};
    LookupPages(pages, 3);

    int expected[] = {3};
    int actual[] = {0};
    currentPageOrder(q, actual, length);
    EXPECT_QUEUE_CONTENTS(expected, actual, length);
}