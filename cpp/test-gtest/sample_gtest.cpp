#include <gtest/gtest.h>

#include "recently_used_list.h"

using namespace std;

TEST(RecentlyUsedList, Empty) {
    auto rul = new RecentlyUsedList();
    auto expected = new vector<string>();
    ASSERT_EQ(rul->getContents(), *expected);
}

TEST(RecentlyUsedList, OneItem) {
    auto rul = new RecentlyUsedList();
    rul->insert("item");
    auto expected = new vector<string>{"item"};
    ASSERT_EQ(rul->getContents(), *expected);
}

TEST(RecentlyUsedList, TwoItemsOrderedByInsertion) {
    auto rul = new RecentlyUsedList();
    rul->insert("item1");
    rul->insert("item2");
    auto expected = new vector<string>{"item2", "item1"};
    ASSERT_EQ(rul->getContents(), *expected);
}

TEST(RecentlyUsedList, DuplicateItemsAreMovedNotInserted) {
    auto rul = new RecentlyUsedList();
    rul->insert("item1");
    rul->insert("item2");
    rul->insert("item1");
    auto expected = new vector<string>{"item1", "item2"};
    ASSERT_EQ(rul->getContents(), *expected);
}

TEST(RecentlyUsedList, EmptyStringsAreNotAllowed) {
    auto rul = new RecentlyUsedList();
    rul->insert("");
    auto expected = new vector<string>{};
    ASSERT_EQ(rul->getContents(), *expected);
}