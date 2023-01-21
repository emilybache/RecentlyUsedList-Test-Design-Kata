package codingdojo;

import java.util.Objects;

public class QNode {

    private final int pageNumber;
    private final String page;
    private QNode previous;
    private QNode next;

    public QNode(int pageNumber, String page) {
        this.pageNumber = pageNumber;
        this.page = page;
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

    public String getPage() {
        return page;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        QNode qNode = (QNode) o;
        return pageNumber == qNode.pageNumber && page.equals(qNode.page);
    }

    @Override
    public int hashCode() {
        return Objects.hash(pageNumber, page);
    }

    @Override
    public String toString() {
        return "QNode{" +
                "pageNumber=" + pageNumber +
                ", page='" + page + '\'' +
                '}';
    }
}
