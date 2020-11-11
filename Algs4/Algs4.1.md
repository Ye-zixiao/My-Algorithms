## 3. 查找

### 3.1 符号表

无序符号表API（也同样是有序符号表共同拥有的）：`public class ST<Key,Value>`

- `ST()`
- `void put(Key key,Value value)`
- `Value get(Key key)`
- `void delete(Key key)`
- `boolean contains(Key key)`
- `boolean isEmpty()`
- `int size()`
- `Iterable<Key> keys()`

有序符号表增加的API：

- `Key min()`
- `Key max()`
- `Key floor(Key key)`
- `Key ceiling(Key key)`
- `int rank(Key key)`
- `Key select(int k)`
- `void deleteMin()`
- `void deleteMax()`
- `int size(Key lo,Key hi)`
- `Iterable<Key> keys(Key lo,Key hi)`
- `Iterable<Key> keys()`

对于符号表（键-值对容器，在C++对应于关联容器std::map）来说，最重要的两个操作为**`void put(Key key,Value val)`和`Value get(Key key) `，分别对应着符号表的插入和搜索操作，其时间复杂度关乎着该容器的好坏。**

#### 3.1.1  无序链表符号表

容器插入操作`put()`时间复杂度：$N$

容器查找操作`get()`时间复杂度：$N$

```java
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

    //获取指定键key对应的值val
    public Value get(Key key) {
        for (Node x = first; x != null; x = x.next) {
            if (key.equals(x.key))
                return x.val;
        }
        return null;
    }

    //添加键值对
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

    /* Iterable指的是一个可迭代的容器（它必然实现了一个iterator()成员）
    	，而Iterator是作用于其上的迭代器 */
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
```



#### 3.1.2  有序数组符号表

容器插入操作`put()`时间复杂度：$N$

容器查找操作`get()`时间复杂度：$logN$

```java
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

public class BinarySearchST<Key extends Comparable<Key>, Value> {
    private Key[] keys;
    private Value[] vals;
    private int capacity = 0;
    private int N = 0;

    //重新调整符号表容器大小
    private void resize(int capacity) {
        this.capacity = capacity;
        Key[] newkeys = (Key[]) new Comparable[capacity];
        Value[] newvals = (Value[]) new Object[capacity];
        for (int i = 0; i < N; ++i) {
            newkeys[i] = keys[i];
            newvals[i] = vals[i];
        }
        keys = newkeys;
        vals = newvals;
    }

    public BinarySearchST(int capacity) {
        this.capacity = capacity;
        this.keys = (Key[]) new Comparable[capacity];
        this.vals = (Value[]) new Object[capacity];
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

    //返回小于等于指定键key的键的数量
    public int rank(Key key) {
        int low = 0, high = N - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int cmp = key.compareTo(keys[mid]);
            if (cmp < 0) high = mid - 1;
            else if (cmp > 0) low = mid + 1;
            else return mid;
        }
        return low;
    }

    public Value get(Key key) {
        if (isEmpty()) return null;
        int i = rank(key);
        if (i < N && keys[i].compareTo(key) == 0)
            return vals[i];
        return null;
    }

    public void put(Key key, Value val) {
        int i = rank(key);
        if (i < N && keys[i].compareTo(key) == 0) {
            vals[i] = val;
            return;
        }
        if (N == capacity)
            resize(capacity * 2);
        for (int j = N; j > i; --j) {
            keys[j] = keys[j - 1];
            vals[j] = vals[j - 1];
        }
        keys[i] = key;
        vals[i] = val;
        N++;
    }

    public void delete(Key key) {
        if (isEmpty()) return;
        int i = rank(key);
        if (i < N && keys[i].compareTo(key) == 0) {
            for (int j = i; j < N - 1; j++) {
                keys[j] = keys[j + 1];
                vals[j] = vals[j + 1];
            }
            keys[N - 1] = null;
            vals[N - 1] = null;
            N--;
        }
    }

    public Key min() {
        if (isEmpty()) return null;
        return keys[0];
    }

    public Key max() {
        if (isEmpty()) return null;
        return keys[N - 1];
    }

    public void deleteMin() {
        delete(min());
    }

    public void deleteMax() {
        delete(max());
    }

    //取大于等于指定键的键
    public Key ceiling(Key key) {
        return keys[rank(key)];
    }

    //取小于等于指定键的键
    public Key floor(Key key) {
        if (isEmpty()) return null;
        int i = rank(key);
        if (i < N) {
            if (keys[i].compareTo(key) == 0)
                return keys[i];
            return keys[i - 1];
        }
        return null;
    }

    public Key select(int k) {
        if (k < 0 || k >= size()) return null;
        return keys[k];
    }

    public int size(Key low, Key high) {
        if (high.compareTo(low) < 0)
            return 0;
        else if (contains(high))
            return rank(high) - rank(low) + 1;
        else
            return rank(high) - rank(low);
    }

    //返回指定键范围的键集合容器，该容器提供了一个iterator()方法
    public Iterable<Key> keys(Key low, Key high) {
        Queue<Key> q = new Queue<Key>();
        for (int i = rank(low); i < rank(high); ++i)
            q.enqueue(keys[i]);
        if (contains(high))
            q.enqueue(keys[rank(high)]);
        return q;
    }

    public Iterable<Key> keys() {
        return keys(min(), max());
    }

    public static void main(String[] args) {
        BinarySearchST<String, Integer> binarySearchST =
                new BinarySearchST<String, Integer>(10);

        binarySearchST.put("a", 32);
        binarySearchST.put("b", 5);
        binarySearchST.put("e", 43);
        binarySearchST.put("d", 64);
        for (String str : binarySearchST.keys())
            StdOut.println(str + " " + binarySearchST.get(str));
        binarySearchST.delete("a");
        StdOut.println(binarySearchST.size());
        StdOut.println(binarySearchST.min());
        StdOut.println(binarySearchST.max());
        StdOut.println(binarySearchST.floor("c"));
        StdOut.println(binarySearchST.ceiling("c"));
    }
}
```



