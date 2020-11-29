import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

public class RedBlackBST<Key extends Comparable<Key>, Value> {
    private static final boolean RED = true;
    private static final boolean BLACK = false;

    private Node root;

    private class Node {
        Key key;
        Value val;
        Node left, right;
        boolean color;
        int size;

        public Node(Key key, Value val, boolean color, int size) {
            this.key = key;
            this.val = val;
            this.color = color;
            this.size = size;
        }
    }

    public RedBlackBST() {
    }

    private boolean isRed(Node x) {
        if (x == null) return false;
        return x.color == RED;
    }

    private int size(Node x) {
        if (x == null)
            return 0;
        return x.size;
    }

    //左旋
    private Node rotateLeft(Node h) {
        Node x = h.right;
        h.right = x.left;
        x.left = h;

        x.color = h.color;
        h.color = RED;
        x.size = h.size;
        h.size = size(h.left) + size(h.right) + 1;
        return x;
    }

    //右旋
    private Node rotateRight(Node h) {
        Node x = h.left;
        h.left = x.right;
        x.right = h;

        x.color = h.color;
        h.color = RED;
        x.size = h.size;
        h.size = size(h.left) + size(h.right) + 1;
        return x;
    }

    //翻转当前结点和左右孩子结点的颜色
    private void flipColors(Node h) {
        h.color = !h.color;
        h.left.color = !h.left.color;
        h.right.color = !h.right.color;
    }

    /* 从当前结点的右子结点中借一个结点给左子结点，使左子结点
       变成一个3-结点；或者3者合并成为3-结点 */
    private Node moveRedLeft(Node h) {
        flipColors(h);
        /* 若右子结点是一个3-结点，则提取一个结点给左子结点
           使其成为3-结点 */
        if (isRed(h.right.left)) {
            h.right = rotateRight(h.right);
            h = rotateLeft(h);
            flipColors(h);
        }
        return h;
    }

    /* 从当前结点的左子结点中借一个结点给右子结点，使右子结点
        变得有剩余结点使得删除一个不影响红黑树的平衡 */
    private Node moveRedRight(Node h) {
        flipColors(h);
        /* 若左子结点是一个3-结点，则提取一个结点给右子结点
           使其成为3-结点 */
        if (isRed(h.left.left)) {
            h = rotateRight(h);
            flipColors(h);
        }
        return h;
    }

