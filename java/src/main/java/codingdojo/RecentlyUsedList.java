package codingdojo;

import java.util.ArrayList;
import java.util.List;

public class RecentlyUsedList {
    private final Hash hash;
    private int numberOfFrames;
    private int count;
    private QNode front;
    private QNode rear;

    /**
     * Construct an empty queue
     *
     * @param numberOfFrames - the maximum number of elements in the queue
     */
    public RecentlyUsedList(int numberOfFrames) {
        this.numberOfFrames = numberOfFrames;
        this.hash = new Hash(numberOfFrames);
    }

    /**
     * Factory method to create a new queue with specific pages
     *
     * @param queueLength - the maximum number of elements in the queue
     * @param pages       - the pages to store in the queue initially, in order
     * @return the queue containing the pages
     */
    public static RecentlyUsedList createRecentlyUsedList(int queueLength, List<Integer> pages) {
        var q = new RecentlyUsedList(queueLength);
        for (Integer page : pages) {
            q.lookupPage(page);
        }
        return q;
    }

    boolean areAllFramesFull() {
        return this.count == this.numberOfFrames;
    }

    boolean isEmpty() {
        return this.rear == null;
    }

    void deQueue() {
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

    void enQueue(int pageNumber) {
        // If all frames are full, remove the page at the rear
        if (areAllFramesFull()) {
            this.hash.setQnode(this.rear.getPageNumber(), null);
            deQueue();
        }
        // Create a new node with given page number,
        // And add the new node to the front of queue
        var temp = new QNode(pageNumber);
        temp.setNext(this.front);

        // If queue is empty, change both front and rear pointers
        if (isEmpty()) {
            this.rear = temp;
            this.front = temp;
        }
        else // Else change the front
        {
            this.front.setPrevious(temp);
            this.front = temp;
        }

        // Add page entry to hash also
        this.hash.setQnode(pageNumber, temp);

        // increment number of full frames
        this.count++;
    }

    /** This function is called when a page with given 'pageNumber' is referenced
     * from cache (or memory). There are two cases:
     * 1. Frame is not there in memory, we bring it in memory and add to the front
     * of queue
     * 2. Frame is there in memory, we move the frame to front of queue
     *
     */
    void lookupPage(int pageNumber)
    {
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
    }

    List<Integer> getCurrentPages(int max) {
        QNode current = this.front;
        int i = 0;
        var result = new ArrayList<Integer>();
        while(current != null && i < max) {
            result.add(current.getPageNumber());
            current = current.getNext();
            i++;
        }
        return result;
    }
}
