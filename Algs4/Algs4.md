# 算法4

## 1.基础

### 1.1栈

下压栈API：

`public class Stack<Item> implements Iterable<Item>`

- `boolean isEmpty();`
- `int size();`

- `void push(Item item);`
- `Item pop();`

##### 使用数组实现的下压栈

```java
import edu.princeton.cs.algs4.StdOut;
import java.util.Iterator;

public class ResizingArrayStack<Item> implements Iterable<Item> {
    private Item[] array = (Item[]) new Object[1];
    private int N = 0;

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public void push(Item item) {
        if (N == array.length) resize(array.length * 2);
        array[N++] = item;
    }

    public Item pop() {
        Item item = array[--N];
        array[N] = null;
        if (N > 0 && N == array.length / 4)
            resize(array.length / 2);
        return item;
    }

    public Iterator<Item> iterator() {
        return new ReverseArrayIterator();
    }

    private void resize(int max) {
        Item[] temp = (Item[]) new Object[max];
        for (int i = 0; i < N; i++)
            temp[i] = array[i];
        array = temp;
    }

    private class ReverseArrayIterator implements Iterator<Item> {
        private int i = N;

        public boolean hasNext() {
            return i > 0;
        }

        public Item next() {
            return array[--i];
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }
    }

    public static void main(String[] args) {
        ResizingArrayStack<Integer> resizingArrayStack = new ResizingArrayStack<Integer>();

        resizingArrayStack.push(20);
        resizingArrayStack.push(32);
        resizingArrayStack.push(321);
        StdOut.println(resizingArrayStack.pop());
        StdOut.println(resizingArrayStack.pop());
        StdOut.println(resizingArrayStack.pop());
    }
}
```



##### 使用链表实现的下压栈

```java
import edu.princeton.cs.algs4.StdOut;
import java.util.Iterator;

public class ListStack<Item> implements Iterable<Item> {
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

    public void push(Item item) {
        Node oldnode = first;
        first = new Node();
        first.item = item;
        first.next = oldnode;
        ++N;
    }

    public Item pop() {
        Item item = first.item;
        first = first.next;
        --N;
        return item;
    }

    public Iterator<Item> iterator() {
        return new ListIterator();
    }

    public static void main(String[] args) {
        ListStack<Integer> listStack = new ListStack<Integer>();

        listStack.push(12);
        listStack.push(2);
        listStack.push(234);
        StdOut.println(listStack.pop());
        StdOut.println(listStack.pop());
        StdOut.println(listStack.pop());
    }
}

```



### 1.2队列

队列API：

`public class Queue<Item> implements Iterable<Item>`

- `int size();`
- `boolean isEmpty();`
- `void enqueue(Item item);`
- `Item dequeue();`

```java
import edu.princeton.cs.algs4.StdOut;

import java.util.Iterator;
import java.util.List;

public class Queue<Item> implements Iterable<Item> {
    private Node first;
    private Node last;
    int N = 0;

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

    public void enqueue(Item item) {
        Node oldlast = last;
        last = new Node();
        last.item = item;
        last.next = null;
        if (isEmpty()) first = last;
        else oldlast.next = last;
        N++;
    }

    public Item dequeue() {
        Item item = first.item;
        first = first.next;
        N--;
        if (isEmpty()) last = null;
        return item;
    }

    public ListIterator iterator() {
        return new ListIterator();
    }

    public static void main(String[] args) {
        Queue<Integer> queue = new Queue<Integer>();

        queue.enqueue(32);
        queue.enqueue(53);
        queue.enqueue(2340);
        for (Integer elem : queue) {
            StdOut.println(elem)
        }
        StdOut.println(queue.dequeue());
        StdOut.println(queue.dequeue());
        StdOut.println(queue.dequeue());
        StdOut.println("final size: " + queue.size());
    }
}
```



### 1.3背包

背包API：

`public class Bag<Item> implements Iterable<Item>`

