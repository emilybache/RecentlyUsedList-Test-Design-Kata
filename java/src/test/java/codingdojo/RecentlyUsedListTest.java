package codingdojo;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class RecentlyUsedListTest {

    @Test
    void emptyQueue() {
        PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));
        Hash hash = new Hash(0);
        var q = new RecentlyUsedList(hash, storage);
        q.lookupPage(1);
        q.lookupPage(2);
        q.lookupPage(3);

        assertEquals(List.of(), q.getCurrentPages());
        assertEquals(List.of(), q.getContents());
    }

    @Test
    void fourElements() {
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
        assertEquals(List.of(
                        new QNode(5, "five"),
                        new QNode(4, "four"),
                        new QNode(1, "one"),
                        new QNode(3, "three")
        ), q.getContents());
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
        assertEquals(List.of(
                new QNode(5, "five"),
                new QNode(4, "four"),
                new QNode(2, "two")
        ), q.getContents());

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
        assertEquals(List.of(
                new QNode(3, "three")
        ), q.getContents());
    }
}
