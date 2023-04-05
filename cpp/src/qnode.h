

#ifndef RECENTLYUSEDLIST_QNODE_H
#define RECENTLYUSEDLIST_QNODE_H
#include <string>
#include <utility>

using namespace std;


typedef struct QNode {
    struct QNode *prev, *next;
    int pageNumber;
    string page;
} QNode;

QNode* newQNode(int pageNumber, string page);


#endif //RECENTLYUSEDLIST_QNODE_H