#### 3.1.3  不同类型符号表对比

使用不同数据结构构造符号表（键-值对关联数组）的优缺点：

|    使用的数据结构    |                   实现                    | 插入时间复杂度 | 查找时间复杂度 |                        优点                        |                             缺点                             |
| :------------------: | :---------------------------------------: | :------------: | :------------: | :------------------------------------------------: | :----------------------------------------------------------: |
|   链表（顺序查找）   |            SequentialSearchST             |      $N$       |      $N$       |                   适用于小型问题                   |                   当问题规模变大时处理很慢                   |
| 有序数组（二分查找） |              BinarySearchST               |      $N$       |     $logN$     | 最优的查找效率和空间需求，能够进行有序性相关的操作 |                         插入操作很慢                         |
|      二叉查找树      |                    BST                    |   $logN$~$N$   |   $logN$~$N$   |         实现简单，能够进行有序性相关的操作         |            没有性能上界的保证，链接需要额外的空间            |
|   平衡二叉树查找树   |                RedBlackBST                |     $logN$     |     $logN$     |   最优的查找和插入效率，能够进行有序性相关的操作   |                      链接需要额外的空间                      |
|        散列表        | SeparateChain HashST LinearProbing HashST |                |                |         能够快速地查找和插入常见类型地数据         | 需要计算每种类型数据地散列，无法进行有序性线管地操作，链接和空节点需要额外的空间 |



### 3.2 二叉查找树

容器插入操作`put()`时间复杂度：$logN$~$N$

容器查找操作`get()`时间复杂度：$logN$~$N$

