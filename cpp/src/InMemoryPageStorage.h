

#ifndef RECENTLYUSEDLIST_INMEMORYPAGESTORAGE_H
#define RECENTLYUSEDLIST_INMEMORYPAGESTORAGE_H

#include <string>
#include <vector>

#include "PageStorage.h"

using namespace std;

class InMemoryPageStorage : public PageStorage {
public:
    InMemoryPageStorage() {
        contents = vector<string>({"zero", "one", "two", "three", "four", "five", "six"});
    }
    string lookup(int index) override;
private:
    vector<string> contents;
};


#endif //RECENTLYUSEDLIST_INMEMORYPAGESTORAGE_H