- `int size();`
- `boolean isEmpty();`
- `void add(Item item);`

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.ST;
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
```



### 1.4链表

使用C实现的单链表：

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Node{
    struct Node*next;
    char value[1];/* 虽然value数组只有一个字节，但可以通过malloc扩展
                    字节大小，而且还能够很好的获取其指针 */
};


struct List{
    struct Node*first;
    struct Node*last;
    int ListSize;
};


/*
 * 链表初始化
 */
void ListInit(struct List*list){
    list->first=NULL;
    list->last=NULL;
    list->ListSize=0;
}


/*
 * 链表销毁 
 */
void ListDestroy(struct List*list){
    struct Node*node,*temp;

    node=list->first;
    while(node!=NULL){
        temp=node;
        node=node->next;
        free(temp);
    }
    list->first=NULL;
    list->last=NULL;
    list->ListSize=0;
}


/* 
 * 返回链表长度
 */
static inline 
int Size(const struct List*list){
    return list->ListSize;
}


/*
 * 链表是否为空
 */
static inline 
int isEmpty(const struct List*list){
    return list->ListSize==0;
}


/*
 * 链表前向插入数据
 */
struct Node* FInsert(struct List*list,void*value,size_t sz){
    struct Node*newNode;

    if((newNode=malloc(sizeof(struct Node)+sz-1))==NULL)
        return NULL;
    memcpy(newNode->value,value,sz);
    newNode->next=list->first;
    if(isEmpty(list)) list->last=newNode;
    list->first=newNode;
    list->ListSize++;
    return newNode;
}


/*
 * 链表后向插入 
 */
struct Node* BInsert(struct List*list,void*value,size_t sz){
    struct Node*newNode;

    if((newNode=malloc(sizeof(struct Node)+sz-1))==NULL)
        return NULL;
    memcpy(newNode->value,value,sz);
    newNode->next=NULL;
    if(isEmpty(list)) list->first=newNode;
    else list->last->next=newNode;
    list->last=newNode;
    list->ListSize++;
    return newNode;
}


/*
 * 链表普通插入，当node==NULL等同于FInsert() 
 */
struct Node* Insert(struct List*list,struct Node*node,void*value,size_t sz){
    struct Node*newNode;

    if(node==NULL)
        return FInsert(list,value,sz);
    else if(list->first==NULL)
        return NULL;
    if((newNode=malloc(sizeof(struct Node)+sz-1))==NULL)
        return NULL;
    memcpy(newNode->value,value,sz);
    newNode->next=node->next;
    node->next=newNode;
    if(list->last==node)
        list->last=newNode;
    list->ListSize++;
    return newNode;
}


/*
 * 链表前向删除元素 
 */
int FRemove(struct List*list,void*retval,size_t sz){
    struct Node*temp;

    if(isEmpty(list))
        return -1;
    if(retval!=NULL)//若retval非空才选择拷贝待删除元素中的数据
        memcpy(retval,list->first->value,sz);
    temp=list->first;
    list->first=list->first->next;
    free(temp);
    if(list->ListSize==1)
        list->last=NULL;
    list->ListSize--;
    return 0;     
}


//不支持bremove()


/*
 * 普通链表元素删除，当node==NULL时等同于FRemove()
 */
int Remove(struct List*list,struct Node*node,void*retval,size_t sz){
    struct Node*temp;

    if(node==NULL)
        return FRemove(list,retval,sz);
    if(node->next==NULL)
        return NULL;
    temp=node->next;
    node->next=temp->next;
    if(list->last==temp)
        list->last=node;
    if(retval!=NULL)
        memcpy(retval,temp->value,sz);
    free(temp);
    list->ListSize--;
    return 0;
}


/*
 * 链表遍历函数，使用用法类似于strtok() 
 */
struct Node* Iterator(struct List*list){
    static struct Node*node=NULL;
    struct Node*ret=NULL;
    
    if(list!=NULL)
        node=list->first;
    if(node!=NULL){
        ret=node;
        node=node->next;
    }
    return ret;
}


/*
 * 返回链表首元素指针
 */
inline static 
struct Node*First(struct List*list){
    return list->first;
}


/*
 * 返回链表尾元素指针 
 */
inline static 
struct Node*Last(struct List*list){
    return list->last;
}


/*
 * 在链表中查找指定元素 
 */
struct Node*Find(const struct List*list,const void*val,size_t sz,
                int(*pf)(const void*,const void*)){
    struct Node*node=list->first;

    while(node!=NULL){
        if(pf(node->value,val))
            return node;
        node=node->next;
    }
    return NULL;
}


int main(void){
    struct List list;
    double darr[10]={
        1.2,1.4,3.12,3.1,8.3,
        2.4,8.3,3.2,6.4,1.6
    };

    ListInit(&list);
    for(int i=0;i<5;i++)
        Insert(&list,NULL,(void*)&darr[i],sizeof(double));
    for(int i=5;i<10;++i)
        Insert(&list,list.last,(void*)&darr[i],sizeof(double));

    for(const struct Node*p=Iterator(&list);
            p!=NULL;p=Iterator(NULL)){
        printf("%.2f\n",*(double*)(p->value));
    }
    printf("current list size: %d\n",Size(&list));
    ListDestroy(&list);
    printf("final list size: %d\n",Size(&list));
    
    return 0;
}
```



