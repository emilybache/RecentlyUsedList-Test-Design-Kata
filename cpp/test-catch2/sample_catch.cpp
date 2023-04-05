#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "recently_used_list.h"
#include "InMemoryPageStorage.h"

void lookupPages(RecentlyUsedList *rul, vector<int> pages) {
    for (int pageNumber: pages) {
        rul->lookupPage(pageNumber);
    }
}

TEST_CASE ("RecentlyUsedList") {
    auto pageStorage = new InMemoryPageStorage();
    auto cache = new Cache(0);
    auto rul = new RecentlyUsedList(cache, pageStorage);

    SECTION("empty list") {
        auto expected = new vector<string>();
        REQUIRE(rul->getContents() == *expected);
    }

    SECTION("one item") {
        cache->setCapacity(4);
        rul->lookupPage(1);
        auto expected = new vector<string>{"one"};
        REQUIRE_THAT(rul->getContents(), Catch::Matchers::Equals(*expected));
    }

    SECTION("order two items by most recently inserted") {
        cache->setCapacity(4);
        lookupPages(rul, {1, 2});
        auto expected = new vector<string>{"two", "one"};
        REQUIRE_THAT(rul->getContents(), Catch::Matchers::Equals(*expected));
    }

    SECTION("duplicate items are moved not inserted") {
        cache->setCapacity(4);
        lookupPages(rul, {1, 2, 1});
        auto expected = new vector<string>{"one", "two"};
        REQUIRE_THAT(rul->getContents(), Catch::Matchers::Equals(*expected));
    }

    SECTION("move from back to front") {
        cache->setCapacity(4);
        lookupPages(rul, {1, 2, 3, 1, 4, 5});
        auto expected = new vector<string>{"five", "four", "one", "three"};
        REQUIRE_THAT(rul->getContents(), Catch::Matchers::Equals(*expected));
    }

    SECTION("remove one not from back") {
        cache->setCapacity(3);
        lookupPages(rul, {1, 2, 3, 2, 4, 5});
        auto expected = new vector<string>{"five", "four", "two"};
        REQUIRE_THAT(rul->getContents(), Catch::Matchers::Equals(*expected));
    }

    SECTION("one element capacity") {
        cache->setCapacity(1);
        lookupPages(rul, {1, 2, 3, 2, 4, 5});
        auto expected = new vector<string>{"five"};
        REQUIRE_THAT(rul->getContents(), Catch::Matchers::Equals(*expected));
    }
}