```java
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

public class BST<Key extends Comparable<Key>, Value> {
    private Node root;

    //二叉树节点私有类定义
    private class Node {
        private Key key;
        private Value val;
        private Node left, right;
        private int N;

        public Node(Key key, Value val, int N) {
            this.left = this.right = null;
            this.key = key;
            this.val = val;
            this.N = N;
        }
    }

    private int size(Node x) {
        if (x == null) return 0;
        return x.N;
    }

    public int size() {
        return size(root);
    }

    public boolean contains(Key key) {
        return get(key) != null;
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    private Value get(Node x, Key key) {
        if (x == null) return null;

        int cmp = key.compareTo(x.key);
        if (cmp < 0)
            return get(x.left, key);
        else if (cmp > 0)
            return get(x.right, key);
        else return x.val;
    }

    //在二叉搜索树中查找指定键的元素
    public Value get(Key key) {
        return get(root, key);
    }

    private Node put(Node x, Key key, Value val) {
        if (x == null) return new Node(key, val, 1);

        int cmp = key.compareTo(x.key);
        if (cmp < 0)
            x.left = put(x.left, key, val);
        else if (cmp > 0)
            x.right = put(x.right, key, val);
        else x.val = val;
        //对于当前节点而言，更新N没什么用，但是对其父节点及其祖先节点是必要的
//        x.N=size(x.left)+size(x.right)+1;
        x.N++;
        return x;
    }

    //向二叉搜索树元素插入操作
    public void put(Key key, Value val) {
        root = put(root, key, val);
    }

    private Node min(Node x) {
        if (x.left == null) return x;
        return min(x.left);
    }

    public Key min() {
        return min(root).key;
    }

    private Node max(Node x) {
        if (x.right == null) return x;
        return max(x.right);
    }

    public Key max() {
        return max(root).key;
    }

    //下取整
    private Node floor(Node x, Key key) {
        if (x == null) return null;

        int cmp = key.compareTo(x.key);
        if (cmp == 0) return x;
        else if (cmp < 0) //若key小于当前节点的key，则继续到该节点的左子树去找
            return floor(x.left, key);
        Node t = floor(x.right, key);
        if (t != null) return t;
        else return x;
    }

    public Key floor(Key key) {
        Node t = floor(root, key);
        if (t == null) return null;
        else return t.key;
    }

    //上取整
    private Node ceiling(Node x, Key key) {
        if (x == null) return null;

        int cmp = key.compareTo(x.key);
        if (cmp == 0) return x;
        else if (cmp > 0)
            return ceiling(x.right, key);
        Node t = ceiling(x.left, key);
        if (t != null) return t;
        else return x;
    }

    public Key ceiling(Key key) {
        Node t = ceiling(root, key);
        if (t == null) return null;
        return t.key;
    }

    //选取排位顺序的键
    private Node select(Node x, int k) {
        if (x == null) return null;

        int t = size(x.left);
        if (t > k) return select(x.left, k);
        else if (t < k) return select(x.right, k - t - 1);
        else return x;
    }

    public Key select(int k) {
        Node t = select(root, k);
        if (t == null) return null;
        else return t.key;
    }

    //获取指定键的位置
    private int rank(Node x, Key key) {
        if (x == null) return 0;

        int cmp = key.compareTo(x.key);
        if (cmp < 0)
            return rank(x.left, key);
        else if (cmp > 0)
            return size(x.left) + 1 + rank(x.right, key);
        else return size(x.left);
    }

    public int rank(Key key) {
        return rank(root, key);
    }

    private void keys(Node x, Queue<Key> queue, Key low, Key high) {
        if (x == null) return;

        int lcomp = low.compareTo(x.key);
        int hcomp = high.compareTo(x.key);
        if (lcomp < 0) keys(x.left, queue, low, high);//先将左子树中符合要求的元素加入queue中
        if (lcomp <= 0 && hcomp >= 0) queue.enqueue(x.key);//再将自己也加入到queue中
        if (hcomp > 0) keys(x.right, queue, low, high);//最后将右子树中符合要求的元素加入到queue中
    }

    //返回存储指定范围键的可迭代容器
    public Iterable<Key> keys(Key low, Key high) {
        Queue<Key> queue = new Queue<Key>();
        keys(root, queue, low, high);
        return queue;
    }

    public Iterable<Key> keys() {
        return keys(min(), max());
    }

    private Node deleteMin(Node x) {
        if (x.left == null) return x.right;
        x.left = deleteMin(x.left);
        x.N = size(x.left) + size(x.right) + 1;
        return x;
    }

    public void deleteMin() {
        root = deleteMin(root);
    }

    private Node deleteMax(Node x) {
        if (x.right == null) return x.left;
        x.right = deleteMax(x.right);
        x.N = size(x.left) + size(x.right) + 1;
        return x;
    }

    public void deleteMax() {
        root = deleteMax(root);
    }

    private Node delete(Node x, Key key) {
        if (x == null) return null;

        int cmp = key.compareTo(x.key);
        if (cmp < 0)
            x.left = delete(x.left, key);
        else if (cmp > 0)
            x.right = delete(x.right, key);
        else {
            //待删结点只有一个子树
            if (x.right == null) return x.left;
            else if (x.left == null) return x.right;
            Node t = x;//保存待删结点
            x = min(x.left);//获取待删结点右子树最小结点引用x
            x.right = deleteMin(t.right);//将待删结点右子树最小结点删除，并将剩余部分挂载到x的右边
            x.left = t.left;//待删结点的左子树挂在新结点的左边
        }
        return x;
    }

    public void delete(Key key) {
        root = delete(root, key);
    }

    private void show(Node x) {
        if (x == null) return;
        show(x.left);
        StdOut.println(x.key);
        show(x.right);
    }

    public void show() {
        show(root);
    }
}
```



