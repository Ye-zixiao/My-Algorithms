## 5.字符串

### 5.1 字符串排序

#### 5.1.1  键索引计数排序

键索引计数法实质上是一种排序方法，适用于小整数键的简单排序。执行4个步骤如下：

1. 使用一个int数组count[]计算出每一个键出现的频率；
2. 使用count[]来计算每一个键在排序结果中的起始索引位置；
3. 将原来数组中的元素移动到一个辅助数组aux[]之中进行排序，且每一个元素在aux[]中的位置是由它的键对应的count[]（此时count[i]表示该键当前在辅助数组中的起始下标位置）值决定；
4. 将在aux[]数组中排序好的数据回写到原来的数组之中。

代码如下所示：

```java
	int N = a.length;
    
    String[] aux = new String[N];
    int[] count = new int[R + 1];
    
	//计算键出现的频率
    for (int i = 0; i < N; i++)
        count[a[i].key() + 1]++;
    //将频率转换为索引
    for (int r = 0; r < R; r++)
        count[r + 1] += count[r];
    //将元素分类
    for (int i = 0; i < N; i++)
        aux[count[a[i].key()]++] = a[i];
    //回写
    for (int i = 0; i < N; i++)
        a[i] = aux[i];
```

下图演示了一组名字字符串按照组号（键）进行从小到大排序的过程：

<img src="image/2020-11-29 110840.png" alt="2020-11-29 110840" style="zoom:65%;" />

<img src="image/2020-11-29 110930.png" alt="2020-11-29 110930" style="zoom:65%;" />

而下面的过程演示了从原数组按照count[]移动到辅助数组的过程：

<img src="image/2020-11-29 111018.png" alt="2020-11-29 111018" style="zoom:67%;" />



#### 5.1.2  低位优先的字符串排序

低位优先的字符串排序实际上就是针对字符串数组**从它们的低位开始到高位进行字符串长度次的键索引计数排序**。

```java
import edu.princeton.cs.algs4.StdOut;

public class LSD {
    public static void sort(String[] a, int W) {
        int N = a.length;
        int R = 256;
        String[] aux = new String[N];

        for (int d = W - 1; d >= 0; d--) {
            int[] count = new int[R + 1];
            for (int i = 0; i < N; i++)
                count[a[i].charAt(d) + 1]++;
            //count[a[i][d]+1]++;
            //count[i+1]=n表示字符码为i的字符出现了n次

            for (int r = 0; r < R; r++)
                count[r + 1] += count[r];
            //count[r+1]+=count[r];
            //此时count[i]表示字符码为i的字符要移动到辅助数组中的下标位置

            for (int i = 0; i < N; i++)
                aux[count[a[i].charAt(d)]++] = a[i];
            //aux[count[a[i][d]]++]=a[i]

            for (int i = 0; i < N; i++)
                a[i] = aux[i];
        }
    }

    public static void main(String[] args) {
        String[] a = new String[]{
                "4PGC938", "2IYE230",
                "3CIO720", "1ICK750",
                "1OHV845", "4JZY524"
        };

        for (String str : a)
            StdOut.println(str);
    }
}

```

C++实现：

```c++
#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const vector<string> &
strsort(vector<string> &strvec, int w) {
	size_t N = strvec.size(), R = 256;
	vector<string> aux(N);
	int *count = new int[R + 1];

	for (int d = w - 1; d >= 0; --d) {
		memset(count, 0, sizeof(int) * (R + 1));
		for (int i = 0; i < N; ++i)
			count[strvec[i][d] + 1]++;
		for (int r = 0; r < R; ++r)
			count[r + 1] += count[r];
		for (int i = 0; i < N; ++i)
			aux[count[strvec[i][d]]++] = strvec[i];
		copy(aux.begin(), aux.end(), strvec.begin());
	}
	delete[] count;
	return strvec;
}

int main() {
	vector<string> strvec{
	    "4PGC938", "2IYE230",
	    "3CIO720", "1ICK750",
	    "1OHV845", "4JZY524"};
	for (const string &str : strsort(strvec, strvec[0].size()))
		cout << str << endl;
	return 0;
}
```

图示：

<img src="image/2020-11-29 113941.png" alt="2020-11-29 113941" style="zoom:65%;" />



#### 5.1.3  高位优先的字符串排序

