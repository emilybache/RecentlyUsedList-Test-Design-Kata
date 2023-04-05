#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "recently_used_list.h"

using namespace std;

class RecentlyUsedListTest : public ::testing::Test {
public:
    RecentlyUsedList* rul = new RecentlyUsedList();
};

TEST_F(RecentlyUsedListTest, Empty) {
    auto expected = new vector<string>();
    ASSERT_EQ(rul->getContents(), *expected);
}

TEST_F(RecentlyUsedListTest, OneItem) {
    rul->insert("item");
    auto expected = new vector<string>{"item"};
    ASSERT_EQ(rul->getContents(), *expected);
}

TEST_F(RecentlyUsedListTest, TwoItemsOrderedByInsertion) {
    rul->insert("item1");
    rul->insert("item2");
    auto expected = new vector<string>{"item2", "item1"};
    ASSERT_EQ(rul->getContents(), *expected);
}

TEST_F(RecentlyUsedListTest, DuplicateItemsAreMovedNotInserted) {
    rul->insert("item1");
    rul->insert("item2");
    rul->insert("item1");
    auto expected = new vector<string>{"item1", "item2"};
    ASSERT_EQ(rul->getContents(), *expected);
}

TEST_F(RecentlyUsedListTest, EmptyStringsAreNotAllowed) {
    rul->insert("");
    auto expected = new vector<string>{};
    ASSERT_EQ(rul->getContents(), *expected);
}