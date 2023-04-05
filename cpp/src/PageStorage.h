

#ifndef RECENTLYUSEDLIST_PAGESTORAGE_H
#define RECENTLYUSEDLIST_PAGESTORAGE_H

#include <string>

using namespace std;

class PageStorage {
public:
    virtual string lookup(int index) = 0;
};


#endif //RECENTLYUSEDLIST_PAGESTORAGE_H