#### 3.2.1  插入操作

在递归前沿着树向下走寻找合适的位置，然后以递归创建了新结点，递归调用返回途中沿着树向上爬时更新结点的计数值

```java
    private Node put(Node x, Key key, Value val) {
        if (x == null) return new Node(key, val, 1);

        int cmp = key.compareTo(x.key);
        if (cmp < 0)
            x.left = put(x.left, key, val);
        else if (cmp > 0)
            x.right = put(x.right, key, val);
        else x.val = val;
        //对于当前节点而言，更新N没什么用，但是对其父节点及其祖先节点是必要的
//        x.N=size(x.left)+size(x.right)+1;
        x.N++;
        return x;
    }

    //向二叉搜索树元素插入操作
    public void put(Key key, Value val) {
        root = put(root, key, val);
    }
```

图示：

<img src="E:/Desktop/Algorithms/Algs4/image/2020-11-08 111923.png" alt="2020-11-08 111923" style="zoom: 80%;" />

#### 3.2.2  查找操作

类似于插入操作

```java
    private Value get(Node x, Key key) {
        if (x == null) return null;

        int cmp = key.compareTo(x.key);
        if (cmp < 0)
            return get(x.left, key);
        else if (cmp > 0)
            return get(x.right, key);
        else return x.val;
    }

    //在二叉搜索树中查找指定键的元素
    public Value get(Key key) {
        return get(root, key);
    }
```



#### 3.2.3  删除操作

*删除最小结点*的关键在于：将待删除结点的右结点接到待删除结点的父结点的左边

```java
    private Node deleteMin(Node x) {
        if (x.left == null) return x.right;
        x.left = deleteMin(x.left);
        x.N = size(x.left) + size(x.right) + 1;
        return x;
    }

	public void deleteMin() {
        root = deleteMin(root);
    }
```

图示：

<img src="E:/Desktop/Algorithms/Algs4/image/2020-11-08 112439.png" alt="2020-11-08 112439" style="zoom:80%;" />

*删除任意结点*的关键在于：`区分只有一个或者无子树的结点（可以看作是像deleteMin()一样的操作）和左右子树同时存在的结点`。无子树或者只有一个子树的结点只要将左子树（若存在）或者右子树接到待删结点的父结点的左/右边。而**左右子树同时存在的结点，需要在删除时暂时记录待删结点的引用，然后取出待删结点右子树中的最小结点用其来替代待删结点（需要将其执行deleteMin()操作），然后将待删结点的左右子树挂在该替代节点的左右两边。**

```java
    private Node delete(Node x, Key key) {
        if (x == null) return null;

        int cmp = key.compareTo(x.key);
        if (cmp < 0)
            x.left = delete(x.left, key);
        else if (cmp > 0)
            x.right = delete(x.right, key);
        else {
            //待删结点只有一个子树
            if (x.right == null) return x.left;
            else if (x.left == null) return x.right;
            //保存待删结点
            Node t = x;
            //获取待删结点右子树最小结点引用x
            x = min(x.left);
            //将待删结点右子树最小结点删除，并将剩余部分挂载到x的右边
            x.right = deleteMin(t.right);
            //待删结点的左子树挂在新结点的左边
            x.left = t.left;
        }
        return x;
    }

    public void delete(Key key) {
        root = delete(root, key);
    }
```

