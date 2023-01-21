

#ifndef RECENTLYUSEDLIST_RECENTLY_USED_LIST_H
#define RECENTLYUSEDLIST_RECENTLY_USED_LIST_H


// A Queue Node
typedef struct QNode {
    struct QNode *prev, *next;
    unsigned pageNumber; // the page number stored in this QNode
} QNode;

// A Queue (A FIFO collection of Queue Nodes)
typedef struct Queue {
    unsigned count; // Number of filled frames
    unsigned numberOfFrames; // total number of frames
    QNode *front, *rear;
} Queue;

// A hash (Collection of pointers to Queue Nodes)
typedef struct Hash {
    int capacity; // how many pages can be there
    QNode** array; // an array of queue nodes
} Hash;


// A utility function to create an empty Queue.
// The queue can have at most 'numberOfFrames' nodes
Queue* createQueue(int numberOfFrames);

// A utility function to create an empty Hash of given capacity
Hash* createHash(int capacity);

// This function is called when a page with given 'pageNumber' is referenced
// from cache (or memory).
void LookupPage(Queue* queue, Hash* hash, unsigned pageNumber);

// populate the array 'pages' with the current order of pages in the queue
void currentPageOrder(Queue* queue, int pages[], int max);

// return a vector of all the pages in the queue, in order
std::vector<int>* currentPages(Queue* q);

#endif //RECENTLYUSEDLIST_RECENTLY_USED_LIST_H