### 1.5算法分析

<img src="image/image-20201029142004452.png" alt="image-20201029142004452" style="zoom: 80%;" />



### 1.6union-find算法

union-find的API：`public class UF`

- `UF(int N)`
- `void find(int p)`
- `int find(int pos)`
- `boolean connected(int p,int q)`
- `int count()`

UF1：使用数组遍历式方式进行连通实现

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class UF1 {
    private int[] id;
    private int count;

    public UF1(int N) {
        id = new int[N];
        count = N;
        for (int i = 0; i < N; i++)
            id[i] = i;
    }

    public int count() {
        return count;
    }

    public int find(int pos) {
        return id[pos];
    }

    public boolean connected(int p, int q) {
        return find(p) == find(q);
    }

    public void union(int p, int q) {
        int pID = find(p);
        int qID = find(q);

        if (pID == qID) return;
        for (int i = 0; i < id.length; ++i)
            if (id[i] == pID) id[i] = qID;
        count--;
    }

    public static void main(String[] args) {
        int[] array = In.readInts(args[0]);
        int cnt = 0, N = array[cnt++];
        UF1 uf1 = new UF1(N);

        while (cnt < array.length) {
            int p = array[cnt++];
            int q = array[cnt++];
            if (uf1.connected(p, q)) continue;
            uf1.union(p, q);
            StdOut.println(p + " " + q);
        }
        StdOut.println(uf1.count() + " components");
    }
}
```



UF2：使用节点连接到同一个树根的方式完成连通分量的来链接

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class UF2 {
    private int[] id;
    private int count;

    public UF2(int N) {
        id = new int[N];
        count = N;
        for (int i = 0; i < N; i++)
            id[i] = i;
    }

    public int count() {
        return count;
    }

    public int find(int pos) {
        while (pos != id[pos]) pos = id[pos];
        return pos;
    }

    public boolean connected(int p, int q) {
        return find(p) == find(q);
    }

    public void union(int p, int q) {
        int pID = find(p);
        int qID = find(q);

        if (pID != qID) {
            id[pID] = qID;
            count--;
        }
    }

    public static void main(String[] args) {
        int[] array = In.readInts(args[0]);
        int cnt = 0, N = array[cnt++];
        UF2 uf2 = new UF2(N);

        while (cnt < array.length) {
            int p = array[cnt++];
            int q = array[cnt++];
            if (uf2.connected(p, q)) continue;
            uf2.union(p, q);
            StdOut.println(p + " " + q);
        }
        StdOut.println(uf2.count() + " connected");
    }
}
```

图示链接过程：

<img src="image/2020-10-30 200900.png" alt="2020-10-30 200900" style="zoom:67%;" />





