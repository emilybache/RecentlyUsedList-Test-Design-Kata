

#ifndef RECENTLYUSEDLIST_CACHE_H
#define RECENTLYUSEDLIST_CACHE_H

#include <vector>
#include <string>
#include <unordered_map>

#include "qnode.h"

using namespace std;

/*
 * Storage for QNodes. Look them up by pageNumber. Maximum capacity is given in constructor.
 */
class Cache {
private:
    int _capacity;
    unordered_map<int, QNode*> *_qnodes;

public:
    explicit Cache(int capacity): _capacity(capacity) {
        _qnodes = new unordered_map<int, QNode*>();
    }
    QNode* getQNode(int pageNumber);
    void setQNode(int pageNumber, QNode *node);
    int getCapacity();
    void setCapacity(int capacity);
};


#endif //RECENTLYUSEDLIST_CACHE_H
