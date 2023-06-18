from dataclasses import dataclass

from typing import TypeVar

QNode = TypeVar("QNode")


@dataclass
class QNode:
    page_number: int
    page: str
    prev: QNode
    next: QNode


class RecentlyUsedList:
    def __init__(self, cache, storage):
        self.cache = cache
        self.storage = storage
        self.count = 0
        self.front = None
        self.rear = None

    @property
    def cache_size(self):
        return self.cache.capacity

    @cache_size.setter
    def cache_size(self, value):
        self.cache.capacity = value

    def lookup_page(self, pageNumber):
        req_page = self.cache.get_qnode(pageNumber)

        # the page is not in cache, bring it
        if (req_page is None):
            self.en_queue(pageNumber)
        # page is there and not at front, change pointer
        elif (req_page != self.front):
            # Unlink rquested page from its current location
            # in queue.
            req_page.prev.next = req_page.next
            if (req_page.next is not None):
                req_page.next.prev = req_page.prev

            # If the requested page is rear, then change rear
            # as this node will be moved to front
            if (req_page == self.rear):
                self.rear = req_page.prev
                self.rear.next = None

            # Put the requested page before current front
            req_page.next = self.front
            req_page.prev = None

            # Change prev of current front
            req_page.next.prev = req_page

            # Change front to the requested page
            self.front = req_page

        if (self.front != None):
            return self.front.page

        return ""

    @property
    def current_pages(self):
        return [node.page_number for node in self.contents]

    @property
    def current_page_content(self):
        return [node.page for node in self.contents]

    @property
    def contents(self):
        current = self.front
        contents = []
        i = 0
        while current is not None and i < self.count:
            contents.append(current)
            current = current.next
            i += 1
        return contents

    def is_empty(self):
        return self.rear is None

    def are_all_frames_full(self):
        return self.count == self.cache.capacity


    def de_queue(self):
        if (self.is_empty()):
            return

        # If this is the only node in list, then change front
        if (self.front == self.rear):
            self.front = None
    
        # Change rear and remove the previous rear
        temp = self.rear
        self.rear = self.rear.prev
    
        if (self.rear):
            self.rear.next = None
    
        del (temp)
    
        # decrement the number of full frames by 1
        self.count -= 1


    def en_queue(self, pageNumber):
        # If all frames are full, remove the page at the rear
        if (self.are_all_frames_full() and self.rear != None):
            # remove page from hash
            self.cache.set_qnode(self.rear.page_number, None)
            self.de_queue()
        
        if (not self.are_all_frames_full()):
            # Create a new node with given page number,
            # And add the new node to the front of queue
            temp = QNode(pageNumber, self.storage.lookup(pageNumber), None, None)
            temp.next = self.front
    
            # If queue is empty, change both front and rear pointers
            if (self.is_empty()):
                self.rear = self.front = temp
            else: # Else change the front
            
                self.front.prev = temp
                self.front = temp
            
    
            # Add page entry to hash also
            self.cache.set_qnode(pageNumber, temp)
    
            # increment number of full frames
            self.count += 1
        