高位优先的字符串排序的基本思想很简单：首先用键索引计数法将所有字符串按照首字母排序，然后（递归地）再将每个首字母所对应的子数组排序（忽略首字母，因为每一类中的所有字符串的首字母都是相同的）。

高位优先排序的难点在于处理不同长度的字符串。在这里我们使用的处理方法就是：不断地递归调用sort，而sort每一次都只根据子字符串中第一个字符对字符串数组进行排序，完成之后对首字符相同的字符串数组部分根据它们的首字符递归调用sort进行排序，直到遇到这个起始字符后面的子字符串数组为空。

如果字符串之间长度不同，那么随着递归的推进，最终总会有些字符串在sort函数中呈现出的子字符串为空（实际中，我们用字符下标>=字符串长度时，表示检测到子字符串为空），那么显然这些字符串应该自动地放到源字符串数组的前面位置。接着再对剩下的子字符串进行递归比较。如图所示：

<img src="image/MSD.jpg" alt="MSD" style="zoom: 50%;" />

```java
import edu.princeton.cs.algs4.Alphabet;
import edu.princeton.cs.algs4.StdOut;

public class MSD {
    private static int R = Alphabet.EXTENDED_ASCII.R();//256
    private static final int M = 10;
    private static String[] aux;

    private static void swap(String[] a, int i, int j) {
        String temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    /* 若下标d已经超过了str的最大下标，则返回-1，这样count[1]这个位置
        就可以记录在本轮不再比较的字符串数量。它是String charAt方法的改造
        而原来的方法在越界之后会直接抛出一个异常 */
    private static int charAt(String str, int d) {
        if (d < str.length()) return str.charAt(d);
        return -1;
    }

    private static boolean less(String v, String w, int d) {
        return v.substring(d).compareTo(w.substring(d)) < 0;
    }

    /* 要知道插入排序是可以一次就将字符串数组进行排序，不需要像最高位优先
        字符串排序那样对每一位字符都进行一次键索引计数排序 */
    public static void insertion_sort(String[] a, int low, int high, int d) {
        for (int i = low, j; i <= high; ++i) {
            String temp = a[i];
            for (j = i; j > low && less(temp, a[j - 1], d); --j)
                a[j] = a[j - 1];
            a[j] = temp;
        }
    }

    public static void msd_sort(String[] a, int low, int high, int d) {
        if (high - low <= M) {
            insertion_sort(a, low, high, d);
            return;
        }

        int[] count = new int[R + 2];
        for (int i = low; i <= high; ++i)
            count[charAt(a[i], d) + 2]++;
        for (int r = 0; r < R; ++r)
            count[r + 1] += count[r];
        for (int i = low; i <= high; ++i)
            aux[count[a[i].charAt(d) + 1]++] = a[i];
        for (int i = low; i <= high; ++i)
            a[i] = aux[i - low];

        //递归根据下一个字符位置进行比较
        for (int r = 0; r < R; ++r)
            msd_sort(a, low + count[r], low + count[r + 1] - 1, d + 1);
    }

    public static void msd_sort(String[] a) {
        int N = a.length;
        aux = new String[N];
        msd_sort(a, 0, N - 1, 0);
    }

    public static void main(String[] args) {
        String[] strarr = new String[]{
                "she", "shells", "seashells",
                "by", "what", "how", "code", "look",
                "the", "the", "are", "surely", "talk",
                "cheap", "joker", "bubble", "fuck"
        };
        msd_sort(strarr);
        for (String str : strarr)
            StdOut.println(str);
    }
}
```

这个算法妙就妙在count[]数组的设计上！count[]在不同阶段下其元素表示的意义如下图所示：

<img src="image/2020-11-30 143905.png" alt="2020-11-30 143905" style="zoom: 80%;" />

下图演示了一次键索引计数排序前后发生的过程：

<img src="image/2020-11-30 143826.png" alt="2020-11-30 143826" style="zoom: 80%;" />



#### 5.1.4  三向字符串快速排序

三向字符串快速排序的思想和普通的三切分快速排序没什么太大的不同，仍然是将字符串数组切分成3个部分，第一部分放置当前字符小于中枢字符的字符串；第二部分放置当前字符串等于中枢字符的字符串；第三部分放置当前字符大于中枢字符的字符串。我将快速排序中使用过的一张图放置在这里会很好的加深理解：

