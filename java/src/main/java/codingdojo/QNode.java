package codingdojo;

public class QNode {

    private int pageNumber;
    private QNode previous;
    private QNode next;

    public QNode(int pageNumber) {
        this.pageNumber = pageNumber;
    }
    public void setNext(QNode q) {
        this.next = q;
    }

    public void setPrevious(QNode q) {
        this.previous = q;
    }

    public QNode getPrevious() {
        return this.previous;
    }

    public int getPageNumber() {
        return this.pageNumber;
    }

    public QNode getNext() {
        return this.next;
    }
}
