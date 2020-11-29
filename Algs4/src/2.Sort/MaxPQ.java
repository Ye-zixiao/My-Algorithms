import edu.princeton.cs.algs4.StdOut;

public class MaxPQ<Key extends Comparable<Key>> {
    private Key[] pq;
    private int capacity;
    private int N = 0;

    public MaxPQ(int maxN) {
        pq = (Key[]) new Comparable[maxN + 1];
        capacity = maxN;
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public void insert(Key v) {
        if (isFull())
            resize(capacity * 2);
        pq[++N] = v;
        swim(N);
    }

    public Key delMax() {
        //这里可以加入越界检查，不过也无所谓
        Key max = pq[1];
        pq[1] = pq[N--];
        pq[N + 1] = null;
        sink(1);

        if ((N + 1) < capacity / 4)
            resize(capacity / 2);
        return max;
    }

    private boolean less(int i, int j) {
        return pq[i].compareTo(pq[j]) < 0;
    }

    private void swap(int i, int j) {
        Key temp = pq[i];
        pq[i] = pq[j];
        pq[j] = temp;
    }

    private void swim(int k) {
        while (k > 1 && less(k / 2, k)) {
            swap(k, k / 2);
            k /= 2;
        }
    }

    private void sink(int k) {
        while (2 * k <= N) {
            int j = k * 2;
            if (j < N && less(j, j + 1)) j++;
            if (!less(k, j)) break;
            swap(k, j);
            k = j;
        }
    }

    private void resize(int maxN) {
        Key[] temp = (Key[]) new Comparable[maxN];
        for (int i = 1; i <= N; ++i)
            temp[i] = pq[i];
        capacity *= 2;
        pq = temp;
    }

    private boolean isFull() {
        return N + 1 == capacity;
    }

    public static void main(String[] args) {
        MaxPQ<Integer> maxPQ = new MaxPQ<Integer>(110);

        for (int i = 0; i < 300; i++)
            maxPQ.insert(i);
        while (!maxPQ.isEmpty())
            StdOut.println(maxPQ.delMax());
    }
}
