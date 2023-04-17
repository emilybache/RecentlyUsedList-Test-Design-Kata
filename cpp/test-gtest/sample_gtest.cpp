#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "recently_used_list.h"
#include "InMemoryPageStorage.h"

using namespace std;


class RecentlyUsedListTest : public ::testing::Test {
protected:
    PageStorage* pageStorage;
    Cache* cache;
    RecentlyUsedList* recentlyUsedList;
    void SetUp() override {
        pageStorage = new InMemoryPageStorage();

    }
    void TearDown() override {
        delete recentlyUsedList;
        delete cache;
        delete pageStorage;
    }
public:
    RecentlyUsedList* createRecentlyUsedList(int cacheSize){
        cache = new Cache(cacheSize);
        recentlyUsedList = new RecentlyUsedList(cache, pageStorage);
        return recentlyUsedList;
    }

    void lookupPages(RecentlyUsedList *recentlyUsedList, vector<int> pages) {
        for (int pageNumber: pages) {
            recentlyUsedList->lookupPage(pageNumber);
        }
    }

};


TEST_F(RecentlyUsedListTest, EmptyCache) {
    createRecentlyUsedList(0);
    lookupPages(recentlyUsedList, {1, 2, 3});
    ASSERT_THAT(recentlyUsedList->getContents(), testing::IsEmpty());
    ASSERT_THAT(recentlyUsedList->getCurrentPages(), testing::IsEmpty());
}

TEST_F(RecentlyUsedListTest, Empty) {
    createRecentlyUsedList(0);
    ASSERT_THAT(recentlyUsedList->getContents(), testing::IsEmpty());
}

TEST_F(RecentlyUsedListTest, OneItem) {
    createRecentlyUsedList(4);
    recentlyUsedList->lookupPage(1);
    EXPECT_THAT(recentlyUsedList->getCurrentPages(), testing::ElementsAre(1));
    EXPECT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("one"));
}

TEST_F(RecentlyUsedListTest, TwoItemsOrderedByInsertion) {
    createRecentlyUsedList(4);
    lookupPages(recentlyUsedList, {1, 3});
    ASSERT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("three", "one"));

}

TEST_F(RecentlyUsedListTest, DuplicateItemsAreMovedNotInserted) {
    createRecentlyUsedList(4);
    lookupPages(recentlyUsedList, {1, 2, 1});
    ASSERT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("one", "two"));
}


TEST_F(RecentlyUsedListTest, MoveFromBackToFront) {
    createRecentlyUsedList(4);
    lookupPages(recentlyUsedList, {1, 2, 3,1,4,5});
    ASSERT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("five", "four", "one", "three"));
}

TEST_F(RecentlyUsedListTest, RemoveOneNotFromBack) {
    createRecentlyUsedList(3);
    lookupPages(recentlyUsedList, {1, 2, 3, 2, 4, 5});
    ASSERT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("five", "four", "two"));
}

TEST_F(RecentlyUsedListTest, OneElementCapacity) {
    createRecentlyUsedList(1);
    lookupPages(recentlyUsedList, {1, 2, 3, 2, 4, 3});
    ASSERT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("three"));
}