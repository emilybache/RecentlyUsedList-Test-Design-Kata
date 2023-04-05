#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "recently_used_list.h"
#include "InMemoryPageStorage.h"

TEST_CASE ("RecentlyUsedList") {
    SECTION("empty cache") {
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(0);
        auto rul = new RecentlyUsedList(cache, pageStorage);
        auto expected = new vector<string>();
        REQUIRE(rul->getContents() == *expected);
    }
    SECTION("empty list") {
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);
        auto expected = new vector<string>();
        REQUIRE(rul->getContents() == *expected);
    }
    SECTION("one item"){
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);
        rul->lookupPage(1);
        auto expected = new vector<string>{"one"};
        REQUIRE_THAT(rul->getContents(), Catch::Matchers::Equals(*expected));
    }

    SECTION("order two items by most recently inserted"){
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);

        rul->lookupPage(1);
        rul->lookupPage(2);
        auto expected = new vector<string>{"two", "one"};
        REQUIRE(rul->getContents() == *expected);
    }

    SECTION("duplicate items are moved not inserted"){
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);

        rul->lookupPage(1);
        rul->lookupPage(2);
        rul->lookupPage(1);
        auto expected = new vector<string>{"one", "two"};
        REQUIRE(rul->getContents() == *expected);
    }
    SECTION("move from back to front"){
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
        REQUIRE(rul->getContents() == *expected);
    }

    SECTION("remove one not from back"){
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(3);
        auto rul = new RecentlyUsedList(cache, pageStorage);

        rul->lookupPage(1);
        rul->lookupPage(2);
        rul->lookupPage(3);
        rul->lookupPage(2);
        rul->lookupPage(4);
        rul->lookupPage(5);
        auto expected = new vector<string>{"five", "four", "two"};
        REQUIRE(rul->getContents() == *expected);
    }

    SECTION("one element capacity"){
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(1);
        auto rul = new RecentlyUsedList(cache, pageStorage);

        rul->lookupPage(1);
        rul->lookupPage(2);
        rul->lookupPage(3);
        rul->lookupPage(2);
        rul->lookupPage(4);
        rul->lookupPage(5);
        auto expected = new vector<string>{"five"};
        REQUIRE(rul->getContents() == *expected);
    }
}