<img src="image/2020-12-01 110112.png" alt="2020-12-01 110112" style="zoom:80%;" />

Java实现：

```java
import edu.princeton.cs.algs4.StdOut;

public class Quick3String {
    private static int charAt(String s, int d) {
        if (d < s.length()) return s.charAt(d);
        return -1;
    }

    private static void swap(String[] a, int i, int j) {
        String temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    private static void sort(String[] a, int low, int high, int d) {
        if (high <= low) return;

        int lt = low, gt = high, i = low + 1;
        int v = charAt(a[low], d);//中枢字符

        /**  i的起始位置
         *    |
         *    v     gt
         * [v,......]
         *
         * */
        while (i <= gt) {
            int t = charAt(a[i], d);
            if (t < v) swap(a, lt++, i++);
            else if (t > v) swap(a, i, gt--);
            else i++;
        }

        sort(a, low, lt - 1, d);
        if (v >= 0) sort(a, lt, gt, d + 1);
        sort(a, gt + 1, high, d);
    }

    public static void sort(String[] a) {
        sort(a, 0, a.length - 1, 0);
    }

    public static void main(String[] args) {
        String[] strarr = new String[]{
                "she", "shells", "seashells",
                "by", "what", "how", "code", "look",
                "the", "the", "are", "surely", "talk",
                "cheap", "joker", "bubble", "fuck"
        };
        sort(strarr);
        for (String str : strarr)
            StdOut.println(str);
    }
}
```

C++实现：（其实我更喜欢用C写😂）

```cpp
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Quick3String {
public:
	static const vector<string> &
	sort(vector<string> &strvec) {
		return (sort(strvec, 0, strvec.size() - 1, 0), strvec);
	}

private:
	static void sort(vector<string> &strvec, int low, int high, int d) {
		if (low >= high)
			return;

		int lt = low, gt = high, i = low + 1;
		int key = (d < strvec[low].size()) ? strvec[low][d] : -1;//中枢字符

		while (gt >= i) {
			if (strvec[i][d] < key)
				swap(strvec, lt++, i++);
			else if (strvec[i][d] > key)
				swap(strvec, i, gt--);
			else
				i++;
		}

		sort(strvec, low, lt - 1, d);
		if (key >= 0)
			sort(strvec, lt, gt, d + 1);
		sort(strvec, gt + 1, high, d);
	}

	static void swap(vector<string> &strvec, int i, int j) {
		::swap(strvec[i], strvec[j]);
	}
};

int main() {
	vector<string> strvec{
	    "she", "shells", "seashells",
	    "by", "what", "how", "code", "look",
	    "the", "the", "are", "surely", "talk",
	    "cheap", "joker", "bubble", "fuck"};
	for (const string &str : Quick3String::sort(strvec))
		cout << str << endl;
	return (0);
}
```

如下是三向字符串快速排序一次完整的过程图演示：

<img src="image/2020-12-01 110444.png" alt="2020-12-01 110444" style="zoom:80%;" />



总结：各种字符串排序算法的性能特点

|         算法         | 是否稳定 | 是否原地排序 | 时间复杂度  | 空间复杂度 |                    适用领域                    |
| :------------------: | :------: | :----------: | :---------: | :--------: | :--------------------------------------------: |
|       插入排序       |    ✔     |      ✔       |  $N$~$N^2$  |    $1$     |            小数组或者已经有序的数组            |
|       归并排序       |    ✔     |      ❌       |  $Nlog^2N$  |   $logN$   |               稳定的通用排序算法               |
|       快速排序       |    ❌     |      ✔       |  $Nlog^2N$  |    $N$     |      通用排序算法，特别适合空间不足的情况      |
|     三向快速排序     |    ❌     |      ✔       | $N$~$NlogN$ |   $logN$   |                   大量重复键                   |
|  低位优先字符串排序  |    ✔     |      ❌       |    $NW$     |    $N$     |                较短的定长字符串                |
|  高位优先字符串排序  |    ✔     |      ❌       |  $N$~$Nw$   |   $N+WR$   |                   随机字符串                   |
| 三向字符串字符串排序 |    ❌     |      ✔       |  $N$~$Nw$   |  $W+logN$  | 通用排序算法，特别适合含有较长公共前缀的字符串 |



### 5.2 单词查找树

#### 5.2.1 单词查找树

以字符串为键的符号表API：`public class StringST<Value>`

