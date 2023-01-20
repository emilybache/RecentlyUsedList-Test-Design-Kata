package codingdojo;

import java.util.ArrayList;

public class RecentlyUsedList {
    private final ArrayList<String> storage;

    public RecentlyUsedList() {
        this.storage = new ArrayList<String>();
    }

    public int size() {
        return this.storage.size();
    }

    public void add(String item) {
        this.storage.remove(item);
        this.storage.add(0, item);
    }

    public String get(int index) {
        return this.storage.get(index);
    }
}
