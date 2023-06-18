import pytest

from cache import Cache
from recently_used_list import RecentlyUsedList


class InMemoryPageStorage:
    def __init__(self, contents):
        self.contents = contents

    def lookup(self, page_number):
        return self.contents[page_number]


@pytest.fixture
def recently_used_list():
    cache = Cache()
    page_storage = InMemoryPageStorage(["zero", "one", "two", "three", "four", "five", "six"])
    return RecentlyUsedList(cache, page_storage)
