#include "recently_used_list.h"
#include <algorithm>


bool RecentlyUsedList::areAllFramesFull() const {
    return _count == _cache->getCapacity();
}

bool RecentlyUsedList::isEmpty() const {
    return _rear == nullptr;
}

string RecentlyUsedList::lookupPage(int pageNumber) {
    QNode* reqPage = _cache->getQNode(pageNumber);

    // the page is not in cache, bring it
    if (reqPage == nullptr)
        enQueue(pageNumber);

        // page is there and not at front, change pointer
    else if (reqPage != _front) {
        // Unlink rquested page from its current location
        // in queue.
        reqPage->prev->next = reqPage->next;
        if (reqPage->next != nullptr)
            reqPage->next->prev = reqPage->prev;

        // If the requested page is rear, then change rear
        // as this node will be moved to front
        if (reqPage == _rear) {
            _rear = reqPage->prev;
            _rear->next = nullptr;
        }

        // Put the requested page before current front
        reqPage->next = _front;
        reqPage->prev = nullptr;

        // Change prev of current front
        reqPage->next->prev = reqPage;

        // Change front to the requested page
        _front = reqPage;
    }
    if (_front != nullptr) {
        return _front->page;
    }
    return "";
}

vector<int> RecentlyUsedList::getCurrentPages() {
    vector<int> pages;
    QNode* current = _front;
    int i = 0;
    while (current != nullptr && i < _count)
    {
        pages.push_back(current->pageNumber);
        current = current->next;
        i++;
    }
    return pages;
}

vector<string> RecentlyUsedList::getContents() {
    vector<string> contents;
    QNode* current = _front;
    int i = 0;
    while (current != nullptr && i < _count)
    {
        contents.push_back(current->page);
        current = current->next;
        i++;
    }
    return contents;
}

void RecentlyUsedList::deQueue() {
    if (isEmpty())
        return;

    // If this is the only node in list, then change front
    if (_front == _rear)
        _front = nullptr;

    // Change rear and remove the previous rear
    QNode* temp = _rear;
    _rear = _rear->prev;

    if (_rear)
        _rear->next = nullptr;

    free(temp);

    // decrement the number of full frames by 1
    _count--;
}

void RecentlyUsedList::enQueue(int pageNumber) {
    // If all frames are full, remove the page at the rear
    if (areAllFramesFull() && _rear != nullptr) {
        // remove page from hash
        _cache->setQNode(_rear->pageNumber, nullptr);
        deQueue();
    }
    if (!areAllFramesFull()) {
        // Create a new node with given page number,
        // And add the new node to the front of queue
        QNode* temp = newQNode(pageNumber, _storage->lookup(pageNumber));
        temp->next = _front;

        // If queue is empty, change both front and rear pointers
        if (isEmpty())
            _rear = _front = temp;
        else // Else change the front
        {
            _front->prev = temp;
            _front = temp;
        }

        // Add page entry to hash also
        _cache->setQNode(pageNumber, temp);

        // increment number of full frames
        _count++;
    }

}


