package codingdojo;

import java.util.ArrayList;
import java.util.List;

public class RecentlyUsedList {
    private final Hash hash;
    private final PageStorage storage;
    private final int numberOfFrames;
    private int count;
    private QNode front;
    private QNode rear;

    /**
     * Construct an empty queue
     *
     * @param hash - the underlying storage for QNodes
     */
    public RecentlyUsedList(Hash hash, PageStorage storage) {
        this.hash = hash;
        this.storage = storage;
        this.numberOfFrames = this.hash.getCapacity();
    }

    boolean areAllFramesFull() {
        return this.count == this.numberOfFrames;
    }

    boolean isEmpty() {
        return this.rear == null;
    }

    private void deQueue() {
        if (isEmpty())
            return;

        if (this.front == this.rear) {
            this.front = null;
        }

        this.rear = this.rear.getPrevious();

        if (this.rear != null) {
            this.rear.setNext(null);
        }
        this.count--;
    }

    private void enQueue(int pageNumber) {
        // If all frames are full, remove the page at the rear
        if (areAllFramesFull() && this.rear != null) {
            this.hash.setQnode(this.rear.getPageNumber(), null);
            deQueue();
        }
        if (!areAllFramesFull()) {
            // Create a new node with given page number,
            // And add the new node to the front of queue
            var temp = new QNode(pageNumber, storage.lookup(pageNumber));
            temp.setNext(this.front);

            // If queue is empty, change both front and rear pointers
            if (isEmpty()) {
                this.rear = temp;
                this.front = temp;
            } else // Else change the front
            {
                this.front.setPrevious(temp);
                this.front = temp;
            }

            // Add page entry to hash also
            this.hash.setQnode(pageNumber, temp);

            // increment number of full frames
            this.count++;
        }
    }

    /**
     * This function is called when a page with given 'pageNumber' is referenced
     * from cache (or memory). There are two cases:
     * 1. Frame is not there in memory, we bring it in memory and add to the front
     * of queue
     * 2. Frame is there in memory, we move the frame to front of queue
     */
    public String lookupPage(int pageNumber) {
        QNode reqPage = this.hash.getQNode(pageNumber);

        // the page is not in cache, bring it
        if (reqPage == null)
            enQueue(pageNumber);

            // page is there and not at front, change pointer
        else if (reqPage != this.front) {
            // Unlink rquested page from its current location
            // in queue.
            reqPage.getPrevious().setNext(reqPage.getNext());
            if (reqPage.getNext() != null)
                reqPage.getNext().setPrevious(reqPage.getPrevious());

            // If the requested page is rear, then change rear
            // as this node will be moved to front
            if (reqPage == this.rear) {
                this.rear = reqPage.getPrevious();
                this.rear.setNext(null);
            }

            // Put the requested page before current front
            reqPage.setNext(this.front);
            reqPage.setPrevious(null);

            // Change prev of current front
            reqPage.getNext().setPrevious(reqPage);

            // Change front to the requested page
            this.front = reqPage;
        }
        if (this.front != null) {
            return this.front.getPage();
        }
        return null;
    }

    public List<Integer> getCurrentPages() {
        return this.getContents().stream().map(QNode::getPageNumber).toList();
    }

    public List<QNode> getContents() {
        QNode current = this.front;
        int i = 0;
        var result = new ArrayList<QNode>();
        while (current != null && i < this.numberOfFrames) {
            result.add(current);
            current = current.getNext();
            i++;
        }
        return result;
    }
}
