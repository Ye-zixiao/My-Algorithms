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
|        散列表        | SeparateChain HashST LinearProbing HashST |   $1$~$logN$   |   $1$~$logN$   |         能够快速地查找和插入常见类型的数据         | 需要计算每种类型数据地散列，无法进行有序性相关的操作，链接和空节点需要额外的空间 |



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

C语言实现：

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 64
#undef min
#undef max

struct Node {
	char str[MAXLINE];
	int val;
	struct Node* left, * right;
};

struct BST {
	struct Node* root;
};


struct Node* CreateNode(const char* buf, int value) {
	struct Node* node;

	if ((node = malloc(sizeof(struct Node))) == NULL)
		return NULL;
	strcpy(node->str, buf);
	node->val = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}


void InitBST(struct BST* bst) {
	bst->root = NULL;
}


void destroy(struct Node* h) {
	if (h == NULL)return;

	if (h->left)  destroy(h->left);
	if (h->right) destroy(h->right);
	free(h);
}


void BSTDestroy(struct BST* bst) {
	if (bst == NULL)return;
	destroy(bst->root);
	bst->root = NULL;
}


//插入操作
struct Node* insert(struct Node* h, const char* buf, int value) {
	if (h == NULL)
		return CreateNode(buf, value);

	int cmp = strcmp(buf, h->str);
	if (cmp < 0)
		h->left = insert(h->left, buf, value);
	else if (cmp > 0)
		h->right = insert(h->right, buf, value);
	else
		h->val = value;
	return h;
}


void BSTInsert(struct BST* bst, const char* buf, int value) {
	bst->root = insert(bst->root, buf, value);
}


//查找操作
int get(const struct Node* h, const char* buf) {
	int cmp;

	if (h == NULL)return -1;
	if ((cmp = strcmp(buf, h->str)) < 0)
		return get(h->left, buf);
	else if (cmp > 0)
		return get(h->right, buf);
	else return h->val;
}


int BSTGet(const struct BST* bst, const char* buf) {
	if (bst == NULL)return -1;
	return get(bst->root, buf);
}


//最小值
struct Node* min(struct Node* h) {
	if (h == NULL)return NULL;
	if (h->left != NULL)
		return min(h->left);
	else return h;
}


const char* BSTMin(const struct BST* bst) {
	if (bst == NULL)return NULL;
	return min(bst->root)->str;
}


//最大值
struct Node* max(struct Node* h) {
	if (h == NULL)return NULL;
	if (h->right != NULL)
		return max(h->right);
	else return h;
}


const char* BSTMax(const struct BST* bst) {
	if (bst == NULL) return NULL;
	return max(bst->root)->str;
}


//删除最小值
struct Node* deleteMin(struct Node* h) {
	struct Node* t;

	if (h == NULL)return NULL;
	if (h->left != NULL) {
		h->left = deleteMin(h->left);
		return h;
	}
	else {
		t = h->right;
		free(h);
		return t;
	}
}


void BSTDeleteMin(struct BST* bst) {
	if (bst == NULL)return;
	bst->root = deleteMin(bst->root);
}


//删除最大值
struct Node* deleteMax(struct Node* h) {
	struct Node* t;

	if (h == NULL)return NULL;
	if (h->right != NULL) {
		h->right = deleteMax(h->right);
		return h;
	}
	else {
		t = h->left;
		free(h);
		return t;
	}
}


void BSTDeleteMax(struct BST* bst) {
	if (bst == NULL)return;
	bst->root = deleteMax(bst->root);
}


//任意删除
struct Node* delete(struct Node* h, const char* buf) {
	//t表示替代删除结点的结点指针,right用来表示右子树的根节点（可能跟原来不一样）
	struct Node* t/*, * right*/;
	int cmp;

	if (h == NULL)return NULL;
	if ((cmp = strcmp(buf, h->str)) < 0) {
		h->left = delete(h->left, buf);
		return h;
	}
	else if (cmp > 0) {
		h->left = delete(h->right, buf);
		return h;
	}
	else {
		//若当前结点的右子树为空
		if (h->right == NULL) {
			t = h->left;
			free(h);
			return t;
		}
		//若当前结点的右子树非空
		else {
			strcpy(h->str, min(h->right)->str);
			h->val = min(h->right)->val;
			h->right = deleteMin(h->right);
			return h;
		}
	}
}


