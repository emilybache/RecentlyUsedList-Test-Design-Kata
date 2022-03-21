
#include "doctest/doctest.h"
#include "recently_used_list.h"


TEST_CASE ("RecentlyUsedListDoctest") {
    SUBCASE("empty list") {
        auto rul = new RecentlyUsedList();
        auto expected = new vector<string>();
        REQUIRE(rul->getContents() == *expected);
    }

    SUBCASE("one item"){
        auto rul = new RecentlyUsedList();
        rul->insert("item");
        auto expected = new vector<string>{"item"};
        REQUIRE(rul->getContents() == *expected);
    }

    SUBCASE("order two items by most recently inserted"){
        auto rul = new RecentlyUsedList();
        rul->insert("item1");
        rul->insert("item2");
        auto expected = new vector<string>{"item2", "item1"};
        REQUIRE(rul->getContents() == *expected);
    }

    SUBCASE("duplicate items are moved not inserted"){
        auto rul = new RecentlyUsedList();
        rul->insert("item1");
        rul->insert("item2");
        rul->insert("item1");
        auto expected = new vector<string>{"item1", "item2"};
        REQUIRE(rul->getContents() == *expected);
    }

    SUBCASE("empty strings are not allowed"){
        auto rul = new RecentlyUsedList();
        rul->insert("");
        auto expected = new vector<string>{};
        REQUIRE(rul->getContents() == *expected);
    }

}


