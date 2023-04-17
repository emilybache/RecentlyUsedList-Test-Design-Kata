#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "recently_used_list.h"
#include "InMemoryPageStorage.h"

using namespace std;


TEST(RecentlyUsedListTest, EmptyCache) {
    auto pageStorage = new InMemoryPageStorage();
    auto cache = new Cache(0);
    auto rul = new RecentlyUsedList(cache, pageStorage);
    rul->lookupPage(1);
    rul->lookupPage(2);
    rul->lookupPage(3);

    ASSERT_THAT(rul->getContents(), testing::IsEmpty());
    ASSERT_THAT(rul->getCurrentPages(), testing::IsEmpty());

    delete rul;
    delete cache;
    delete pageStorage;
}

TEST(RecentlyUsedListTest, Empty) {
    auto pageStorage = new InMemoryPageStorage();
    auto cache = new Cache(0);
    auto rul = new RecentlyUsedList(cache, pageStorage);
    ASSERT_THAT(rul->getContents(), testing::IsEmpty());

    delete rul;
    delete cache;
    delete pageStorage;
}

TEST(RecentlyUsedListTest, OneItem) {
    auto pageStorage = new InMemoryPageStorage();
    auto cache = new Cache(4);
    auto rul = new RecentlyUsedList(cache, pageStorage);
    rul->lookupPage(1);
    EXPECT_THAT(rul->getCurrentPages(), testing::ElementsAre(1));
    EXPECT_THAT(rul->getContents(), testing::ElementsAre("one"));

    delete rul;
    delete cache;
    delete pageStorage;
}

TEST(RecentlyUsedListTest, TwoItemsOrderedByInsertion) {
    auto pageStorage = new InMemoryPageStorage();
    auto cache = new Cache(4);
    auto rul = new RecentlyUsedList(cache, pageStorage);
    rul->lookupPage(1);
    rul->lookupPage(3);
    ASSERT_THAT(rul->getContents(), testing::ElementsAre("three", "one"));

    delete rul;
    delete cache;
    delete pageStorage;
}

TEST(RecentlyUsedListTest, DuplicateItemsAreMovedNotInserted) {
    auto pageStorage = new InMemoryPageStorage();
    auto cache = new Cache(4);
    auto rul = new RecentlyUsedList(cache, pageStorage);
    rul->lookupPage(1);
    rul->lookupPage(2);
    rul->lookupPage(1);
    ASSERT_THAT(rul->getContents(), testing::ElementsAre("one", "two"));

    delete rul;
    delete cache;
    delete pageStorage;
}


TEST(RecentlyUsedListTest, MoveFromBackToFront) {
    auto pageStorage = new InMemoryPageStorage();
    auto cache = new Cache(4);
    auto rul = new RecentlyUsedList(cache, pageStorage);
    rul->lookupPage(1);
    rul->lookupPage(2);
    rul->lookupPage(3);
    rul->lookupPage(1);
    rul->lookupPage(4);
    rul->lookupPage(5);
    auto expected = new vector<string>{"five", "four", "one", "three"};
    ASSERT_EQ(rul->getContents(), *expected);

    delete rul;
    delete cache;
    delete pageStorage;
}

TEST(RecentlyUsedListTest, RemoveOneNotFromBack) {
    auto pageStorage = new InMemoryPageStorage();
    auto cache = new Cache(3);
    auto rul = new RecentlyUsedList(cache, pageStorage);
    rul->lookupPage(1);
    rul->lookupPage(2);
    rul->lookupPage(3);
    rul->lookupPage(2);
    rul->lookupPage(4);
    rul->lookupPage(5);
    ASSERT_THAT(rul->getContents(), testing::ElementsAre("five", "four", "two"));

    delete rul;
    delete cache;
    delete pageStorage;
}

TEST(RecentlyUsedListTest, OneElementCapacity) {
    auto pageStorage = new InMemoryPageStorage();
    auto cache = new Cache(1);
    auto rul = new RecentlyUsedList(cache, pageStorage);
    rul->lookupPage(1);
    rul->lookupPage(2);
    rul->lookupPage(3);
    ASSERT_THAT(rul->getContents(), testing::ElementsAre("three"));

    delete rul;
    delete cache;
    delete pageStorage;
}