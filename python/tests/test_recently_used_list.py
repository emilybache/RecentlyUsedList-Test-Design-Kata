import pytest

from recently_used_list import RecentlyUsedList, QNode


def lookup_pages(recentlyUsedList: RecentlyUsedList, pages):
    for page in pages:
        recentlyUsedList.lookup_page(page)


def test_empty_cache(recently_used_list):
    recently_used_list.cache_size = 0
    lookup_pages(recently_used_list, [1, 2, 3])
    assert recently_used_list.current_pages == []
    assert recently_used_list.contents == []


def test_lookup_page(recently_used_list):
    recently_used_list.cache_size = 1
    page = recently_used_list.lookup_page(1)
    assert page == "one"


def test_one_element(recently_used_list):
    recently_used_list.cache_size = 1
    lookup_pages(recently_used_list, [1, 2, 3])
    assert recently_used_list.current_pages == [3]
    assert recently_used_list.current_page_content == [
        "three",
    ]


def test_move_from_back_to_front(recently_used_list):
    recently_used_list.cache_size = 4
    lookup_pages(recently_used_list, [1, 2, 3, 1, 4, 5])
    assert recently_used_list.current_pages == [5, 4, 1, 3]
    assert recently_used_list.current_page_content == [
        "five",
        "four",
        "one",
        "three",
    ]


def test_remove_one_not_from_back(recently_used_list):
    recently_used_list.cache_size = 3
    lookup_pages(recently_used_list, [1, 2, 3, 2, 4, 5])
    assert recently_used_list.current_pages == [5, 4, 2]
    assert recently_used_list.current_page_content == [
        "five",
        "four",
        "two",
    ]