UF3：在UF2的基础上增加一个记录连通分量的节点数的数组，每次进行挂载（链接）的时候根据连通分量树的大小将小树挂在大树的根节点上

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class UF3 {
    private int[] id;
    private int[] sz;
    private int count;

    public UF3(int N) {
        id = new int[N];
        sz = new int[N];
        count = N;
        for (int i = 0; i < N; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }

    public int count() {
        return count;
    }

    public int find(int pos) {
        while (pos != id[pos]) pos = id[pos];
        return pos;
    }

    public boolean connected(int p, int q) {
        return find(p) == find(q);
    }

    public void union(int p, int q) {
        int pID = find(p);
        int qID = find(q);

        if (pID != qID) {
            //将小树挂在大树的根节点上
            if (sz[pID] < sz[qID]) {
                id[pID] = qID;
                sz[qID] += sz[pID];
            } else {
                id[qID] = pID;
                sz[pID] += sz[qID];
            }
            count--;
        }
    }

    public static void main(String[] args) {
        int[] array = In.readInts(args[0]);
        int cnt = 0, N = array[cnt++];
        UF3 uf3 = new UF3(N);

        while (cnt < array.length) {
            int p = array[cnt++];
            int q = array[cnt++];
            if (uf3.connected(p, q)) continue;
            uf3.union(p, q);
            StdOut.println(p + " " + q);
        }
        StdOut.println(uf3.count() + " connected");
    }
}
```

链接图示：

<img src="image/2020-10-30 211440.png" alt="屏幕截图 2020-10-30 211440" style="zoom: 80%;" />



## 2.排序

公共类API：`public class Sort`

- `private  static boolean less(Comparable lhs, Comparable rhs)`
- `private static void swap(Comparable[] a, int i,int j)`
- `private static void show(Comparable[] a)`
- `public static  boolean isSorted(Comparable[] a)`
- `public static void sort(Comparable[] a)`

封装sort静态方法的类展示如下，后面只展示sort()方法

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import jdk.nashorn.internal.ir.LiteralNode;

public class Sort {
    private static boolean less(Comparable lhs, Comparable rhs) {
        return lhs.compareTo(rhs) < 0;
    }

    private static void swap(Comparable[] a, int i, int j) {
        Comparable temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    private static void show(Comparable[] a) {
        for (int i = 0; i < a.length; ++i)
            StdOut.println(a[i]);
    }

    public static boolean isSorted(Comparable[] a) {
        for (int i = 1; i < a.length; i++)
            if (less(a[i], a[i - 1]))
                return false;
        return true;
    }

    public static void sort(Comparable[] a) {
		//见下
    }

    public static void main(String[] args) {
        Integer[] array = new Integer[100];
        for (int i = 0; i < array.length; ++i)
            array[i] = (Integer) StdRandom.uniform(0, 100);

        sort(array);
        show(array);
    }
}

```



### 2.1初级排序

##### 冒泡排序

慢慢的将当前剩余最大的值交换到相对最后位置，如同气泡向水面上冒一样。时间复杂度$N^2$

```java
    public static void sort(Comparable[] a) {
        for (int i = a.length; i > 0; i--) {
            for (int j = 1; j < i; ++j)
                if (less(a[j], a[j - 1]))
                    swap(a, j, j - 1);
        }
    }
```



##### 选择排序

核心思想就是将依次最小的元素放在数组最前面。时间复杂度$N^2$

```java
    public static void sort(Comparable[] a) {
        for (int i = 0; i < a.length; ++i) {
            int min = i;
            for (int j = i + 1; j < a.length; ++j) {//选取出最小下标
                if (less(a[j], a[min]))
                    min = j;
            }
            swap(a, i, min);
        }
    }
```



##### 插入排序

核心思想就是将第j个元素插入到数组前j-1个元素的某个恰当位置中。时间复杂度$N^2$

解法1：

```java
    public static void sort(Comparable[] a) {
        for (int i = 1; i < a.length; ++i) {
            for (int j = i; j > 0 && less(a[j], a[j - 1]); --j)
                swap(a, j, j - 1);
        }
    }
```

解法2：采用移动而不是交换，节省交换成本

```java
    public static void sort(Comparable[] a) {
        for (int i = 1, j; i < a.length; ++i) {
            Comparable temp = a[i];
            for (j = i; j > 0 && less(temp, a[j - 1]); j--)
                a[j] = a[j - 1];
            a[j] = temp;
        }
    }
```

图示：

<img src="image/insertion.jpg" alt="insertion" style="zoom:50%;" />



##### 希尔排序

希尔排序的核心思想就是：先对相隔一段间距的元素进行插入排序使得数组部分有序，然后减少间隔量最终变成完全的插入排序，此时达到最终的有序。时间复杂度小于$N^2$，递增序列$1/2(3^k-1)$可以做到$N^{3/2}$

解法1：

```java
    public static void sort(Comparable[] a) {
        for (int h = a.length / 3; h >= 1; h /= 3) {
            for (int i = h; i < a.length; i++)
                for (int j = i; j >= h && less(a[j], a[j - h]); j -= h)
                    swap(a, j, j - h);
        }
    }
```

解法2：

```java
    public static void sort(Comparable[] a) {
        for (int h = a.length / 3; h >= 1; h /= 3) {
            for (int i = h, j; i < a.length; ++i) {
                Comparable temp = a[i];
                for (j = i; j >= h && less(temp, a[j - h]); j -= h)
                    a[j] = a[j - h];
                a[j] = temp;
            }
        }
    }
```



### 2.2归并排序

自顶向下的归并排序，即使用了分而治之的方法将大数组分解成小数组然后进行归并

```java
    private static Comparable[] aux;

	//归并操作
    public static void merge(Comparable[] a, int low, int mid, int high) {
        int i = low, j = mid + 1;
        for (int k = low; k <= high; ++k)
            aux[k] = a[k];

        for (int k = low; k <= high; ++k) {
            if (i > mid)
                a[k] = aux[j++];
            else if (j > high)
                a[k] = aux[i++];
            else if (less(aux[i], aux[j]))
                a[k] = aux[i++];
            else
                a[k] = aux[j++];
        }
    }

	//递归式归并排序操作
    private static void msort(Comparable[] a, int low, int high) {
        if (high - low <= 0) return;
//        else if(high-low<15)
//            InsertSort(a,low,high);

        int mid = low + (high - low) / 2;
        msort(a, low, mid);
        msort(a, mid + 1, high);
        merge(a, low, mid, high);
    }

	//封装了msort的归并排序操作
    public static void sort(Comparable[] a) {
        aux = new Comparable[a.length];
        msort(a, 0, a.length - 1);
    }
```

改进版归并排序：当分割后的数组规模小于15时采用插入排序进行解决，而不再继续使用分割（因为插入排序对于小数组而言可能比归并排序更快）

```java
    private static Comparable[] aux;

    //归并操作
    public static void merge(Comparable[] a, int low, int mid, int high) {
        int i = low, j = mid + 1;
        for (int k = low; k <= high; ++k)
            aux[k] = a[k];

        for (int k = low; k <= high; ++k) {
            if (i > mid)
                a[k] = aux[j++];
            else if (j > high)
                a[k] = aux[i++];
            else if (less(aux[i], aux[j]))
                a[k] = aux[i++];
            else
                a[k] = aux[j++];
        }
    }

    //插入排序
    public static void InsertSort(Comparable[] a, int low, int high) {
        for (int i = low, j; i <= high; ++i) {
            Comparable temp = a[i];
            for (j = i; j > low && less(temp, a[j - 1]); --j)
                a[j] = a[j - 1];
            a[j] = temp;
        }
    }

    //递归式的归并排序
    private static void msort(Comparable[] a, int low, int high) {
        if (high - low <= 0) return;
        else if (high - low < 15)
            InsertSort(a, low, high);
        else {
            StdOut.println("get here?");
            int mid = low + (high - low) / 2;
            msort(a, low, mid);
            msort(a, mid + 1, high);
            if (less(a[mid + 1], a[mid]))//若该局部数组已经有序，则不需要再进入merge之中
                merge(a, low, mid, high);
        }
    }

    //封装递归之后的归并排序
    public static void sort(Comparable[] a) {
        aux = new Comparable[a.length];
        msort(a, 0, a.length - 1);
    }
```

自顶向下的归并排序，其运行方向与上面相反，从低端从顶端运行，先两两归并，然后44归并，。。最后整体归并

```java
    private static Comparable[] aux;

	//归并操作
    public static void merge(Comparable[] a, int low, int mid, int high) {
        int i = low, j = mid + 1;
        for (int k = low; k <= high; ++k)
            aux[k] = a[k];

        for (int k = low; k <= high; ++k) {
            if (i > mid)
                a[k] = aux[j++];
            else if (j > high)
                a[k] = aux[i++];
            else if (less(aux[i], aux[j]))
                a[k] = aux[i++];
            else
                a[k] = aux[j++];
        }
    }

    //封装递归之后的归并排序
    public static void sort(Comparable[] a) {
        int N = a.length;
        aux = new Comparable[N];
        for (int sz = 1; sz < N; sz *= 2) {
            for (int lo = 0; lo < N - sz; lo += sz * 2)
                merge(a, lo, lo + sz - 1, Math.min(N - 1, lo + sz * 2 - 1));
        }
    }
```



### 2.3快速排序

##### 普通快速排序

```java
    private static int partition(Comparable[] a, int low, int high) {
        int i = low, j = high + 1;
        Comparable key = a[low];

        while (true) {
            while (less(a[++i], key))
                if (i == high) break;
            while (less(key, a[--j]))
                if (j == low) break;
            if (i >= j) break;
            swap(a, i, j);
        }
        swap(a, low, j);
        return j;
    }

    public static void qsort(Comparable[] a, int low, int high) {
        if (low >= high) return;

        int pos = partition(a, low, high);
        qsort(a, low, pos - 1);
        qsort(a, pos + 1, high);
    }

    public static void sort(Comparable[] a) {
        qsort(a, 0, a.length - 1);
    }
```

快速排序的改进版1：面对小数组使用插入排序进行代替

```java
    public static void InsertionSort(Comparable[] a, int low, int high) {
        for (int i = low, j; i < high; i++) {
            Comparable temp = a[low];
            for (j = i; j > 0 && less(a[j], a[j - 1]); --j)
                a[j] = a[j - 1];
            a[j] = temp;
        }
    }

    public static void qsort(Comparable[] a, int low, int high) {
        if (high - low <= 0) return;
        else if (high - low < 10) {
            InsertionSort(a, low, high);
            return;
        }

        int pos = partition(a, low, high);
        qsort(a, low, pos - 1);
        qsort(a, pos + 1, high);
    }

    public static void sort(Comparable[] a) {
        qsort(a, 0, a.length - 1);
    }
```

快速排序改进版2：使用三取样+小数组转而用插入排序完成的方式来加速数组排序

```java
    //三取样确定切分元素位置，保证key值不大不小
	private static int ThreeMid(Comparable[] a, int low, int high) {
        Integer[] temp = {low, low + (high - low) / 2, high};
        for (int i = 1, j; i < temp.length; ++i) {
            Integer t = temp[i];
            for (j = i; j > 0 && less(a[j], a[j - 1]); --j)
                temp[j] = temp[j - 1];
            temp[j] = t;
        }
        return temp[1];
    }

    public static int partition(Comparable[] a, int low, int high) {
        int i = low, j = high + 1;
        swap(a, ThreeMid(a, low, high), low);
        Comparable key = a[low];

        while (true) {
            while (less(a[++i], key))
                if (i == high) break;
            while (less(key, a[--j]))
                if (j == low) break;
            if (i >= j) break;
            swap(a, i, j);
        }
        swap(a, low, j);
        return j;
    }

    public static void InsertionSort(Comparable[] a, int low, int high) {
        for (int i = low, j; i <= high; ++i) {
            Comparable t = a[i];
            for (j = i; j > low && less(a[j], a[j - 1]); --j)
                a[j] = a[j - 1];
            a[j] = t;
        }
    }

    public static void qsort(Comparable[] a, int low, int high) {
        if (high - low <= 0) return;
        else if (high - low < 10) {
            InsertionSort(a, low, high);
            return;
        }

        int mid = partition(a, low, high);
        qsort(a, low, mid - 1);
        qsort(a, mid + 1, high);
    }

    public static void sort(Comparable[] a) {
        qsort(a, 0, a.length - 1);
    }
```

##### 三切分快速排序

```java
	//3取样    
	private static int ThreeMid(Comparable[] a, int low, int high) {
        Integer[] temp = {low, low + (high - low) / 2, high};
        for (int i = 1, j; i < temp.length; ++i) {
            Integer t = temp[i];
            for (j = i; j > 0 && less(a[j], a[j - 1]); --j)
                temp[j] = temp[j - 1];
            temp[j] = t;
        }
        return temp[1];
    }

    public static void qsort(Comparable[] a, int low, int high) {
        if (high - low <= 0) return;

        swap(a, low, ThreeMid(a, low, high));//用到了3取样方法
        int lt = low, i = low + 1, gt = high;
        Comparable v = a[low];
        
        while (i <= gt) {
            int cmp = a[i].compareTo(v);
            if (cmp < 0)
                swap(a, lt++, i++);
            else if (cmp > 0)
                swap(a, gt--, i);
            else
                i++;
        }
        qsort(a, low, lt - 1);
        qsort(a, gt + 1, high);
    }

    public static void sort(Comparable[] a) {
        qsort(a, 0, a.length - 1);
    }
```

图示：

<img src="image/2020-11-02 211617.png" alt="2020-11-02 211617" style="zoom: 80%;" />

### 2.4优先队列

优先队列API：

`public class MaxPQ<Key extends Comparable<Key>>`

- `MaxPQ()`
- `MaxPQ(int max)`
- `MaxPQ(Key[] a)`
- `void insert(Key v)`
- `Key max()`
- `Key delMax()`
- `boolean isEmpty()`
- `int size()`

##### 最大堆

一个允许动态调整的最大二叉堆：

```java
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

    //插入操作
    public void insert(Key v) {
        if (isFull())
            resize(capacity * 2);
        pq[++N] = v;
        swim(N);
    }

    //删除最大堆中最大值元素，并返回
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

    /* 工具方法： */
    
    private boolean less(int i, int j) {
        return pq[i].compareTo(pq[j]) < 0;
    }

    private void swap(int i, int j) {
        Key temp = pq[i];
        pq[i] = pq[j];
        pq[j] = temp;
    }

    //使指定位置元素上浮，直到合理位置为止
    private void swim(int k) {
        while (k > 1 && less(k / 2, k)) {
            swap(k, k / 2);
            k /= 2;
        }
    }

    //使指定位置元素下沉，直到合理位置为止
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

        for (int i = 0; i < 200; i++)
            maxPQ.insert(i);
        while (!maxPQ.isEmpty())
            StdOut.println(maxPQ.delMax());
    }
}

```

##### 索引优先队列



##### 堆排序

核心思想：先将需要排序的数组构建成为最大堆，然后与最后一个元素进行交换、递减堆大小并重新对根节点做下层操作，重复上述操作直到堆大小变成为0

```java
import edu.princeton.cs.algs4.StdOut;

public class Sort {
    private static void swap(Comparable[] a, int i, int j) {
        Comparable temp = a[j];
        a[j] = a[i];
        a[i] = temp;
    }

    private static boolean less(Comparable lhs, Comparable rhs) {
        return lhs.compareTo(rhs) < 0;
    }

    //元素下沉函数
    private static void sink(Comparable[] a, int k, int N) {
        while (2 * k + 1 < N) {
            int j = 2 * k + 1;
            if (j < N - 1 && less(a[j], a[j + 1])) j++;
            if (!less(a[k], a[j])) break;
            swap(a, k, j);
            k = j;
        }
    }

    //堆排序
    public static void sort(Comparable[] a) {
        int N = a.length;
        /* 从底向上使用sink()函数构建最大堆（注意是从那个最后一个
        	右子节点的节点开始sink()最大堆有序化） */
        for (int k = N / 2 - 1; k >= 0; --k)
            sink(a, k, N);
        while (N > 0) {
            swap(a, 0, --N);
            sink(a, 0, N);
        }
    }

    public static void show(Comparable[] a) {
        for (Comparable item : a)
            StdOut.println(item);
    }

    public static void main(String[] args) {
        Integer[] array = new Integer[100];
        for (int i = 0; i < array.length; ++i)
            array[i] = array.length - i;
        sort(array);
        show(array);
    }
}
```

图示：

<img src="image/2020-11-03 105203.png" alt="2020-11-03 105203" style="zoom:80%;" />

C语言实现：

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAYLENGTH 100

static void swap(int array[],int i,int j){
    int temp=array[i];
    array[i]=array[j];
    array[j]=temp;
}


/* 最大堆元素下沉操作 */
static void sink(int array[],int k,int N){
    int lchild,rchild,maxchild;

    while(2*k+1<N){
        lchild=2*k+1;
        rchild=2*k+2;
        maxchild=lchild;
        //想要实现逆序排序只要改变1、2两点的比较运算符即可
        if(rchild<N&&array[lchild]<array[rchild])//1
            maxchild=rchild;
        if(array[maxchild]<array[k])//2
            break;
        swap(array,k,maxchild);
        k=maxchild;
    }
}


/* 堆排序 */
void HeapSort(int array[],int N){
    for(int k=N/2-1;k>=0;--k)
        sink(array,k,N);
    while(N>0){
        swap(array,0,--N);
        sink(array,0,N);
    }
}


void show(int array[],int N){
    for(int i=0;i<N;++i)
        printf("%d\n",array[i]);
}


int main(void)
{
    int array[ARRAYLENGTH];
    for(int i=0;i<ARRAYLENGTH;++i)
        array[i]=ARRAYLENGTH-i;
    HeapSort(array,ARRAYLENGTH);
    show(array,ARRAYLENGTH);
}
```



## 3.查找

### 3.1符号表

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

##### 无序链表符号表

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



##### 有序数组符号表

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

使用不同数据结构构造符号表（键-值对关联数组）的优缺点：

|    使用的数据结构    |                   实现                    | 插入时间复杂度 | 查找时间复杂度 |                        优点                        |                             缺点                             |
| :------------------: | :---------------------------------------: | :------------: | :------------: | :------------------------------------------------: | :----------------------------------------------------------: |
|   链表（顺序查找）   |            SequentialSearchST             |      $N$       |      $N$       |                   适用于小型问题                   |                   当问题规模变大时处理很慢                   |
| 有序数组（二分查找） |              BinarySearchST               |      $N$       |     $logN$     | 最优的查找效率和空间需求，能够进行有序性相关的操作 |                         插入操作很慢                         |
|      二叉查找树      |                    BST                    |   $logN$~$N$   |   $logN$~$N$   |         实现简单，能够进行有序性相关的操作         |            没有性能上界的保证，链接需要额外的空间            |
|   平衡二叉树查找树   |                RedBlackBST                |     $logN$     |     $logN$     |   最优的查找和插入效率，能够进行有序性相关的操作   |                      链接需要额外的空间                      |
|        散列表        | SeparateChain HashST LinearProbing HashST |                |                |         能够快速地查找和插入常见类型地数据         | 需要计算每种类型数据地散列，无法进行有序性线管地操作，链接和空节点需要额外的空间 |



### 3.2二叉查找树

