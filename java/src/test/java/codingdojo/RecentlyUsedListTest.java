package codingdojo;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class RecentlyUsedListTest {

    /**
     * Factory method to create a new queue with specific pages
     *
     * @param queueLength - the maximum number of elements in the queue
     * @param pages       - the pages to store in the queue in order
     * @return the queue containing the pages
     */
    public static RecentlyUsedList createRecentlyUsedList(int queueLength, List<Integer> pages) {
        var q = new RecentlyUsedList(queueLength);
        for (Integer page : pages) {
            q.lookupPage(page);
        }
        return q;
    }

    @Test
    void fourElements() {
        var queueLength = 4;
        var pages = List.of(1,2,3,1,4,5);

        var queue = createRecentlyUsedList(queueLength, pages);

        assertEquals(List.of(5,4,1,3), queue.getCurrentPages());
    }

    @Test
    void fourElementsSmallHash() {
        var queueLength = 4;
        var pages = List.of(1,2,3,1,4,5);

        var queue = createRecentlyUsedList(queueLength, pages);

        assertEquals(List.of(5,4,1,3), queue.getCurrentPages());
    }

    @Test
    void removeOneNotFromBack() {
        var queueLength = 3;
        var pages = List.of(1,2,3,2,4,5);

        var queue = createRecentlyUsedList(queueLength, pages);

        assertEquals(List.of(5,4,2), queue.getCurrentPages());
    }

    @Test
    void oneElement() {
        var queueLength = 1;
        var pages = List.of(1,2,3);

        var queue = createRecentlyUsedList(queueLength, pages);

        assertEquals(List.of(3), queue.getCurrentPages());
    }
}
