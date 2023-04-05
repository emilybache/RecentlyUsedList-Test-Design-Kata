

#include "Cache.h"

int Cache::getCapacity() {
    return _capacity;
}

QNode* Cache::getQNode(int pageNumber) {
    auto it = _qnodes->find(pageNumber);
    if (it == _qnodes->end())
        return nullptr;

    auto foundNode = _qnodes->at(pageNumber);
    return foundNode;
}

void Cache::setQNode(int pageNumber, QNode *node) {
    if (node == nullptr) {
        auto it = _qnodes->find(pageNumber);
        _qnodes->erase(it);
    } else {
        _qnodes->insert(make_pair(pageNumber, node));
    }
    if (_qnodes->size() > _capacity) {
        throw invalid_argument("Cache is full!");
    }
}

void Cache::setCapacity(int capacity) {
    _capacity = capacity;
}


