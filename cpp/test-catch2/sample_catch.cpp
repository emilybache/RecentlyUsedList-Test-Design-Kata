#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "recently_used_list.h"
#include "InMemoryPageStorage.h"

TEST_CASE ("RecentlyUsedList") {
    auto pageStorage = new InMemoryPageStorage();
    SECTION("empty list") {
        auto cache = new Cache(0);
        auto rul = new RecentlyUsedList(cache, pageStorage);
        auto expected = new vector<string>();
        REQUIRE(rul->getContents() == *expected);
    }
    SECTION("one item"){
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);
        rul->lookupPage(1);
        auto expected = new vector<string>{"one"};
        REQUIRE_THAT(rul->getContents(), Catch::Matchers::Equals(*expected));
    }

    SECTION("order two items by most recently inserted"){
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);

        rul->lookupPage(1);
        rul->lookupPage(2);
        auto expected = new vector<string>{"two", "one"};
        REQUIRE(rul->getContents() == *expected);
    }

    SECTION("duplicate items are moved not inserted"){
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);

        rul->lookupPage(1);
        rul->lookupPage(2);
        rul->lookupPage(1);
        auto expected = new vector<string>{"one", "two"};
        REQUIRE(rul->getContents() == *expected);
    }



}


