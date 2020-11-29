import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

import javax.sound.sampled.Line;

public class LinearProbingHashST<Key, Value> {
    private int N;
    private int M = 16;
    private Key[] keys;
    private Value[] vals;

    private int hash(Key key) {
        return (key.hashCode() & 0x7fffffff) % M;
    }

    private void resize(int cap) {
        LinearProbingHashST<Key, Value> t =
                new LinearProbingHashST<Key, Value>(cap);
        for (int i = 0; i < M; i++)
            if (keys[i] != null)
                t.put(keys[i], vals[i]);
        keys = t.keys;
        vals = t.vals;
        M = t.M;
    }

    public LinearProbingHashST() {
        keys = (Key[]) new Object[M];
        vals = (Value[]) new Object[M];
    }

    public LinearProbingHashST(int m) {
        keys = (Key[]) new Object[m];
        vals = (Value[]) new Object[m];
        M = m;
    }

    public void put(Key key, Value val) {
        if (N >= M / 2) resize(M * 2);

        int i = hash(key);
        for (; keys[i] != null; i = (i + 1) % M)
            if (keys[i].equals(key)) {
                vals[i] = val;
                return;
            }
        keys[i] = key;
        vals[i] = val;
        N++;
    }

    public Value get(Key key) {
        for (int i = hash(key); keys[i] != null; i = (i + 1) % M)
            if (keys[i].equals(key))
                return vals[i];
        return null;
    }

    public void delete(Key key) {
        if (!contains(key)) return;

        //删除指定的键-值对
        int i = hash(key);
        while (!key.equals(keys[i]))
            i = (i + 1) % M;
        keys[i] = null;
        vals[i] = null;

        /* 将删除键-值对右边的键-值对重新插入，这样防止后续的键-值对
            无法查找到（因为这些键-值对很有可能是通过探针的方式插入的） */
        i = (i + 1) % M;
        for (; keys[i] != null; i = (i + 1) % M) {
            Key keyToRedo = keys[i];
            Value valToRedo = vals[i];
            keys[i] = null;
            vals[i] = null;
            N--;
            put(keyToRedo, valToRedo);
        }
        N--;
        if (N > 0 && N == M / 8)
            resize(M / 2);
    }

    public Iterable<Key> keys() {
        Queue<Key> queue = new Queue<Key>();
        for (int i = 0; i < M; ++i)
            if (keys[i] != null)
                queue.enqueue(keys[i]);
        return queue;
    }

    public boolean contains(Key key) {
        return get(key) != null;
    }

    public int size() {
        return N;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public static void main(String[] args) {
        LinearProbingHashST<String, Integer> linearProbingHashST
                = new LinearProbingHashST<String, Integer>();
        linearProbingHashST.put("a", 132);
        linearProbingHashST.put("b", 32);
        linearProbingHashST.put("k", 54);
        linearProbingHashST.put("d", 63);
        linearProbingHashST.put("x", 43);
        for (String str : linearProbingHashST.keys())
            StdOut.println(str);
        StdOut.println("size: " + linearProbingHashST.size());
        linearProbingHashST.delete("k");
        StdOut.println("current size: " + linearProbingHashST.size());
        for (String str : linearProbingHashST.keys())
            StdOut.println(str);
    }
}
