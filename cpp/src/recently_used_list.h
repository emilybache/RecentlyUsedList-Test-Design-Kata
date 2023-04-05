#ifndef SAMPLE_H
#define SAMPLE_H

#include <vector>
#include <string>

#include "qnode.h"
#include "Cache.h"
#include "PageStorage.h"

using namespace std;


class RecentlyUsedList {
public:

    RecentlyUsedList(Cache *cache, PageStorage *storage): _cache(cache), _storage(storage) {
        _count = 0;
        _front = nullptr;
        _rear = nullptr;
    };

    bool areAllFramesFull() const;
    bool isEmpty() const;
    string lookupPage(int pageNumber);
    vector<int> getCurrentPages();
    vector<string> getContents();

private:
    Cache *_cache;
    PageStorage *_storage;
    int _count;
    QNode *_front;
    QNode *_rear;

    void deQueue();
    void enQueue(int pageNumber);
};

#endif //SAMPLE_H
