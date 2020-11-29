
public class IndexMinPQ<Key extends Comparable<Key>> {
    private int[] pq;//索引二叉堆，保存进行优先排序的元素在keys数组中的索引
    private int[] qp;//存储在某一个索引在索引二叉堆中的下标
    private Key[] keys;//保存索引二叉堆中的真正优先级元素，若值为-1表示没有存储元素
    int maxN;
    int n;

    public IndexMinPQ(int maxN) {
        this.maxN = maxN;
        this.n = 0;
        pq = new int[maxN + 1];
        qp = new int[maxN + 1];
        keys = (Key[]) new Comparable[maxN + 1];
        for (int i = 0; i <= maxN; ++i)
            qp[i] = -1;
    }

    public int size() {
        return n;
    }

    public boolean isEmpty() {
        return n == 0;
    }

    public boolean contains(int i) {
        return qp[i] != -1;
    }

    public void insert(int i, Key key) {
        validateIndex(i);
        if (contains(i))
            throw new IllegalArgumentException("");

        n++;
        qp[i] = n;
        pq[n] = i;
        keys[i] = key;
        swim(n);
    }

    public void delete(int i) {
        validateIndex(i);
        if (!contains(i))
            throw new IllegalArgumentException("");

        int index = qp[i];
        swap(index, n--);
        swim(index);
        sink(index);
        keys[i] = null;
        qp[i] = -1;
    }

    public void changeKey(int i, Key key) {
        validateIndex(i);
        if (!contains(i))
            throw new IllegalArgumentException("");

        keys[i] = key;
        swim(qp[i]);
        sink(qp[i]);
    }

    public Key min() {
        if (isEmpty())
            throw new IllegalArgumentException("");
        return keys[pq[1]];
    }

    public int minIndex() {
        if (isEmpty())
            throw new IllegalArgumentException("");
        return pq[1];
    }

    public int delMin() {
        if (isEmpty())
            throw new IllegalArgumentException("");

        int minIndex = pq[1];
        swap(1, n--);
        sink(1);
        qp[minIndex] = -1;
        keys[minIndex] = null;
        pq[n + 1] = -1;
        return minIndex;
    }

    private void validateIndex(int i) {
        if (i < 0 && i >= maxN)
            throw new IllegalArgumentException("");
    }

    private boolean greater(int i, int j) {
        return keys[pq[i]].compareTo(keys[pq[j]]) > 0;
    }

    //交换优先队列中的两个元素的索引，因此需要交换pq和qp
    private void swap(int i, int j) {
        int tmp = pq[i];
        pq[i] = pq[j];
        pq[j] = tmp;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }

    private void sink(int k) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && greater(j, j + 1)) j++;
            if (!greater(k, j)) break;
            swap(k, j);
            k = j;
        }
    }

    private void swim(int k) {
        while (k > 1 && greater(k / 2, k)) {
            swap(k / 2, k);
            k /= 2;
        }
    }
}