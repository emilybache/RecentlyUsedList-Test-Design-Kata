package codingdojo;

import java.util.HashMap;
import java.util.Map;

/**
 * Storage for QNodes. Look them up by pageNumber. Maximum capacity is given in constructor.
 */
public class Hash {
    private int capacity;
    private Map<Integer, QNode> qnodes;

    public Hash(int capacity) {
        this.capacity = capacity;
        this.qnodes  = new HashMap<>(capacity);
    }

    public QNode getQNode(int pageNumber) {
        if (!this.qnodes.containsKey(pageNumber)) {
            return null;
        }
        return this.qnodes.get(pageNumber);
    }

    public void setQnode(int pageNumber, QNode qnode) {
        if (qnode == null) {
            this.qnodes.remove(pageNumber);
        } else {
            this.qnodes.put(pageNumber, qnode);
        }
        if (this.qnodes.size() > capacity) {
            throw new IndexOutOfBoundsException("Hash is full!");
        }
    }

    public int getCapacity() {
        return this.capacity;
    }
}
