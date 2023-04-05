#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "recently_used_list.h"
#include "InMemoryPageStorage.h"

using namespace std;


class RecentlyUsedListTest : public ::testing::Test {
private:
    PageStorage* pageStorage = new InMemoryPageStorage();
public:
    RecentlyUsedList* createRecentlyUsedList(int cacheSize){
        auto cache = new Cache(cacheSize);
        return new RecentlyUsedList(cache, pageStorage);
    }
    void lookupPages(RecentlyUsedList *rul, vector<int> pages) {
        for (int pageNumber: pages) {
            rul->lookupPage(pageNumber);
        }
    }
};

TEST_F(RecentlyUsedListTest, EmptyCache) {
    auto rul = createRecentlyUsedList(0);
    lookupPages(rul, {1, 2, 3});
    ASSERT_THAT(rul->getContents(), testing::IsEmpty());
    ASSERT_THAT(rul->getCurrentPages(), testing::IsEmpty());
}

TEST_F(RecentlyUsedListTest, Empty) {
    auto rul = createRecentlyUsedList(0);
    ASSERT_THAT(rul->getContents(), testing::IsEmpty());
}

TEST_F(RecentlyUsedListTest, OneItem) {
    auto rul = createRecentlyUsedList(4);
    rul->lookupPage(1);
    EXPECT_THAT(rul->getCurrentPages(), testing::ElementsAre(1));
    EXPECT_THAT(rul->getContents(), testing::ElementsAre("one"));
}

TEST_F(RecentlyUsedListTest, TwoItemsOrderedByInsertion) {
    auto rul = createRecentlyUsedList(4);
    lookupPages(rul, {1, 3});
    ASSERT_THAT(rul->getContents(), testing::ElementsAre("three", "one"));

}

TEST_F(RecentlyUsedListTest, DuplicateItemsAreMovedNotInserted) {
    auto rul = createRecentlyUsedList(4);
    lookupPages(rul, {1, 2, 1});
    ASSERT_THAT(rul->getContents(), testing::ElementsAre("one", "two"));
}

