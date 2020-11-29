import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

import java.util.Collection;
import java.util.Iterator;

public class SeqSearchST<Key, Value> {
    private Node first;
    private int N = 0;

    private class Node {
        Key key;
        Value val;
        Node next;

        public Node(Key key, Value val, Node next) {
            this.key = key;
            this.val = val;
            this.next = next;
        }
    }

    public SeqSearchST() {
    }

    public Value get(Key key) {
        for (Node x = first; x != null; x = x.next) {
            if (key.equals(x.key))
                return x.val;
        }
        return null;
    }

    public void put(Key key, Value val) {
        for (Node x = first; x != null; x = x.next) {
            if (key.equals(x.key)) {
                x.val = val;
                return;
            }
        }
        first = new Node(key, val, first);
        N++;
    }

    public void delete(Key key) {
        put(key, null);
        N--;
    }

    public boolean contains(Key key) {
        return get(key) != null;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public Iterable<Key> keys() {
        Queue<Key> queue = new Queue<Key>();
        for (Node x = first; x != null; x = x.next)
            queue.enqueue(x.key);
        return queue;
    }

    public static void main(String[] args) {
        SeqSearchST<String, Integer> seqSearchST =
                new SeqSearchST<String, Integer>();

        seqSearchST.put("hello", 32);
        seqSearchST.put("show", 3);
        seqSearchST.put("world", 5);
        seqSearchST.put("code", 6);
        for (String key : seqSearchST.keys())
            StdOut.println(key + " " + seqSearchST.get(key));
        StdOut.println("size: " + seqSearchST.size());
    }
}
