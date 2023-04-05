#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "recently_used_list.h"

using namespace std;

class RecentlyUsedListTest : public ::testing::Test {
public:
    RecentlyUsedList* rul = new RecentlyUsedList();
};

TEST_F(RecentlyUsedListTest, Empty) {
    ASSERT_THAT(rul->getContents(), testing::IsEmpty());
}

TEST_F(RecentlyUsedListTest, OneItem) {
    rul->insert("item");
    ASSERT_THAT(rul->getContents(), testing::ElementsAre("item"));
}

TEST_F(RecentlyUsedListTest, TwoItemsOrderedByInsertion) {
    rul->insert("item1");
    rul->insert("item2");
    ASSERT_THAT(rul->getContents(), testing::ElementsAre("item2", "item1"));

}

TEST_F(RecentlyUsedListTest, DuplicateItemsAreMovedNotInserted) {
    rul->insert("item1");
    rul->insert("item2");
    rul->insert("item1");
    ASSERT_THAT(rul->getContents(), testing::ElementsAre("item1", "item2"));
}

TEST_F(RecentlyUsedListTest, EmptyStringsAreNotAllowed) {
    rul->insert("");
    ASSERT_THAT(rul->getContents(), testing::IsEmpty());
}