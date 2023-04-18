#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "recently_used_list.h"
#include "InMemoryPageStorage.h"

using namespace std;

class RecentlyUsedListTest : public testing::Test {
protected:
    InMemoryPageStorage* pageStorage;
    Cache* cache;
    RecentlyUsedList* recentlyUsedList;
    void SetUp() override {
        pageStorage = new InMemoryPageStorage();
        cache = new Cache(0);
        recentlyUsedList = new RecentlyUsedList(cache, pageStorage);
    }
    void TearDown() override {
        delete recentlyUsedList;
        delete cache;
        delete pageStorage;
    }

    void lookupPages(vector<int> pagesToLookup) {
        for (int pageNumber : pagesToLookup) {
            recentlyUsedList->lookupPage(pageNumber);
        }
    }
};

TEST_F(RecentlyUsedListTest, EmptyCache) {
    int cacheSize = 0;
    cache->setCapacity(cacheSize);
    auto pagesToLookup = {1,2,3};
    lookupPages(pagesToLookup);

    ASSERT_THAT(recentlyUsedList->getContents(), testing::IsEmpty());
    ASSERT_THAT(recentlyUsedList->getCurrentPages(), testing::IsEmpty());
}

TEST_F(RecentlyUsedListTest, Empty) {
    int cacheSize = 0;
    cache->setCapacity(cacheSize);
    
    ASSERT_THAT(recentlyUsedList->getContents(), testing::IsEmpty());
}

TEST_F(RecentlyUsedListTest, OneItem) {
    int cacheSize = 4;
    cache->setCapacity(cacheSize);
    
    recentlyUsedList->lookupPage(1);
    EXPECT_THAT(recentlyUsedList->getCurrentPages(), testing::ElementsAre(1));
    EXPECT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("one"));
}

TEST_F(RecentlyUsedListTest, TwoItemsOrderedByInsertion) {
    int cacheSize = 4;
    cache->setCapacity(cacheSize);
    auto pagesToLookup = {1,3};
    lookupPages(pagesToLookup);

    ASSERT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("three", "one"));
}

TEST_F(RecentlyUsedListTest, DuplicateItemsAreMovedNotInserted) {
    int cacheSize = 4;
    cache->setCapacity(cacheSize);
    auto pagesToLookup = {1,2,1};
    lookupPages(pagesToLookup);

    ASSERT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("one", "two"));
}


TEST_F(RecentlyUsedListTest, MoveFromBackToFront) {
    int cacheSize = 4;
    cache->setCapacity(cacheSize);
    auto pagesToLookup = {1,2,3,1,4,5};
    lookupPages(pagesToLookup);

    ASSERT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("five", "four", "one", "three"));

}

TEST_F(RecentlyUsedListTest, RemoveOneNotFromBack) {
    int cacheSize = 3;
    cache->setCapacity(cacheSize);
    auto pagesToLookup = {1,2,3,2,4,5};
    lookupPages(pagesToLookup);
    ASSERT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("five", "four", "two"));
}

TEST_F(RecentlyUsedListTest, OneElementCapacity) {
    int cacheSize = 1;
    cache->setCapacity(cacheSize);
    auto pagesToLookup = {1,2,3};
    lookupPages(pagesToLookup);

    ASSERT_THAT(recentlyUsedList->getContents(), testing::ElementsAre("three"));
}