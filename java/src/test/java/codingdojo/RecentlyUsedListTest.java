package codingdojo;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class RecentlyUsedListTest {

    private final PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));

    private RecentlyUsedList createRecentlyUsedList(int cacheSize) {
        var cache = new Cache<QNode>(cacheSize);
        return new RecentlyUsedList(cache, storage);
    }

    private static void lookupPages(RecentlyUsedList recentlyUsedList, List<Integer> pagesToLookUp) {
        for (int pageNumber :
                pagesToLookUp) {
            recentlyUsedList.lookupPage(pageNumber);
        }
    }

    @Test
    void emptyCache() {
        RecentlyUsedList recentlyUsedList = createRecentlyUsedList(0);

        lookupPages(recentlyUsedList, List.of(1,2,3));

        assertTrue(recentlyUsedList.getCurrentPages().isEmpty());
        assertTrue(recentlyUsedList.getContents().isEmpty());
    }

    @Test
    void lookupPage() {
        RecentlyUsedList recentlyUsedList = createRecentlyUsedList(1);

        String page = recentlyUsedList.lookupPage(1);

        assertEquals("one", page);
    }

    @Test
    void moveFromBackToFront() {
        RecentlyUsedList recentlyUsedList = createRecentlyUsedList(4);

        lookupPages(recentlyUsedList, List.of(1,2,3,1,4,5));

        assertEquals(List.of(5, 4, 1, 3), recentlyUsedList.getCurrentPages());
        assertEquals(List.of(
                new QNode(5, "five"),
                new QNode(4, "four"),
                new QNode(1, "one"),
                new QNode(3, "three")
        ), recentlyUsedList.getContents());
    }

    @Test
    void removeOneNotFromBack() {
        RecentlyUsedList recentlyUsedList = createRecentlyUsedList(3);

        lookupPages(recentlyUsedList, List.of(1,2,3,2,4,5));

        assertEquals(List.of(5, 4, 2), recentlyUsedList.getCurrentPages());
        assertEquals(List.of(
                new QNode(5, "five"),
                new QNode(4, "four"),
                new QNode(2, "two")
        ), recentlyUsedList.getContents());

    }

    @Test
    void oneElement() {
        RecentlyUsedList recentlyUsedList = createRecentlyUsedList(1);

        lookupPages(recentlyUsedList, List.of(1,2,3));


        assertEquals(List.of(3), recentlyUsedList.getCurrentPages());
        assertEquals(List.of(
                new QNode(3, "three")
        ), recentlyUsedList.getContents());
    }
}
