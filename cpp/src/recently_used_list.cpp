#include "recently_used_list.h"
#include <algorithm>

RecentlyUsedList::RecentlyUsedList() {
    _contents = new vector<string>();
}

const vector<string> &RecentlyUsedList::getContents() const { return *_contents; }

void RecentlyUsedList::insert(const string& item) {
    if (item.empty()) {
        return;
    }
    _contents->erase(std::remove(_contents->begin(), _contents->end(), item),
                     _contents->end());
    _contents->insert(_contents->begin(), item);
}