图示：

<img src="E:/Desktop/Algorithms/Algs4/image/2020-11-08 113310.png" alt="2020-11-08 113310" style="zoom:80%;" />



#### 3.2.4  范围(遍历)操作

这里的范围操作关键就是使用中序遍历，将二叉搜索树中的结点按照从小到大的顺序加入到队列之中

```java
    private void keys(Node x, Queue<Key> queue, Key low, Key high) {
        if (x == null) return;

        int lcomp = low.compareTo(x.key);
        int hcomp = high.compareTo(x.key);
        //先将左子树中符合要求的元素加入queue中
        if (lcomp < 0) keys(x.left, queue, low, high);
        //再将自己也加入到queue中
        if (lcomp <= 0 && hcomp >= 0) queue.enqueue(x.key);
        //最后将右子树中符合要求的元素加入到queue中
        if (hcomp > 0) keys(x.right, queue, low, high);
    }

    //返回存储指定范围键的可迭代容器
    public Iterable<Key> keys(Key low, Key high) {
        Queue<Key> queue = new Queue<Key>();
        keys(root, queue, low, high);
        return queue;
    }

    public Iterable<Key> keys() {
        return keys(min(), max());
    }

    private Node deleteMin(Node x) {
        if (x.left == null) return x.right;
        x.left = deleteMin(x.left);
        x.N = size(x.left) + size(x.right) + 1;
        return x;
    }
```

图示：

![2020-11-08 115926](E:/Desktop/Algorithms/Algs4/image/2020-11-08 115926.png)

#### 3.2.5 上下取整操作

以下取整为例，其关键点在于：若在结点遍历过程中遇到一个比自己小的结点，就先暂时记录它然后在它的右子树中继续查找（试图找到比这个节点更合适的结点）。若找不到就仍然使用这个暂存的点进行返回，否则使用找到的合适点进行返回。

```java
    //下取整
    private Node floor(Node x, Key key) {
        if (x == null) return null;

        int cmp = key.compareTo(x.key);
        if (cmp == 0) return x;
        else if (cmp < 0) //若key小于当前节点的key，则继续到该节点的左子树去找
            return floor(x.left, key);
        Node t = floor(x.right, key);
        if (t != null) return t;
        else return x;
    }

    public Key floor(Key key) {
        Node t = floor(root, key);
        if (t == null) return null;
        else return t.key;
    }
```

图示：

<img src="E:/Desktop/Algorithms/Algs4/image/2020-11-08 120041.png" alt="2020-11-08 120041" style="zoom:80%;" />



#### 3.2.6  排位选择操作

选取指定位顺序的键select()方法的关键在于：根据每一个结点中的N成员与欲取结点的位置进行比较，若欲取结点位置大于当前节点的N则到该节点的右结点去寻找（不过欲取结点位置要减去左边的结点数量）；若小于则在左边递归寻找；若相等则返回当前结点。

```java
    //选取排位顺序的键
    private Node select(Node x, int k) {
        if (x == null) return null;

        int t = size(x.left);
        if (t > k) return select(x.left, k);
        else if (t < k) return select(x.right, k - t - 1);
        else return x;
    }

    public Key select(int k) {
        Node t = select(root, k);
        if (t == null) return null;
        else return t.key;
    }
```

图示：

<img src="E:/Desktop/Algorithms/Algs4/image/2020-11-08 120703.png" alt="2020-11-08 120703" style="zoom:80%;" />

而返回指定键位置的rank()方法，则很容易用size()方法递归计算出来

```java
    //获取指定键的位置
    private int rank(Node x, Key key) {
        if (x == null) return 0;

        int cmp = key.compareTo(x.key);
        if (cmp < 0)
            return rank(x.left, key);
        else if (cmp > 0)
            return size(x.left) + 1 + rank(x.right, key);
        else return size(x.left);
    }

    public int rank(Key key) {
        return rank(root, key);
    }
```

 ### 3.3 平衡查找树

#### 3.3.1  2-3树

