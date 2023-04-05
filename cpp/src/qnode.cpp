
#include "qnode.h"


QNode* newQNode(int pageNumber, string page) {
    // Allocate memory and assign 'pageNumber'
    auto temp = (QNode*)malloc(sizeof(QNode));
    temp->pageNumber = pageNumber;
    temp->page = std::move(page);

    // Initialize prev and next as NULL
    temp->prev = temp->next = nullptr;

    return temp;
}
