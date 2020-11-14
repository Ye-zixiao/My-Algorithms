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



### 2.1.初级排序

#### 冒泡排序

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



#### 选择排序

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



#### 插入排序

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



#### 希尔排序

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

#### 普通快速排序

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

#### 三切分快速排序

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

#### 最大堆

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

#### 索引优先队列



#### 堆排序

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