2-3树指的是由2-结点和3-结点共同构成的二叉树，其中2-结点具有两个指向孩子结点的链接（左孩子比它小，右孩子比它大），而3-结点具有三个指向孩子结点的链接（左孩子比它小，中间孩子键值介于3-结点中两个键之间，右孩子比它大）。***一棵完美平衡的2-3查找树中的所有空链接null到根结点的距离总是相同的，且查找/插入操作总是能够在$logN$时间复杂度内完成***。

<img src="image/2020-11-11 100146.png" alt="2020-11-11 100146" style="zoom:80%;" />

##### 3.3.1.1  2-3树的插入操作





#### 3.3.2  红黑树

***红黑树的本质就是通过普通二叉搜索树来实现完美平衡2-3树***，而2-3树可以保证我们的查找/插入操作维持在$logN$级别

```java
import edu.princeton.cs.algs4.StdOut;

import java.util.concurrent.BlockingDeque;

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

    /* 辅助函数 */
    private boolean isRed(Node x) {
        if (x == null) return false;
        return x.color == RED;
    }

    private int size(Node x) {
        if (x == null)
            return 0;
        return x.size;
    }

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

    private void flipColors(Node h) {
        h.color = !h.color;
        h.left.color = !h.left.color;
        h.right.color = !h.right.color;
    }

    private Node moveRedLeft(Node h) {
        flipColors(h);
        if (isRed(h.right.left)) {
            h.right = rotateRight(h.right);
            h = rotateLeft(h);
            flipColors(h);
        }
        return h;
    }

    private Node moveRedRight(Node h) {
        flipColors(h);
        if (isRed(h.left.left)) {
            h = rotateRight(h);
            flipColors(h);
        }
        return h;
    }

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

        if (!isRed(h.left) && isRed(h.right))
            h = rotateLeft(h);
        if (isRed(h.left) && isRed(h.left.left))
            h = rotateRight(h);
        if (isRed(h.left) && isRed(h.right))
            flipColors(h);
        h.size = size(h.left) + size(h.right) + 1;
        return h;
    }

    private Node get(Node h, Key key) {
        while (h != null) {
            int cmp = key.compareTo(h.key);
            if (cmp < 0)
                h = h.left;
            else if (cmp > 0)
                h = h.right;
            else return h;
        }
        return null;
    }

    private Node deleteMin(Node h) {
        if (h.left == null)
            return null;
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
        if (!isRed(h.right) && !isRed(h.right.left))
            h = moveRedRight(h);
        h.right = deleteMax(h.right);
        return balance(h);
    }

    public boolean isEmpty() {
        return root == null;
    }

    public int size() {
        return size(root);
    }

    public boolean contains(Key key) {
        return get(key) != null;
    }

    public Value get(Key key) {
        if (root == null)
            return null;
        return get(root, key).val;
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

    public static void main(String[] args) {
        RedBlackBST<String, Integer> redBlackBST =
                new RedBlackBST<String, Integer>();

        redBlackBST.put("a", 22);
        redBlackBST.put("b", 32);
        redBlackBST.put("c", 5);
        redBlackBST.put("d", 24);
        redBlackBST.put("h", 2);
        StdOut.println("tree size: " + redBlackBST.size());
        StdOut.println("c's value: " + redBlackBST.get("c"));
        redBlackBST.deleteMin();
        StdOut.println("current tree size: " + redBlackBST.size());
        if (redBlackBST.contains("b"))
            StdOut.println("b");
        if (redBlackBST.contains("c"))
            StdOut.println("c");
        if (redBlackBST.contains("d"))
            StdOut.println("d");
        redBlackBST.deleteMin();
        redBlackBST.deleteMax();
        redBlackBST.deleteMax();
        StdOut.println("current tree size: " + redBlackBST.size());
        StdOut.println("current c: " + redBlackBST.get("c"));
    }
}
```



##### 3.3.2.1  插入操作

1、向2-结点进行插入



2、向3-结点进行插入



3、中间结点的向上（插入）传递

该步骤在递归返回的时候完成相应的左/右旋转



##### 3.3.2.2  删除最小/大值操作



##### 3.3.2.3  删除操作