void BSTDelete(struct BST* bst, const char* buf) {
	if (bst == NULL)return;
	bst->root = delete(bst->root, buf);
}


//打印操作（中序）
void print(const struct Node* h) {
	if (h == NULL)return;

	if (h->left != NULL)
		print(h->left);
	printf("str: %s, value: %d\n", h->str, h->val);
	if (h->right != NULL)
		print(h->right);
}


void BSTPrint(const struct BST* bst) {
	print(bst->root);
	putchar('\n');
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

> 注意：这里采用的是使用return返回更新好结点的指针（引用）的方式递归向上传递给父结点，通知其最新的左/右子结点的指针（引用），从而来完成子结点的更新（删除或者删除）。例如如下形式就是典型的使用形式：
>
> `struct Node *deleteMin(struct Node*h);`
>
> `h->left=deleteMin(h->left);`
>
> 通过递归返回的时候更新父结点的指向子结点的指针（引用）会使用很方便。但若使用二级指针的方式来更新的话，会显得比较麻烦。可能需要如下的形式：
>
> `voide deleteMin(struct Node**h);`



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

*删除任意结点*的关键在于：`区分只有一个或者无子树的结点（可以看作是像deleteMin()一样的操作）和左右子树同时存在的结点`。无子树或者只有一个子树的结点只要将左子树（若存在）或者右子树接到待删结点的父结点的左/右边。而**左右子树同时存在的结点，需要在删除时暂时记录待删结点的引用，然后取出待删结点右子树中的最小结点用其来替代待删结点（需要将其执行deleteMin()操作），然后将调整后的左右子树挂在该替代节点的左右两边。**

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

2-3树指的是由2-结点和3-结点共同构成的二叉树，其中2-结点具有两个指向孩子结点的链接（左孩子比它小，右孩子比它大），而3-结点具有三个指向孩子结点的链接（左孩子比它小，中间孩子键值介于3-结点中两个键之间，右孩子比它大）。**一棵完美平衡的2-3查找树中的所有空链接null到根结点的距离总是相同的，且查找/插入操作总是能够在$logN$时间复杂度内完成**。

<img src="image/2020-11-11 100146.png" alt="2020-11-11 100146" style="zoom:80%;" />



2-3树的插入操作可以总体分成如下两种情况：

1. 向2-结点进行插入：

   此时的处理很简单，2-结点直接变成3-结点即可。

2. 向3-结点进行插入：

   则操作时会临时产生一个临时的4-结点，该4-结点然后就会分解将中键（中间结点）提出给父结点（此时等效于向其父结点又进行了一次插入操作）。①*若父结点原来是2-结点*，则其结果就如同1）的结果相同（父结点变成了一个3-结点），此时插入操作就到此为止；②*若父结点原来是3-结点*，则父结点也同样的会临时变成一个4-结点，此时该父结点又一次提出一个中间结点给它的父结点...若此递归下去，直到其遇到一个为2-结点的父结点（*一种比较特殊的情况就是若该中间结点向上插入的过程中遇到了根结点*，使得根结点变成了一个临时4-结点，此时该临时4-结点会直接分解成3个2结点，使树增高1层）。
   
   <img src="image/2020-11-12 213802.png" alt="2020-11-12 213802" style="zoom:80%;" />
   
   

#### 3.3.2  红黑树

**红黑树(左倾)的本质就是通过普通二叉搜索树来实现完美平衡2-3树**，而通过这种方式实现的2-3树可以保证我们的查找和插入操作都维持在$logN$级别

```java
import edu.princeton.cs.algs4.BlockFilter;
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
```

C语言实现：

```c
/**
 * 左倾红黑树实现
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODESTRLEN 64
#define RED 1
#define BLACK 0

#define MAX(l,r) ((l)>(r)?(l):(r))

struct Node {
	char str[NODESTRLEN];
	int val;
	int color;
	struct Node* left, * right;
};

struct RBT {
	struct Node* root;
};


//结点创建
struct Node* NodeCreate(const char* buf, int value) {
	struct Node* node;
	if ((node = malloc(sizeof(struct Node))) == NULL)
		return NULL;
	strncpy(node->str, buf, NODESTRLEN - 1);
	node->str[NODESTRLEN - 1] = '\0';
	node->val = value;
	node->color = RED;
	node->left = NULL;
	node->right = NULL;
	return node;
}


//红黑树初始化
void RBTInit(struct RBT* rbt) {
	rbt->root = NULL;
}


void NodeDestroy(struct Node* h) {
	if (h == NULL)return;

	if (h->left)NodeDestroy(h->left);
	if (h->right)NodeDestroy(h->right);
	free(h);
}


//红黑树销毁
void RBTDestroy(struct RBT* rbt) {
	if (rbt == NULL)return;
	NodeDestroy(rbt->root);
	rbt->root = NULL;
}


int isEmpty(const struct RBT* rbt) {
	return (rbt == NULL || rbt->root == NULL) ? 1 : 0;
}


//判断当前结点是否为红结点
int isRed(const struct Node* node) {
	return node == NULL ? 0 : node->color ? 1 : 0;
}


int NodeSize(const struct Node* h) {
	if (h == NULL)return 0;
	return NodeSize(h->left) + NodeSize(h->right) + 1;
}


//结点总数
int RBTSize(const struct RBT* rbt) {
	if (rbt == NULL)return 0;
	return NodeSize(rbt->root);
}


int height(const struct Node* node) {
	if (node == NULL)return 0;
	int hs = MAX(height(node->left), height(node->right));
	return hs + ((node->color == BLACK) ? 1 : 0);
}


//树高
int RBTHeight(const struct RBT* rbt) {
	return rbt == NULL ? 0 : height(rbt->root);
}


//颜色翻转
void flipColors(struct Node* h) {
	h->color = !h->color;
	h->left->color = !h->left->color;
	h->right->color = !h->right->color;
}


//左旋
struct Node* rotateLeft(struct Node* h) {
	struct Node* x = h->right;

	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = RED;
	return x;
}


//右旋
struct Node* rotateRight(struct Node* h) {
	struct Node* x = h->left;

	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = RED;
	return x;
}


/**
 * 从当前结点的右子树中提出个结点使左子结点变成非2-结点
 */
struct Node* removeLeft(struct Node* h) {
	flipColors(h);
	if (isRed(h->right->left)) {
		h->right = rotateRight(h->right);
		h = rotateLeft(h);
		flipColors(h);
	}
	return h;
}


/**
 * 从当前结点的左子树中提出个结点使右子结点变成非2-结点
 */
struct Node* removeRight(struct Node* h) {
	flipColors(h);
	if (isRed(h->left->left)) {
		h = rotateRight(h);
		flipColors(h);
	}
	return h;
}


struct Node* NodeMin(struct Node* node) {
	if (node == NULL)return NULL;
	return node->left ? NodeMin(node->left) : node;
}


//返回最小键
const char* RBTMin(const struct RBT* rbt) {
	return isEmpty(rbt) ? NULL : NodeMin(rbt->root)->str;
}


struct Node* NodeMax(struct Node* node) {
	if (node == NULL)return NULL;
	return node->right ? NodeMax(node->right) : node;
}


//返回最大键
const char* RBTMax(const struct RBT* rbt) {
	return isEmpty(rbt) ? NULL : NodeMax(rbt->root)->str;
}


struct Node* NodePut(struct Node* h, const char* buf, int value) {
	int cmp;

	if (h == NULL)
		return NodeCreate(buf, value);
	if ((cmp = strcmp(buf, h->str)) < 0) {
		h->left = NodePut(h->left, buf, value);
	}
	else if (cmp > 0) {
		h->right = NodePut(h->right, buf, value);
	}
	else h->val = value;

	if (!isRed(h->left) && isRed(h->right))
		h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left))
		h = rotateRight(h);
	if (isRed(h->left) && isRed(h->right))
		flipColors(h);
	return h;
}


//插入操作
void RBTPut(struct RBT* rbt, const char* buf, int value) {
	if (rbt == NULL) {
		fprintf(stderr, "rbt is null\n");
		return;
	}
	rbt->root = NodePut(rbt->root, buf, value);
	rbt->root->color = BLACK;
}


int get(const struct Node* h, const char* buf) {
	int cmp;

	if (h == NULL)return -1;
	if ((cmp = strcmp(buf, h->str)) < 0)
		return get(h->left, buf);
	else if (cmp > 0)
		return get(h->right, buf);
	return h->val;
}


//查找
int RBTGet(const struct RBT* rbt, const char* buf) {
	return rbt == NULL ? -1 : get(rbt->root, buf);
}


//检测是否存在该键
int contains(const struct RBT* rbt, const char* buf) {
	return RBTGet(rbt, buf) != -1;
}


//在删除结点后调用该函数来重新对结点进行调整，使其保持平衡
struct Node* balance(struct Node* h) {
	if (isRed(h->right))
		h = rotateLeft(h);
	if (isRed(h->left) && isRed(h->left->left))
		h = rotateRight(h);
	if (isRed(h->left) && isRed(h->right))
		flipColors(h);
	return h;
}


struct Node* deleteMin(struct Node* h) {
	if (h == NULL)return NULL;
	if (h->left == NULL) {
		free(h);
		return NULL;
	}
	if (!isRed(h->left) && !isRed(h->left->left))
		h = removeLeft(h);
	h->left = deleteMin(h->left);
	return balance(h);
}


//删除最小结点
void RBTDeleteMin(struct RBT* rbt) {
	if (rbt == NULL)return;
	if (!isRed(rbt->root->left) && !isRed(rbt->root->right))
		rbt->root->color = RED;
	rbt->root = deleteMin(rbt->root);
	if (!isEmpty(rbt))rbt->root->color = BLACK;
}


struct Node* deleteMax(struct Node* h) {
	if (h == NULL)return NULL;
	if (isRed(h->left))
		h = rotateRight(h);
	if (h->right == NULL) {
		free(h);
		return NULL;
	}
	if (!isRed(h->right) && !isRed(h->right->left))
		h = removeRight(h);
	h->right = deleteMax(h->right);
	return balance(h);
}


//删除最大结点
void RBTDeleteMax(struct RBT* rbt) {
	if (rbt == NULL)return;
	if (!isRed(rbt->root->left) && !isRed(rbt->root->right))
		rbt->root->color = RED;
	rbt->root = deleteMax(rbt->root);
	if (!isEmpty(rbt))rbt->root->color = BLACK;
}


struct Node* delete(struct Node* h, const char* buf) {
	if (h == NULL)return NULL;

	if (strcmp(buf, h->str) < 0) {
		if (!isRed(h->left) && !isRed(h->left->left))
			h = removeLeft(h);
		h->left = delete(h->left, buf);
	}
	else {
		if (isRed(h->left))
			h = rotateRight(h);
        /* 算法4书中使用的key.compareTo(h.key)其实没有什么用，
        	其比较顶多就是确保就是我们需要找的结点，但实际上即使
        	不适用这个我们也可以确保。因为我们要删的结点肯定会通过
        	上面执行的局部调整变成一个3-结点中的一个，这样才可以
        	使删除操作变得方便，而且它一定是既没有左子结点也肯定
        	没有右子结点!😋*/
		if (/*strcmp(buf,h->str)==0 && */h->right == NULL) {
			free(h);
			return NULL;
		}
		if (!isRed(h->right) && !isRed(h->right->left))
			h = removeRight(h);

		if (strcmp(buf, h->str) == 0) {
			struct Node* t = NodeMin(h->right);
			strcpy(h->str, t->str);
			h->val = t->val;
			h->right = deleteMin(h->right);
		}
		else h->right = delete(h->right, buf);
	}
	return balance(h);
}


//任意删除
void RBTDelete(struct RBT* rbt, const char* buf) {
	if (isEmpty(rbt)) {//检查红黑树是否为空？
		fprintf(stderr, "rbt is null or is empty\n");
		return;
	}
	if (!contains(rbt, buf)) {//检测红黑树中是否包含该键
		fprintf(stderr, "key: %s is not contain!\n", buf);
		return;
	}

	if (!isRed(rbt->root->left) && !isRed(rbt->root->right))
		rbt->root->color = RED;
	rbt->root = delete(rbt->root, buf);
	if (!isEmpty(rbt))rbt->root->color = BLACK;
}


static void printNode(const struct Node* node) {
	if (node == NULL)return;
	if (node->left)
		printNode(node->left);
	printf("str: %s, val: %d, color: %d\n", node->str, node->val, isRed(node));
	if (node->right)
		printNode(node->right);
}


//打印
static void RBTPrint(const struct RBT* rbt) {
	if (rbt == NULL) {
		fprintf(stderr, "rbt is null\n");
		return;
	}
	printNode(rbt->root);
}
```



##### 3.3.2.1  二叉搜索树改造

为了使得上述普通的二叉搜索树能够支持红黑树的实现，我们需要在`private class Node`中加入一个名为color的布尔类型变量，当color==RED(true)表示该结点是一个红结点，这意味着该结点和其父结点组成了一个逻辑上的3-结点；否则为黑结点，这意味着该结点单独组成一个2-结点。

<img src="image/2020-11-14 092242.png" alt="2020-11-14 092242" style="zoom:80%;" />

除此之外我们还对红黑树做出如下的规定（这样我们的红黑树就如同下图一样）：

- 红链接均为左链接（纯粹是为了处理的情况少点，方便）
- 没有任何一个结点同时与两条红链接同时相连
- 该树是完美黑色平衡的，即任意空链接到它的黑链接数量都是相同的
- 根结点永远都是黑结点，空结点也永远都是黑结点

<img src="image/2020-11-14 092401.png" alt="2020-11-14 092401" style="zoom:80%;" />

这样做的好处在于代码复用性高，只要稍微对二叉搜索树进行改进，基本上只要对结点类定义、`put()`和`delete()`等方法进行改造就可以。

##### 3.3.2.1  左右旋操作

为了实现结点的插入，我们必须在之前了解下结点的左旋和右旋操作。**左旋**指的是以当前结点为中心进行逆时针方向旋转，该操作本质就是将该子树的根结点设置为原根结点的右子结点。比如它可以使得一个红链接为右链接的3-结点变成一个红链接为左链接的3-结点。

```java
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
```

<img src="image/2020-11-14 094122.png" alt="2020-11-14 094122" style="zoom:80%;" />

<img src="image/2020-11-14 094141.png" alt="2020-11-14 094141" style="zoom:80%;" />

而**右旋**与之相反，它以当前节点为中心进行顺时针方向旋转，该操作本质上就是将该指数的根结点设置为原根结点的左子结点。比如它可以将一个红链接为左链接的3-结点变成一个红链接为右链接的3-结点。

```java
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
```

<img src="image/2020-11-14 094443.png" alt="2020-11-14 094443" style="zoom:80%;" />

<img src="image/2020-11-14 094501_LI.jpg" alt="2020-11-14 094501_LI" style="zoom:80%;" />



##### 3.3.2.2  插入操作

在此之前，我们需要做如下规定：*新插入的结点总是红结点*

1. **向2-结点进行插入**

若向一个2-结点进行插入，则2-结点会直接变成3-结点。对于一个向左插入的红结点而言，新的结点对符合我们的要求，因此我们不需要做什么；但是对于一个向右插入的红结点而言，由于其插入的结点的红链接是右链接不符合我们“红链接必须是右链接”的前提假设，因此我们需要对其根结点进行左旋操作。

<img src="image/2020-11-14 095322.png" alt="2020-11-14 095322" style="zoom:80%;" />

2. **向3-结点进行插入**

若向一个3-结点进行插入，则按照2-3树的插入规则该结点会临时变成一个4-结点，然后取出其中间结点向上给原3-结点的父结点（本质就是将中间结点插入到其父结点中。而插入操作又等同于新来的结点的color==RED，所以在处理3-结点插入的时候特别需要面对子结点是红色的多种情况）。向3-结点插入新结点有如下3种情况：

- 向3-结点的右边插入

此时的处理就是直接变成临时4-结点，然后向上传递中间结点，而左右结点被分解变成了两个单独的2-结点。在程序中操作就只是简单的翻转颜色`flipColors()`而已

- 向3-结点的左边插入

此时的处理是让其直接变成临时4-结点，然后做右旋操作，最后向上传递中间结点，然后左右结点被分解成两个独立的2-结点。在程序中操作为左旋`rotateLeft()`+翻转颜色`flipColors()`

- 向3-结点的中间插入

此时的处理是让其直接变成临时的4-结点，然后做左旋操作，然后再右旋，最后向上传递中间结点，左右结点被分解成两个独立的2-结点。在程序中操作为左旋`rotateLeft()`+右旋`rotateRight()`+翻转颜色`flipColors()`

<img src="image/2020-11-14 101137.png" alt="2020-11-14 101137" style="zoom:80%;" />

3. **中间结点的向上（插入）传递**

因为我们上面提到过，特别是对于向3-结点插入的时候必然存在一个向父结点插入中间结点的过程，因此简简单单找到合适的插入点然后做相应的旋转操作什么的显然是不够的。我们必须使用递归的方式，通过递归不断向下查找到合适的位置插入，然后再递归返回的途中使用相应的处理手段（旋转、翻转颜色使红结点变黑，黑结点变红）不断从下向上调整好所有路径上的结点，这样即使途中有向上传递中间结点的情况这样也能够完美的处理。

由于只有向3-结点插入新结点才会发生向上传递的情况，所以我们可以以向3-结点插入的三种情况（左边插入、中间插入、右边插入）为模板做出`if() {  /*...*/ }`的调整，下图是3-结点插入后状态转移图（其中囊括了所有的处理情况），其中的①②③是我们的处理顺序：

<img src="image/2020-11-14 101422.png" alt="2020-11-14 101422" style="zoom:80%;" />

```java
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
```



##### 3.3.2.2  删除最小/大值操作

在2-3树删除最小/大值过程中，我们能够发现若最左边或最右边的结点是一个3-结点，那么我们以普通二叉搜索树的删除方式直接删除这个结点就行了，此时3-结点变成了2-结点，但丝毫不影响我们红黑树的完美平衡。但是当最左边或者最右边的结点为2-结点的时候就不一样了，此时若直接删除这个结点就会影响到红黑树的完美平衡性。因此删除最小/大值操作的关键在于：**沿着左链接或者右链接向下，保证不能直接删除一个2-结点，要确保当前结点总不是2-结点**（对于向左删除一定是向左偏的非2-结点，对于向右删除的一定向右偏的非2-结点，其中临时产生的4-结点一定是既向右又向左）。

1. **删除最小值**

因此在沿着左链接向下的过程中，当前结点有如下的3种情况：

- 若当前结点的左子结点是3-结点

则此时我们并不需要特别的处理，因为它本身就一定是一个向左偏的3-结点

- 若当前节点的左子结点是2-结点，但右子结点不是2-结点

  则此时左子结点需要到右子结点中“借”一个键移动到左子结点。因此在递归之前需要做出如下操作：①先进行颜色翻转处理（联想到插入时分解一个4-结点的时候也有一个颜色翻转的操作，这个和其下面的颜色翻转可以是其逆操作，不止一次是因为插入时本身也存在中间结点上提而多次调用的过程）；②然后对当前结点的右子结点进行右旋操作；③接着对当前结点做左旋操作，使得右子结点成为新的根结点（替代当前结点）；④最后再对根结点进行颜色翻转操作。

  <img src="image/RBDelete.jpg" alt="RBDelete" style="zoom: 50%;" />

- 若当前节点的左子结点和其右子结点都是2-结点

  则此时需要将左子结点、右子结点和父结点中的最小键（其实这是从2-3树角度考虑的，在二叉搜索树实现的红黑树中不需要这个考虑，直接称当前结点即可）合并成一个4-结点（这里也不用像书上那样过多的考虑2-3-4树那样）。因此在递归向下前需要做出如下的操作：直接进行颜色翻转使得当前结点变成4-结点。

  <img src="image/sing.jpg" alt="sing" style="zoom:50%;" />

当完成上述的递归左链接向下的过程后，`deleteMin()`就可以被递归调用以对真正的欲删除的结点进行删除操作。需要注意的是：当完成删除操作之后，需要在递归返回的路径中依次对每一个结点执行再平衡操作，以保持我们对红黑树的预先规定。（当然其中很多细节需要不断查看源码进行体悟）

```java
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

    public void deleteMin() {
        if (!isRed(root.left) && !isRed(root.right))
            root.color = RED;
        root = deleteMin(root);
        if (isEmpty()) root.color = BLACK;
    }
```



2. **删除最大值**

   其操作类似于删除最小值，但可能有一些细节上的不同。

```java
    //翻转当前结点和左右孩子结点的颜色
    private void flipColors(Node h) {
        h.color = !h.color;
        h.left.color = !h.left.color;
        h.right.color = !h.right.color;
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

    public void deleteMax() {
        if (!isRed(root.left) && !isRed(root.right))
            root.color = RED;
        root = deleteMax(root);
        if (isEmpty()) root.color = BLACK;
    }
```



##### 3.3.2.3  删除操作

红黑树的任意删除操作其实本质上就是删除最小值操作和删除最大值操作的的扩展版，它结合向了左删除或者向右删除的特征。**若我们想要删除的结点在当前结点的左子树上，则要确保当前结点一定是一个向左偏的非2-结点；若我们想要删除的结点在当前结点的右子树上（或欲删除结点在就是当前结点），则要确保当前结点一定是向右偏的非2-结点**。我们会惊奇地发现：删除当前结点和删除右子树上的结点都被归为了一类处理。

**即使在删除的过程中红黑树也仍然保持着完美平衡**（因为我们删除前的操作都是通过局部微调的方式维持着平衡的状态，顶多就是出现某一个非2-结点的红链接方向向右而已，这都是为了在要在3-结点身上删除一个键值对使其变成2-结点做准备）。所以我们有理由相信当即将删除那个指定结点的时候，它一定是一个向左偏的3-结点（向左删除）或者是一个向右偏的3-结点（向右删除）或者是一个临时4-结点或者本来就单单一个结点。

当我们需要向右删除或者删除当前结点时仍然是基本上如同处理一个删除最小值的情况：①当前结点的右子结点本身就是3-结点；②当前结点的右子结点为2-结点，但是左子结点为3-结点；③当前结点、左右子结点都是2-结点。所以处理它们的方法基本上相同，就是让当前结点变成向右偏的非2-结点。

<img src="image/rdelete.jpg" alt="rdelete" style="zoom: 50%;" />

还是通过代码进行理解更好：

```java
    private Node delete(Node h, Key key) {
        //欲删除结点在左子树中
        if (key.compareTo(h.key) < 0) {
            if (!isRed(h.left) && !isRed(h.left.left))
                h = moveRedLeft(h);
            h.left = delete(h.left, key);
        }
        //欲删除结点在右子树或者当前结点就是
        else {
            if (isRed(h.left))
                h = rotateRight(h);
            /* 若当前结点确实是欲删除结点，若右边没有子结点，则由于红黑树在删除
            	的过程中仍然是平衡的，所以当前结点左边是绝对没有子结点，即使有
                也被上一步的右旋操作处理掉了。所以这里直接删除返回null本质上与
                上面的deleteMax()我个人觉得区别不大。*/
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

    public void delete(Key key) {
        if (!isRed(root.left) && !isRed(root.right))
            root.color = RED;
        root = delete(root, key);
        if (!isEmpty()) root.color = BLACK;
    }
```





### 3.4  散列表

#### 3.4.1  散列函数



#### 3.4.2  基于拉链法的散列表

基于拉链法的散列表使用一个大小为M（素数）、每一个元素指向一条链表的数组，将多个散列值相同的键-值对存放在同一个元素指向链表之中，从而避免碰撞冲突。

<img src="image/2020-11-14 115346.png" alt="2020-11-14 115346" style="zoom:67%;" />

插入时间复杂度：$N/M$(在散列值均匀的前提下)~$logN$

查找时间复杂度：$N/M$(在散列值均匀的前提下)~$logN$

```java
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
```



#### 3.4.3  基于线性探测法的散列表

实现散列表的另一种方式使用大小为M的数组保存N个键-值对，其中M>N。这种方法依靠数组中的空位解决碰撞冲突。基于这种策略的所有方法统称为开放地址散列表。而开放地址散列表种最简单的一种方法就是线性探测法：*当碰撞（指定索引上已经被别的键-值对占据），此时我们直接检测下一个位置（通过索引+1），若没有使用就存放在这个位置（可以重复）*。

插入操作时间复杂度：常数阶~$logN$

查找操作时间复杂度：常数阶~$logN$

```java
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
}
```

