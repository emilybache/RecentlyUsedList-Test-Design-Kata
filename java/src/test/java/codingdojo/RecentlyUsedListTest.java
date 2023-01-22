package codingdojo;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class RecentlyUsedListTest {

    @Test
    void emptyQueue() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        Hash hash = new Hash(0);
        var q = new RecentlyUsedList(hash, storage);
        q.lookupPage(1);
        q.lookupPage(2);
        q.lookupPage(3);

        assertTrue(q.getCurrentPages().isEmpty());
        assertTrue(q.getContents().isEmpty());
    }

    @Test
    void lookupPage() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        Hash hash = new Hash(1);
        var q = new RecentlyUsedList(hash, storage);

        String page = q.lookupPage(1);

        assertEquals("one", page);
    }

    @Test
    void moveFromBackToFront() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        Hash hash = new Hash(4);
        var q = new RecentlyUsedList(hash, storage);
        q.lookupPage(1);
        q.lookupPage(2);
        q.lookupPage(3);
        q.lookupPage(1);
        q.lookupPage(4);
        q.lookupPage(5);

        assertEquals(List.of(5, 4, 1, 3), q.getCurrentPages());
        var contents = q.getContents();
        assertEquals("five", contents.get(0).getPage());
        assertEquals("four", contents.get(1).getPage());
        assertEquals("one", contents.get(2).getPage());
        assertEquals("three", contents.get(3).getPage());
    }

    @Test
    void removeOneNotFromBack() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        Hash hash = new Hash(3);
        var q = new RecentlyUsedList(hash, storage);
        q.lookupPage(1);
        q.lookupPage(2);
        q.lookupPage(3);
        q.lookupPage(2);
        q.lookupPage(4);
        q.lookupPage(5);

        assertEquals(List.of(5, 4, 2), q.getCurrentPages());
        var contents = q.getContents();
        assertEquals("five", contents.get(0).getPage());
        assertEquals("four", contents.get(1).getPage());
        assertEquals("two", contents.get(2).getPage());

    }

    @Test
    void oneElement() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        Hash hash = new Hash(1);
        var q = new RecentlyUsedList(hash, storage);
        q.lookupPage(1);
        q.lookupPage(2);
        q.lookupPage(3);

        assertEquals(List.of(3), q.getCurrentPages());
        var contents = q.getContents();
        assertEquals("three", contents.get(0).getPage());
    }
}
