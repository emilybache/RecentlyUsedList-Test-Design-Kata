import pytest

from cache import Cache
from recently_used_list import RecentlyUsedList


class InMemoryPageStorage:
    def __init__(self, contents):
        self.contents = contents

    def lookup(self, page_number):
        return self.contents[page_number]


def test_empty_cache():
    page_storage = InMemoryPageStorage(["zero", "one", "two", "three", "four", "five", "six"])
    cache = Cache()
    recently_used_list = RecentlyUsedList(cache, page_storage)

    recently_used_list.lookup_page(1)
    recently_used_list.lookup_page(2)
    recently_used_list.lookup_page(3)

    assert recently_used_list.current_pages == []
    assert recently_used_list.contents == []


def test_lookup_page():
    page_storage = InMemoryPageStorage(["zero", "one", "two", "three", "four", "five", "six"])
    cache = Cache()
    recently_used_list = RecentlyUsedList(cache, page_storage)
    recently_used_list.cache_size = 1

    page = recently_used_list.lookup_page(1)

    assert page == "one"


def test_one_element():
    page_storage = InMemoryPageStorage(["zero", "one", "two", "three", "four", "five", "six"])
    cache = Cache()
    recently_used_list = RecentlyUsedList(cache, page_storage)
    recently_used_list.cache_size = 1

    recently_used_list.lookup_page(1)
    recently_used_list.lookup_page(2)
    recently_used_list.lookup_page(3)

    assert recently_used_list.current_pages == [3]
    assert recently_used_list.contents[0].page == "three"


def test_move_from_back_to_front():
    page_storage = InMemoryPageStorage(["zero", "one", "two", "three", "four", "five", "six"])
    cache = Cache()
    recently_used_list = RecentlyUsedList(cache, page_storage)
    recently_used_list.cache_size = 4

    recently_used_list.lookup_page(1)
    recently_used_list.lookup_page(2)
    recently_used_list.lookup_page(3)
    recently_used_list.lookup_page(1)
    recently_used_list.lookup_page(4)
    recently_used_list.lookup_page(5)

    assert recently_used_list.current_pages == [5, 4, 1, 3]
    assert recently_used_list.contents[0].page == "five"
    assert recently_used_list.contents[1].page == "four"
    assert recently_used_list.contents[2].page == "one"
    assert recently_used_list.contents[3].page == "three"


def test_remove_one_not_from_back():
    page_storage = InMemoryPageStorage(["zero", "one", "two", "three", "four", "five", "six"])
    cache = Cache()
    recently_used_list = RecentlyUsedList(cache, page_storage)
    recently_used_list.cache_size = 3

    recently_used_list.lookup_page(1)
    recently_used_list.lookup_page(2)
    recently_used_list.lookup_page(3)
    recently_used_list.lookup_page(2)
    recently_used_list.lookup_page(4)
    recently_used_list.lookup_page(5)

    assert recently_used_list.current_pages == [5, 4, 2]
    assert recently_used_list.contents[0].page == "five"
    assert recently_used_list.contents[1].page == "four"
    assert recently_used_list.contents[2].page == "two"
