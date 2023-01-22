#include <gtest/gtest.h>


#include "recently_used_list.h"

using namespace std;
using namespace ::testing;

class RecentlyUsedListTest : public ::testing::Test {
public:
    Queue* q;
    Hash* hash;

    void SetUp() override {
        hash = createHash(10);
    }

    void lookupPages(int pages[], int pagesCount) const {
        for (int i = 0; i < pagesCount; ++i) {
            LookupPage(q, hash, pages[i]);
        }
    }

    void ExpectQueueContents(int expected[], int length) const {
        int actual[length];
        memset(actual, 0, length*sizeof(expected[0]));
        currentPageOrder(q, actual, length);
        for (int i = 0; i < length ; i ++) {
            EXPECT_EQ(expected[i], actual[i]);
        }
    }
};

TEST_F(RecentlyUsedListTest, fourPages)
{
    // Arrange
    int length = 4;
    q = createQueue(length);

    // Act
    int pages[] = {1, 2, 3, 1, 4, 5};
    lookupPages(pages, 6);

    // Assert
    int expected[] = {5, 4, 1, 3};
    ExpectQueueContents(expected, length);
}

TEST_F(RecentlyUsedListTest, removeOneNotFromBack)
{
    // Arrange
    int length = 3;
    q = createQueue(length);

    // Act
    int pages[] = {1, 2, 3, 2, 4, 5};
    lookupPages(pages, 6);

    // Assert
    int expected[] = {5, 4, 2};
    ExpectQueueContents(expected, length);
}

TEST_F(RecentlyUsedListTest, oneElement)
{
    // Arrange
    int length = 1;
    q = createQueue(length);

    // Act
    int pages[] = {1, 2, 3};
    lookupPages(pages, 3);

    // Assert
    int expected[] = {3};
    ExpectQueueContents(expected, length);
}