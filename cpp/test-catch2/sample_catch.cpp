#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "recently_used_list.h"

TEST_CASE ("RecentlyUsedList") {
    auto rul = new RecentlyUsedList();
    SECTION("empty list") {
        auto expected = new vector<string>();
        REQUIRE(rul->getContents() == *expected);
    }
    SECTION("one item"){
        rul->insert("item");
        auto expected = new vector<string>{"item"};
        REQUIRE(rul->getContents() == *expected);
    }

    SECTION("order two items by most recently inserted"){
        rul->insert("item1");
        rul->insert("item2");
        auto expected = new vector<string>{"item2", "item1"};
        REQUIRE(rul->getContents() == *expected);
    }

    SECTION("duplicate items are moved not inserted"){
        rul->insert("item1");
        rul->insert("item2");
        rul->insert("item1");
        auto expected = new vector<string>{"item1", "item2"};
        REQUIRE(rul->getContents() == *expected);
    }

    SECTION("empty strings are not allowed"){
        rul->insert("");
        auto expected = new vector<string>{};
        REQUIRE(rul->getContents() == *expected);
    }

}


