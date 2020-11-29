public class SET<Key> {
    private int N;
    private int M = 16;
    private Key[] keys;

    public SET() {
        keys = (Key[]) new Object[M];
    }

    public SET(int m) {
        keys = (Key[]) new Object[m];
        M = m;
    }

    private void resize(int cap) {
        SET<Key> t = new SET<Key>(cap);
        for (int i = 0; i < M; ++i)
            if (keys[i] != null)
                t.add(keys[i]);
        keys = t.keys;
        M = t.M;
    }

    private int hash(Key key) {
        return (key.hashCode() & 0x7fffffff) % M;
    }

    public int size() {
        return N;
    }

    public boolean contains(Key key) {
        for (int i = hash(key); keys[i] != null; i++)
            if (keys[i].equals(key))
                return true;
        return false;
    }

    public void add(Key key) {
        if (N >= M / 2) resize(M * 2);

        int i = hash(key);
        for (; keys[i] != null; i = (i + 1) % M) {
            if (keys[i].equals(key))
                return;
        }
        keys[i] = key;
        N++;
    }

    public void delete(Key key) {
        if (!contains(key)) return;

        int i = hash(key);
        for (; !key.equals(keys[i]); i = (i + 1) % M) ;
        keys[i] = null;

        i = (i + 1) % M;
        for (; keys[i] != null; i = (i + 1) % M) {
            Key keyToRedo = keys[i];
            keys[i] = null;
            N--;
            add(keyToRedo);
        }
        N--;
        if (N > 0 && N == M / 8) resize(M / 2);
    }
}
