package codingdojo;

import java.util.List;

/**
 * This is a Test Double - specifically a Fake
 * It replaces a database for testing purposes.
 */
public class InMemoryPageStorage implements PageStorage {
    private final List<String> contents;

    public InMemoryPageStorage(List<String> contents) {
        this.contents = contents;
    }

    @Override
    public String lookup(Integer index) {
        return this.contents.get(index-1);
    }
}