- `StringST()`
- `void put(String key,Value val)`
- `Value get(String key)`
- `void delete(String key)`
- `boolean contains(String key)`
- `boolean isEmpty()`
- `String longestPrefixOf(String s)`
- `Iterable<String> keysWithPrefix(String s)`
- `Iterable<String> keysThatMatch(String s)`
- `int size()`
- `Iterable<String> keys()`

结构图示：

<img src="image/2020-12-02 141539.png" alt="2020-12-02 141539" style="zoom:80%;" />

```java
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;


public class TrieST<Value> {
    private static int R = 256;
    private Node root;

    private static class Node {
        private Object val;
        private Node[] next = new Node[R];
    }

    private Node put(Node x, String key, Value val, int d) {
        if (x == null) x = new Node();
        if (d == key.length()) {
            x.val = val;
            return x;
        }

        char c = key.charAt(d);
        x.next[c] = put(x.next[c], key, val, d + 1);
        return x;
    }

    private Node delete(Node x, String key, int d) {
        if (x == null) return null;
        if (d == key.length())
            x.val = null;
        else {
            //递归查找并删除
            char c = key.charAt(d);
            x.next[c] = delete(x.next[c], key, d + 1);
        }

        if (x.val != null) return x;
        for (char c = 0; c < R; c++)
            if (x.next[c] != null) return x;
        return null;
    }

    private Node get(Node x, String key, int d) {
        if (x == null) return null;
        if (d == key.length()) return x;

        char c = key.charAt(d);
        return get(x.next[c], key, d + 1);
    }

    private void collect(Node x, String pre, Queue<String> queue) {
        if (x == null) return;
        if (x.val != null) queue.enqueue(pre);
        for (char c = 0; c < R; c++)
            collect(x.next[c], pre + c, queue);
    }

    /* pre表示先前经由单词查找树找到的前缀字符串，只有当这个前缀字符串与
     * 匹配字符串长度相同且结点值不为null时才表示匹配成功，故将其加入到队列中 */
    private void collect(Node x, String pre, String pat, Queue<String> queue) {
        int d = pre.length();
        if (x == null) return;
        if (d == pat.length() && x.val != null)
            queue.enqueue(pre);
        if (d == pat.length()) return;

        char next = pat.charAt(d);
        for (char c = 0; c < R; c++)
            if (next == '.' || next == c)
                collect(x.next[c], pre + c, pat, queue);
    }

    private int search(Node x, String s, int d, int length) {
        if (x == null) return length;
        if (x.val != null) length = d;
        if (d == s.length()) return length;
        char c = s.charAt(d);
        return search(x.next[c], s, d + 1, length);
    }

    private int size(Node x) {
        if (x == null) return 0;

        int cnt = 0;
        if (x.val != null) cnt++;
        for (char c = 0; c < R; c++)
            cnt += size(x.next[c]);
        return cnt;
    }

    public int size() {
        return size(root);
    }

    public boolean isEmpty() {
        return size() == 0;
    }

    public boolean contains(String key) {
        return get(key) != null;
    }

    public void put(String key, Value val) {
        root = put(root, key, val, 0);
    }

    public void delete(String key) {
        root = delete(root, key, 0);
    }

    public Value get(String key) {
        Node x = get(root, key, 0);
        if (x == null) return null;
        return (Value) x.val;
    }

    public Iterable<String> keysWithPrefix(String pre) {
        Queue<String> queue = new Queue<String>();
        collect(get(root, pre, 0), pre, queue);
        return queue;
    }

    public Iterable<String> keys() {
        return keysWithPrefix("");
    }

    public Iterable<String> keysThatMatch(String pat) {
        Queue<String> queue = new Queue<String>();
        collect(root, "", pat, queue);
        return queue;
    }

    public String longestPrefixOf(String s) {
        int length = search(root, s, 0, 0);
        return s.substring(0, length);
    }

    public static void main(String[] args) {
        String[] strarr = new String[]{
                "sea", "what", "fuck", "show",
                "how", "good", "code", "dance"
        };
        TrieST<Integer> trieST = new TrieST<Integer>();

        for (int i = 0; i < strarr.length; ++i)
            trieST.put(strarr[i], i);
        StdOut.println(trieST.size());
        for(String str: trieST.keys())
            StdOut.println(str);
    }
}
```



单词查找树性质：

