package codingdojo;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class RecentlyUsedListTest {

    @Test
    void emptyCache() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        var cache = new Cache<QNode>(0);
        var recentlyUsedList = new RecentlyUsedList(cache, storage);
        recentlyUsedList.lookupPage(1);
        recentlyUsedList.lookupPage(2);
        recentlyUsedList.lookupPage(3);

        assertTrue(recentlyUsedList.getCurrentPages().isEmpty());
        assertTrue(recentlyUsedList.getContents().isEmpty());
    }

    @Test
    void lookupPage() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        var cache = new Cache<QNode>(1);
        var recentlyUsedList = new RecentlyUsedList(cache, storage);

        String page = recentlyUsedList.lookupPage(1);

        assertEquals("one", page);
    }

    @Test
    void moveFromBackToFront() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        var cache = new Cache<QNode>(4);
        var recentlyUsedList = new RecentlyUsedList(cache, storage);
        recentlyUsedList.lookupPage(1);
        recentlyUsedList.lookupPage(2);
        recentlyUsedList.lookupPage(3);
        recentlyUsedList.lookupPage(1);
        recentlyUsedList.lookupPage(4);
        recentlyUsedList.lookupPage(5);

        assertEquals(List.of(5, 4, 1, 3), recentlyUsedList.getCurrentPages());
        var contents = recentlyUsedList.getContents();
        assertEquals("five", contents.get(0).getPage());
        assertEquals("four", contents.get(1).getPage());
        assertEquals("one", contents.get(2).getPage());
        assertEquals("three", contents.get(3).getPage());
    }

    @Test
    void removeOneNotFromBack() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        var cache = new Cache<QNode>(3);
        var recentlyUsedList = new RecentlyUsedList(cache, storage);
        recentlyUsedList.lookupPage(1);
        recentlyUsedList.lookupPage(2);
        recentlyUsedList.lookupPage(3);
        recentlyUsedList.lookupPage(2);
        recentlyUsedList.lookupPage(4);
        recentlyUsedList.lookupPage(5);

        assertEquals(List.of(5, 4, 2), recentlyUsedList.getCurrentPages());
        var contents = recentlyUsedList.getContents();
        assertEquals("five", contents.get(0).getPage());
        assertEquals("four", contents.get(1).getPage());
        assertEquals("two", contents.get(2).getPage());

    }

    @Test
    void oneElement() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        var cache = new Cache<QNode>(1);
        var recentlyUsedList = new RecentlyUsedList(cache, storage);
        recentlyUsedList.lookupPage(1);
        recentlyUsedList.lookupPage(2);
        recentlyUsedList.lookupPage(3);

        assertEquals(List.of(3), recentlyUsedList.getCurrentPages());
        var contents = recentlyUsedList.getContents();
        assertEquals("three", contents.get(0).getPage());
    }
}
