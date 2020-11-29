import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.SequentialSearchST;
import edu.princeton.cs.algs4.StdOut;

public class SeparateChainingHashST<Key, Value> {
    private SequentialSearchST<Key, Value>[] st;
    private int N;//键值对数
    private int M;//散列表大小

    //根据键key，使用散列函数计算该键在散列表中的索引
    private int hash(Key key) {
        return (key.hashCode() & 0x7fffffff) % M;
    }

    private void resize(int newM) {
        SeparateChainingHashST<Key, Value> temp =
                new SeparateChainingHashST<Key, Value>(newM);
        for (int i = 0; i < M; i++)
            for (Key key : st[i].keys())
                temp.put(key, st[i].get(key));
        this.M = temp.M;
        this.N = temp.N;
        this.st = temp.st;
    }

    public SeparateChainingHashST(int M) {
        this.M = M;
        this.N = 0;
        st = (SequentialSearchST<Key, Value>[]) new SequentialSearchST[M];
        for (int i = 0; i < M; ++i)
            st[i] = new SequentialSearchST<>();
    }

    public SeparateChainingHashST() {
        this(997);
    }

    public void put(Key key, Value val) {
        if (N >= M * 10) resize(2 * M);

        st[hash(key)].put(key, val);
        N++;
    }

    public Value get(Key key) {
        return (Value) st[hash(key)].get(key);
    }

    public void delete(Key key) {
        st[hash(key)].delete(key);
        N--;

        if (N <= 2 * M) resize(M / 2);
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public boolean contains(Key key) {
        return get(key) != null;
    }

    Iterable<Key> keys() {
        Queue<Key> queue = new Queue<Key>();

        for (int i = 0; i < M; ++i) {
            if (!st[i].isEmpty()) {
                Iterable<Key> t = st[i].keys();
                for (Key key : t)
                    queue.enqueue(key);
            }
        }
        return queue;
    }

    public static void main(String[] args) {
        SeparateChainingHashST<String, Integer> st = new SeparateChainingHashST<String, Integer>();

        st.put("a", 43);
        st.put("b", 32);
        st.put("s", 23);
        st.put("k", 12);
        st.put("p", 97);
        StdOut.println("size: " + st.size());
        StdOut.println("a: " + st.get("a"));
        StdOut.println("k: " + st.get("k"));
        for (String str : st.keys())
            StdOut.println(str);
    }
}
