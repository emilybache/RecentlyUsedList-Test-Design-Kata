package codingdojo;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class RecentlyUsedListTest {

    private PageStorage storage = new InMemoryPageStorage(List.of("one", "two", "three", "four", "five", "six"));

    private RecentlyUsedList createRecentlyUsedListAddLookupPages(int capacity, List<Integer> pagesToLookup) {
        Hash hash = new Hash(capacity);
        var q = new RecentlyUsedList(hash, storage);
        for (int page : pagesToLookup) {
            q.lookupPage(page);
        }
        return q;
    }

    @Test
    void emptyQueue() {
        int capacity = 0;
        var pagesToLookup = List.of(1,2,3);

        RecentlyUsedList q = createRecentlyUsedListAddLookupPages(capacity, pagesToLookup);

        assertEquals(List.of(), q.getCurrentPages());
        assertEquals(List.of(), q.getContents());
    }

    @Test
    void fourElements() {
        int capacity = 4;
        var pagesToLookup = List.of(1,2,3,1,4,5);

        RecentlyUsedList q = createRecentlyUsedListAddLookupPages(capacity, pagesToLookup);

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
        int capacity = 3;
        var pagesToLookup = List.of(1,2,3,2,4,5);

        RecentlyUsedList q = createRecentlyUsedListAddLookupPages(capacity, pagesToLookup);

        assertEquals(List.of(5, 4, 2), q.getCurrentPages());
        assertEquals(List.of(
                new QNode(5, "five"),
                new QNode(4, "four"),
                new QNode(2, "two")
        ), q.getContents());

    }

    @Test
    void oneElement() {
        int capacity = 1;
        var pagesToLookup = List.of(1,2,3);

        RecentlyUsedList q = createRecentlyUsedListAddLookupPages(capacity, pagesToLookup);


        assertEquals(List.of(3), q.getCurrentPages());
        assertEquals(List.of(
                new QNode(3, "three")
        ), q.getContents());
    }
}
