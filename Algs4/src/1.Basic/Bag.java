import edu.princeton.cs.algs4.StdOut;

import java.util.Iterator;

public class Bag<Item> implements Iterable<Item> {
    private Node first;
    private int N = 0;

    private class Node {
        Item item;
        Node next;
    }

    private class ListIterator implements Iterator<Item> {
        private Node current = first;

        public boolean hasNext() {
            return current != null;
        }

        public Item next() {
            Item item = current.item;
            current = current.next;
            return item;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public void add(Item item) {
        Node oldfirst = first;
        first = new Node();
        first.item = item;
        first.next = oldfirst;
        N++;
    }

    public Iterator iterator() {
        return new ListIterator();
    }

    public static void main(String[] args) {
        Bag<Integer> bag = new Bag<Integer>();

        bag.add(120);
        bag.add(32);
        bag.add(42);
        for (Integer elem : bag)
            StdOut.println(elem);
        StdOut.println("current size: " + bag.size());
    }
}