    //在删除后做局部平衡处理
    private Node balance(Node h) {
        if (isRed(h.right))
            h = rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left))
            h = rotateRight(h);
        if (isRed(h.left) && isRed(h.right))
            flipColors(h);
        h.size = size(h.left) + size(h.right) + 1;
        return h;
    }

    private Node put(Node h, Key key, Value val) {
        if (h == null)
            return new Node(key, val, RED, 1);

        int cmp = key.compareTo(h.key);
        if (cmp < 0)
            h.left = put(h.left, key, val);
        else if (cmp > 0)
            h.right = put(h.right, key, val);
        else h.val = val;

        /* 红黑树比普通二叉查找树多就多在如下部分： */
        if (!isRed(h.left) && isRed(h.right))
            h = rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left))
            h = rotateRight(h);
        if (isRed(h.left) && isRed(h.right))
            flipColors(h);
        h.size = size(h.left) + size(h.right) + 1;
        return h;
    }

    private Value get(Node h, Key key) {
        while (h != null) {
            int cmp = key.compareTo(h.key);
            if (cmp < 0)
                h = h.left;
            else if (cmp > 0)
                h = h.right;
            else return h.val;
        }
        return null;
    }

    private Node deleteMin(Node h) {
        if (h.left == null)
            return null;

        /* 左子结点不是3-结点的情况下需要进行moveRedLeft
            局部调整作业，使得左子结点变成一个3结点 */
        if (!isRed(h.left) && !isRed(h.left.left))
            h = moveRedLeft(h);
        h.left = deleteMin(h.left);
        return balance(h);
    }

    private Node deleteMax(Node h) {
        if (isRed(h.left))
            h = rotateRight(h);
        if (h.right == null)
            return null;

        /* 右子结点不是3-结点的情况下需要进行moveRedRight
            局部调整作业，使得右子结点变成一个3-结点 */
        if (!isRed(h.right) && !isRed(h.right.left))
            h = moveRedRight(h);
        h.right = deleteMax(h.right);
        return balance(h);
    }

    private Node delete(Node h, Key key) {
        //欲删除结点在左子树中
        if (key.compareTo(h.key) < 0) {
            if (!isRed(h.left) && !isRed(h.left.left))
                h = moveRedLeft(h);
            h.left = delete(h.left, key);
        }
        /* 欲删除结点为当前结点或在右子树上。其中最需要注意的是要在前往右边
           的删除路径上让途径的结点变成向右偏的3-结点（即红链接只存在于父结
           点和其右子结点之间，而不是父结点和其左子结点之间），这样递归下去
           方便从无子3-结点中删除一个结点*/
        else {
            if (isRed(h.left))
                h = rotateRight(h);
            if (key.compareTo(h.key) == 0 && h.right == null)
                return null;
            if (!isRed(h.right) && !isRed(h.right.left))
                h = moveRedRight(h);
            if (key.compareTo(h.key) == 0) {
                h.val = get(h.right, min(h.right).key);
                h.key = min(h.right).key;
                h.right = deleteMin(h.right);
            } else h.right = delete(h.right, key);
        }
        return balance(h);
    }

    private void keys(Node h, Queue<Key> queue, Key low, Key high) {
        if (h == null) return;

        int lcmp = low.compareTo(h.key);
        int hcmp = high.compareTo(h.key);
        if (lcmp < 0)
            keys(h.left, queue, low, high);
        if (lcmp <= 0 && hcmp >= 0)
            queue.enqueue(h.key);
        if (hcmp > 0)
            keys(h.right, queue, low, high);
    }

    private Node min(Node h) {
        if (h.left == null) return h;
        return min(h.left);
    }

    private Node max(Node h) {
        if (h.right == null) return h;
        return max(h.right);
    }

    private int rank(Node h, Key key) {
        if (h == null) return 0;

        int cmp = key.compareTo(h.key);
        if (cmp < 0)
            return rank(h.left, key);
        else if (cmp > 0)
            return rank(h.right, key) + size(h.left) + 1;
        else return size(h.left);
    }

    private Node select(Node h, int k) {
        if (h == null) return null;

        int t = size(h.left);
        if (t > k)
            return select(h.left, k);
        else if (t < k)
            return select(h.right, k - t - 1);
        else return h;
    }

    private Node floor(Node h, Key key) {
        if (h == null) return null;

        int cmp = key.compareTo(h.key);
        if (cmp < 0)
            return floor(h.left, key);
        Node t = floor(h.right, key);
        if (t != null) return t;
        return h;
    }

    private Node ceiling(Node h, Key key) {
        if (h == null) return null;

        int cmp = key.compareTo(h.key);
        if (cmp > 0)
            return ceiling(h.right, key);
        Node t = ceiling(h.left, key);
        if (t != null) return t;
        return h;
    }

    public boolean isEmpty() {
        return root == null;
    }

    public int size() {
        return size(root);
    }

    public int size(Key low, Key high) {
        if (low.compareTo(high) >= 0)
            return 0;
        else if (!contains(high))
            return rank(high) - rank(low);
        else
            return rank(high) - rank(low) + 1;
    }

    public boolean contains(Key key) {
        return get(key) != null;
    }

    public int rank(Key key) {
        if (!contains(key))
            throw new RuntimeException("No this key");
        return rank(root, key);
    }

    public Key select(int k) {
        Node t = select(root, k);
        if (t == null) return null;
        return t.key;
    }

    public Key floor(Key key) {
        Node t = floor(root, key);
        if (t == null) return null;
        return t.key;
    }

    public Key ceiling(Key key) {
        Node t = ceiling(root, key);
        if (t == null) return null;
        return t.key;
    }

    public Value get(Key key) {
        if (root == null)
            return null;
        return get(root, key);
    }

    public void put(Key key, Value val) {
        root = put(root, key, val);
        root.color = BLACK;
    }

    public void deleteMin() {
        if (!isRed(root.left) && !isRed(root.right))
            root.color = RED;
        root = deleteMin(root);
        if (isEmpty()) root.color = BLACK;
    }

    public void deleteMax() {
        if (!isRed(root.left) && !isRed(root.right))
            root.color = RED;
        root = deleteMax(root);
        if (isEmpty()) root.color = BLACK;
    }

    public void delete(Key key) {
        if (!isRed(root.left) && !isRed(root.right))
            root.color = RED;
        root = delete(root, key);
        if (!isEmpty()) root.color = BLACK;
    }

    public Iterable<Key> keys(Key low, Key high) {
        Queue<Key> queue = new Queue<Key>();
        keys(root, queue, low, high);
        return queue;
    }

    public Iterable<Key> keys() {
        return keys(min(), max());
    }

    public Key min() {
        if (root == null) return null;
        return min(root).key;
    }

    public Key max() {
        if (root == null) return null;
        return max(root).key;
    }

    public static void main(String[] args) {
        RedBlackBST<String, Integer> redBlackBST =
                new RedBlackBST<String, Integer>();

        redBlackBST.put("a", 22);
        redBlackBST.put("b", 32);
        redBlackBST.put("c", 5);
        redBlackBST.put("d", 24);
        redBlackBST.put("h", 2);
        for (String str : redBlackBST.keys())
            StdOut.print(str + " ");
        StdOut.println();

        StdOut.println("ceiling of k: " + redBlackBST.ceiling("k"));
        StdOut.println("floor of k: " + redBlackBST.floor("k"));

        redBlackBST.delete("d");
        redBlackBST.deleteMin();
        redBlackBST.deleteMax();
        for (String str : redBlackBST.keys())
            StdOut.print(str + " ");
        StdOut.println();

    }
}
