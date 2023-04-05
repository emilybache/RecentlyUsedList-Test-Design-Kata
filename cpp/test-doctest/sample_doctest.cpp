
#include <sstream>
#include "doctest/doctest.h"
#include "recently_used_list.h"
#include "InMemoryPageStorage.h"

// This code is needed so you can see the contents of the vectors of items when the tests fail
namespace doctest
{
    template <typename T>
    struct StringMaker<std::vector<T> >
    {
        static String convert(const std::vector<T>& in) {
            std::ostringstream oss;

            oss << "[";
            for(typename std::vector<T>::const_iterator it = in.begin(); it != in.end(); ++it)
                oss << *it << ", ";
            oss << "]";

            return oss.str().c_str();
        }
    };
}

TEST_CASE ("RecentlyUsedListDoctest") {
    SUBCASE("empty cache") {
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(0);
        auto rul = new RecentlyUsedList(cache, pageStorage);
        auto expected = new vector<string>();
        REQUIRE(rul->getContents() == *expected);
    }
    SUBCASE("empty list") {
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);
        auto expected = new vector<string>();
        REQUIRE(rul->getContents() == *expected);
    }

    SUBCASE("one item"){
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);
        rul->lookupPage(1);
        auto expected = new vector<string>{"one"};
        REQUIRE(rul->getContents() == *expected);
    }

    SUBCASE("order two items by most recently inserted"){
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);

        rul->lookupPage(1);
        rul->lookupPage(2);
        auto expected = new vector<string>{"two", "one"};
        REQUIRE(rul->getContents() == *expected);
    }

    SUBCASE("duplicate items are moved not inserted"){
        auto pageStorage = new InMemoryPageStorage();
        auto cache = new Cache(4);
        auto rul = new RecentlyUsedList(cache, pageStorage);
        rul->lookupPage(1);
        rul->lookupPage(2);
        rul->lookupPage(1);

        auto expected = new vector<string>{"one", "two"};
        REQUIRE(rul->getContents() == *expected);
    }

    SUBCASE("move from back to front"){
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

    SUBCASE("remove one not from back"){
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
    SUBCASE("one element capacity"){
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


