package codingdojo;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class RecentlyUsedListTest {

    @Test
    void fourElements() {
        var queueLength = 4;
        var pages = List.of(1,2,3,1,4,5);
        var queue = RecentlyUsedList.createRecentlyUsedList(queueLength, pages);

        List<Integer> currentPages = queue.getCurrentPages(queueLength);

        assertEquals(List.of(5,4,1,3), currentPages);
    }

    @Test
    void fourElementsSmallHash() {
        var queueLength = 4;
        var pages = List.of(1,2,3,1,4,5);
        var queue = RecentlyUsedList.createRecentlyUsedList(queueLength, pages);

        List<Integer> currentPages = queue.getCurrentPages(queueLength);

        assertEquals(List.of(5,4,1,3), currentPages);
    }

    @Test
    void removeOneNotFromBack() {
        var queueLength = 3;
        var pages = List.of(1,2,3,2,4,5);
        var queue = RecentlyUsedList.createRecentlyUsedList(queueLength, pages);

        List<Integer> currentPages = queue.getCurrentPages(queueLength);

        assertEquals(List.of(5,4,2), currentPages);
    }

    @Test
    void oneElement() {
        var queueLength = 1;
        var pages = List.of(1,2,3);
        var queue = RecentlyUsedList.createRecentlyUsedList(queueLength, pages);

        List<Integer> currentPages = queue.getCurrentPages(queueLength);

        assertEquals(List.of(3), currentPages);
    }
}
