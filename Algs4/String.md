## 5. 字符串

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

这种数据结构的关键原理在于：让每一个单词的字符挂接在基于字符集的R（拓展ASCII为256）叉树上，若树上的某一个字符所对应的值非null，那么表示该字符与之前路径上所有字符组成的字符串存在，且对应值就是这个字符结点所对应的值。

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



##### 5.2.1.1  相关操作分析

###### 5.2.1.1.1  插入操作

为了达到插入的目的，我们必须解决先前路径上的字符结点不存在的问题。若先前路径上的字符结点不存在，虽然我们不会为这样的结点赋值，但是我还是必须要创建这样的结点。再创建之后必须检查字符的长度是否与指定插入键字符串的长度相同，若是则将值赋予；否则递归处理到下一个结点（若先前的结点是新建的，那么下一个结点也必然需要新创建）。

```java
	private Node put(Node x, String key, Value val, int d) {
        if (x == null) x = new Node();//若当前字符结点不存在，则新建
        if (d == key.length()) {	  //若到达了指定的字符结点，则赋值
            x.val = val;
            return x;
        }
									//否则递归处理到下一个结点再处理
        char c = key.charAt(d);
        x.next[c] = put(x.next[c], key, val, d + 1);
        return x;
    }

	public void put(String key, Value val) {
        root = put(root, key, val, 0);
    }
```

下面演示了一个简单单词查找树的构造过程：

<img src="image/2020-12-03 092844.png" alt="2020-12-03 092844" style="zoom:67%;" />



###### 5.2.1.1.2  查找操作

查找操作和插入操作类似，也是使用递归，我们可以用下面一个简单的算法指示完成相应的操作：

```
NodeType get(NodeType x, Key key):
	若当前结点 ==null: 返回null
	
	若当前结点复合要求: 返回当前结点
	否则 get(x.next[c], key)
```

实际真正的代码如下，在这里结点是否符合要求完全依赖的是字符串的长度是否等于先前路径上字符的个数，若相等，我们直接返回这个结点并不管这个结点的值是否为null，是否是null这个工作可以交给下面的封装函数完成。

```java
	private Node get(Node x, String key, int d) {
        if (x == null) return null;
        if (d == key.length()) return x;

        char c = key.charAt(d);
        return get(x.next[c], key, d + 1);
    }

	public Value get(String key) {
        Node x = get(root, key, 0);
        if (x == null) return null;
        return (Value) x.val;
    }
```

下面演示了一些实际的查找过程：

<img src="image/2020-12-03 093943.png" alt="2020-12-03 093943" style="zoom:67%;" />



###### 5.3.1.1.3  删除操作

删除操作实际上很简单，只需要将单词查找树中对应字符串最后一个字符的结点的值设置为null即可，不过若这个结点在删除之前就没有任何子结点，那么就需要对这个结点本身以及其父字符结点+祖先结点中不再有孩子的结点（且自己本身的值为null）沿路径向上一并删除，这里主要由递归的return返回null起作用。（**这里的套路与左倾红黑树中的删除方法相同！**🤓）

```java
    private Node delete(Node x, String key, int d) {
        if (x == null) return null;
        
        //1、若当前结点即是指定结点，则值置为null
        if (d == key.length())
            x.val = null;
        //2、否则，递归查找
        else {
            char c = key.charAt(d);
            x.next[c] = delete(x.next[c], key, d + 1);
        }

        /* 置结点值为null后，在返回的路径上对每一个字符结点
        	进行处理。将没有子结点且自己的值为null的结点删除 */
        if (x.val != null) return x;
        for (char c = 0; c < R; c++)
            if (x.next[c] != null) return x;
        return null;
    }

    public void delete(String key) {
        root = delete(root, key, 0);
    }
```

下图展示了一个指定字符串删除的递归前、低轨到指定字符结点将其值置为null以及递归返回的过程中沿路径向上对结点的尾后处理过程：

<img src="image/2020-12-03 104909.png" alt="2020-12-03 104909" style="zoom:67%;" />



###### 5.2.1.1.3  返回具有指定前缀键

返回具有指定前缀键的作用就是可以将一个单词查找树中存储的具有指定前缀的字符串加入到一个容器之中，然后将这个容器的引用进行返回。在上述类中对应的方法就是`keyWithPrefix()`。

为了完成这一目标我们引入了一个收集函数`collect()`，它是一个类中的私有辅助方法，它可以从指定的字符结点开始将路径上（直到最后的末尾）具有指定前缀的、且存在于单词查找树中的字符串加入到一个容器之中。这里使用的方法仍然是递归！下面的算法指示描述了这个递归方法的范式：

```
NodeType collect(NodeType x, Key key, Queue queue):
	若当前结点 == null: return
	
	若当前结点值非空: 加入这个结点前面路径所有字符组成的字符串到容器之中
	否则 collcet(x.next[c], key, queue)
```

根据上面这个`collect()`辅助方法我们可以轻易的让封装函数将单词查找树的根结点root和前缀字符串、容器传入到这个方法之中，最终通过递归将所有符合的字符串加入到容器之中，从而返回具有指定前缀键的容器引用。

更进一步，若我们向这个函数传入的前缀字符串是一个空字符串""，那么我们就可以让`keyWithPrefix()`方法实际返回单词查找树中的所有字符串键！我们将这个方法命名为`keys()`。

```java
    private void collect(Node x, String pre, Queue<String> queue) {
        if (x == null) return;
        if (x.val != null) queue.enqueue(pre);
        for (char c = 0; c < R; c++)
            collect(x.next[c], pre + c, queue);
    }

	//返回所有单词查找树中存在的具有指定前缀的字符串键
    public Iterable<String> keysWithPrefix(String pre) {
        Queue<String> queue = new Queue<String>();
        collect(get(root, pre, 0), pre, queue);
        return queue;
    }

	//返回所有单词查找树中存在的字符串键
    public Iterable<String> keys() {
        return keysWithPrefix("");
    }
```

下图演示了一次对具有指定前缀“sh”的字符串查找：

<img src="image/2020-12-03 100139.png" alt="2020-12-03 100139" style="zoom:67%;" />



###### 5.2.1.1.4  通配符匹配

通配符匹配的思想其实也很简单，类似于上面的查找过程。例如对于一个单词查找树{"shell","she","what"}，我们试图从中找出符合下面通配符字符串，即pattern，“shel..”，那么我们必然知道指定通配符需要查找的字符串长度必然与统配字符串的长度相同（这里为5）！，显然我们只需要沿着前面“she”字符串前缀找剩下路径中长度为5的字符结点，若这个结点的值非空，那么将其加入到实现安排的容器之中即可，否则不加入。我们可以用如下的伪代码指示这一过程：

```
NodeType collect(NodeType x, String pattern, Queue queue):
	若当前结点为空: return
	
	若当前结点表示字符串长度与通配模式字符串长度相同 && 结点值非空:
		将这个字符串加入到容器之中
	若当前结点表示的字符串长度与通配模式字符串长度相同但结点值为空:
		return
	对当前结点中符合要求下一个字符要求的子结点:
		collect(x.next[c], pattern, queue)
```

具体的代码如下所示：

```java
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

    public Iterable<String> keysThatMatch(String pat) {
        Queue<String> queue = new Queue<String>();
        collect(root, "", pat, queue);
        return queue;
    }
```



######  5.2.1.15  最长前缀

最长前缀问题指的是给定一个字符串从单词查找树中找出最长的前缀，且这个前缀字符串本身也存储于单词查找树中，一种最特别的情况就是给定字符串本身就是最大前缀，那么可以料想这个单词字符串本身也必然是存储于单词查找树中。

解决这个问题的最好方法仍然是递归，不过递归方法的目的是为了找到那个最长前缀字符串的长度，而不是直接获取最长前缀字符串。这个递归式有如下几种情况需要处理：①若当前结点为空，则返回之前保存的最长前缀字符串长度；②若当前结点非空，则将保存的最长前缀字符串长度修改为当前字符串的长度；③若当前结点的长度已经等于指定字符串的长度，则直接返回这个保存的最长前缀字符串长度；④剩下的情况就是递归了。算法流程如下所示：

```
int search(NodeType x, String s, int d, int length):
	若当前结点为空: return length
	
	若当前结点值非空: 修改length长度
	若当前结点表示的字符串长度等于查找字符串的长度: return length 
	return search(x.next[c], s, d, length)
```

```java
    private int search(Node x, String s, int d, int length) {
        if (x == null) return length;
        if (x.val != null) length = d;
        if (d == s.length()) return length;
        char c = s.charAt(d);
        return search(x.next[c], s, d + 1, length);
    }

    public String longestPrefixOf(String s) {
        int length = search(root, s, 0, 0);
        return s.substring(0, length);
    }
```



##### 5.2.1.2 单词查找树性质

- 会命中的查找在单词查找树中所访问的字符结点数最多为键的长度+1，而与单词查找树中键的数量无关；
- 不会命中的查找在单词查找树中的随机模型中需要访问$~log_R{N}$（$N$表示总随机键数，$R$表示所基于的字符数量）个字符节点数，也就是说查找未命中的成本与键的长度无关；
- 一棵单词查找树中的链接总数在$RN$到$RNw$之间，其中$w$为键的平均长度。这意味着所有键比较短时，链接的总数接近于$RN$；当所有键比较长时，链接的总数接近于$RNw$。所以缩小$R$可以节省大量的空间。

总结就是：**命中查找时间成本与字符串的长度有关，而未命中查找时间成本与单词查找树中的键数量有关；而整个单词查找树的空间成本与键的数量、所基于字符集中的字符数量有关**。



#### 5.2.2 三向单词查找树

三向单词查找树可以认为是R向单词查找树的紧凑表示，其最大的好处在于可以很好的解决R向单词查找树所允许空间严重依赖于字符集中的字符R数量而造成的巨大空间需求。在三向单词查找树中，每个结点都含有一个字符、三条链接和一个值。这3条链接分别对应着当前字符小于、等于和大于结点字母的所有键。按照我们R向单词查找树的实现我们可以很好的完成上述数据结构的实现：

```java
public class TST<Value> {
    private Node root;

    private class Node {
        char c;
        Node left, mid, right;
        Value val;
    }

    private Node get(Node x, String key, int d) {
        if (x == null) return null;

        char c = key.charAt(d);
        if (c < x.c)
            return get(x.left, key, d);
        else if (c > x.c)
            return get(x.right, key, d);
        else if (d < key.length() - 1)
            return get(x.mid, key, d + 1);
        else return x;
    }

    public Value get(String key) {
        Node x = get(root, key, 0);
        if (x == null) return null;
        else return (Value) x.val;
    }

    private Node put(Node x, String key, Value val, int d) {
        char c = key.charAt(d);
        if (x == null) {
            x = new Node();
            x.c = c;
        }

        if (c < x.c)
            x.left = put(x.left, key, val, d);
        else if (c > x.c)
            x.right = put(x.right, key, val, d);
        else if (d < key.length() - 1)
            x.mid = put(x.mid, key, val, d + 1);
        else x.val = val;
        return x;
    }

    public void put(String key, Value val) {
        root = put(root, key, val, 0);
    }
}
```

三向单词查找树的形状如下：

<img src="image/2020-12-03 115705.png" alt="2020-12-03 115705" style="zoom:67%;" />

对于三向单词查找树有如下的性质：

- 由$N$个平均长度为$w$的字符串构造的三向单词查找树中的链接总数在$3N$到$3Nw$之间；
- 在一棵由$N$个随机字符串构造的三向单词查找树中，查找未命中平均需要比较字符$~InN$次。除了$~InN$次外，一次插入或命中的查找会比较一次被查找的键中的每个字符。



**各种字符串查找算法的性能比较**：

|       算法(数据结构)       | 未命中查找检查的字符数量 |        内存使用        |             优点             |
| :------------------------: | :----------------------: | :--------------------: | :--------------------------: |
|      二叉树查找(BST)       |       $c_1(lgN)^2$       |         $64N$          |      适用于随机排列的键      |
|     2-3树查找(红黑树)      |       $c_2(lgN)^2$       |         $64N$          |          有性能保障          |
|    线性探测法(并行数组)    |           $w$            |      $32N$~$128N$      |     内置类型，缓存散列值     |
| 字典树查找(R向单词查找树)  |        $log_R{N}$        | $(8R+56)N$~$(8R+56)Nw$ | 适用于较短的键和较小的字母表 |
| 字典树查找(三向单词查找树) |        $1.39lgN$         |      $64N$~$64Nw$      |       适用于非随机的键       |



### 5.3 子字符串查找

#### 5.3.1  暴力子字符串查找算法

时间复杂度：$NM$

空间复杂度：$N+M$

```java
import edu.princeton.cs.algs4.StdOut;

public class StrSearch {
    public static int BFSearch(String txt, String pat) {
        int M = txt.length(), N = pat.length();
        for (int i = 0; i <= M - N; ++i) {
            int j;
            //并不显式的回溯跟踪文本串的下标
            for (j = 0; j < N; ++j)
                if (txt.charAt(i + j) != pat.charAt(j))
                    break;
            if (j == N) return i;
        }
        return -1;
    }

    public static int BFSearch1(String txt, String pat) {
        int i, M = txt.length();
        int j, N = pat.length();
        for (i = 0, j = 0; i < M && j < N; ++i) {
            if (txt.charAt(i) == pat.charAt(j)) ++j;
            else {
                /* 若未匹配成功，显式回溯跟踪文本串的下标，
                    并复位跟踪匹配模式串的下标 */
                i -= j;
                j = 0;
            }
        }
        if (j == N) return i - N;
        else return -1;
    }

    public static void main(String[] args) {
        String txt = "hello world", pat = "world";
        StdOut.println(BFSearch1(txt, pat));
        StdOut.println(txt.substring(BFSearch1(txt, pat)));
    }
}
```



#### 5.3.2  KMP匹配算法

因为算法4中使用的有限状态自动机的方式来讲解KMP算法，我个人不是很喜欢那种理解方式，所以采用一般算法书籍中常用的“最大公共前后缀计算”的方式来讲解这一内容，并使用C++实现。

> 在这里推荐一个up主讲解的视频：[KMP字符串匹配算法](https://www.bilibili.com/video/BV1Px411z7Yo?from=search&seid=13799977324547539020)

时间复杂度：$N/M$~$NM$

空间复杂度：$N+M$

```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//计算模式字符串的最大公共前缀表
void prefix_table(const string &pattern, int prefix[], int n) {
	int len = 0, i = 1;
	prefix[0] = 0;
	while (i < n) {
		if (pattern[i] == pattern[len]) {
			len++;
			prefix[i] = len;
			i++;
		} else {
			/* 若当前最大公共前后缀无法虽然i的增加而增长，而退而寻找它之前的
			 * 第二大公共前后缀字符串，若当len为0时也找不到则直接将最大公共
			 * 前后缀数组prefix中的当前位置设置为0即可 */
			if (len > 0)
				len = prefix[len - 1];
			else {
				prefix[i] = len;
				i++;
			}
		}
	}
}

//向后移动一位最大公共前缀表，并将第0位设置为-1
void move_prefix(int prefix[], int n) {
	for (int i = n - 1; i > 0; --i)
		prefix[i] = prefix[i - 1];
	prefix[0] = -1;
}

//kmp算法执行子字符串查找
int kmp_search(const string &txt, const string &pat) {
	int i, M = txt.size();
	int j, N = pat.size();
	int *next = new int[N];
	prefix_table(pat, next, N);
	move_prefix(next, N);

	for (i = 0, j = 0; i < M && j < N;) {
		if (txt[i] == pat[j]) {
			i++;
			j++;
		} else {
			j = next[j];
			if (j == -1) {
				j = 0;
				i++;
			}
		}
	}
	delete[] next;
	if (j == N)
		return i - N;
	else
		return -1;
}

int main() {
	string txt("hello world"), pat("world");
	cout << kmp_search(txt, pat) << endl;
	cout << txt.substr(kmp_search(txt, pat), pat.size()) << endl;
	return 0;
}
```



##### 5.3.2.1  最大公共前后缀

众所周知，KMP算法的核心就是避免在文本串中的下标（指向当前待判的字符）在与模式字符串发生比较失败的时候进行回溯，防止不必要的重复比较。下面演示了KMP使用最大公共前后缀数组生成的next数组进行匹配时发生的前后两步：

<img src="image/kmp (2).jpg" alt="kmp (2)" style="zoom:50%;" />

<img src="image/kmp1.jpg" alt="kmp1" style="zoom:50%;" />

从上面的kmp匹配的过程中你可以看到文本串中的i在匹配的过程中并没有像暴力排序那样发生指针回溯的过程，其中两个最主要与BF算法不同的两个细节在于：①模式字符串pattern跳过了对文本串txt第2、3个字符开始的匹配；②模式字符串pattern中的下标j移动到了一个另一个位置。

对于第一个细节，如此操作的理由在于：由于模式字符串和上面的文本字符串在最后一个a字符前面的部分已经执行过了比较，我们知道下面abaa中前三个字符aba与上面的abac中的aba相同，而模式字符串第一个字符a却与后面的b不相同，因此我们显然可以知道若按照暴力匹配，下一步的abaa与bacb比较必然在第一个字符就会失败。因此我们可以直接跳过这个字符，让abaa与acba进行比较。

<img src="image/kmp2.jpg" alt="kmp2" style="zoom: 50%;" />

对于第二个细节，如此操作的理由在于：由于根据上面的推断abaa现在应该让文本串中的acba进行比较，但是由于aba这个字符串有着最大公共前后缀“a”。因此上一步的abaa与abac比较已经可以让我们知道前缀“a”和acba的第一个字符a的比较也是可以跳过的！所以我们可以直接将j设置成最大前后缀后边字符的下标，即：j=len(当前j前面字符串的最大前后缀)。

<img src="image/kmp3.jpg" alt="kmp3" style="zoom:50%;" />

由上我们可以知道只要，只要我们计算出一个模式字符串的最大公共前后缀数组，我们可以使得在子字符串匹配的过程中只发生模式字符串中的下标j回退而不发生文本字符串下标i的回退。而真正绝对j到底回退到那个模式字符串数组中的哪一个位实际上取决于由最大公共前后缀数组prefix_table生成的next数组。其算法伪代码大致如下：

```python
def kmp(txt,pattern):
	根据pattern生成最大公共前后缀数组prefix
	进而由prefix生成next数组
	
	for i < txt.len && j < pattern.len:
		if 当前字符与模式串中的字符相同:
            i++, j++
		#当前字符没有成功，试试模式串中最大公共前后缀后面开始的字符
		#我们规定若next[j]等于-1表示这个当前字符串前面的部分没有
		#最大公共前后缀，此时直接开始试文本串中下一个字符串，j复位
		else
			j = next[j]
			if j == -1:
            	i++, j = 0
     
	if j == pattern.len:
    	return i - pattern.len
    else return -1;
```



##### 5.3.2.2  计算最大公共前后缀

计算最大公共前后缀需要用到动态规划的思想。通过下面逐步计算最大公共前后缀数组的过程可以发现：当前最大公共前后缀的值可以通过前一个子字符串的结果进一步计算得到。

例如**①**“aba”的下一个最大前缀前后缀值若想成为2，那么只需要比较位置为1的b和当前字符（aba后面的那个字符）是否相等，若相等则将前一个最大公共前后缀的值+1放置到当前位置；**②**否则用前面字符串的第二长公共前后缀字符串后的第一个字符与当前字符比较，若相同用这个第二公共前后缀字符串长度+1放置到当前prefix数组位置。例如”**aba**cd**aba**b“需要计算当前位置的prefix值，而“abacdaba”的最大公共前后缀为“aba”，既然当前的“b”与“aba”后面的“c”不相同，那么当前最大公共前后缀显然不能+1。只能退而求其次看看“abacdaba”的第二公共前后缀“a”后面的b是否与当前字符相同，显然这里是相同的，所以我们可以用第二公共前后缀长度1+1放置到当前的prefix之中。如果上面的都不成立，则继续比较第3大公共前后缀。。。直到没有子前后缀就从头比较。

<img src="image/next.jpg" alt="next" style="zoom:50%;" />

我们可以用下面的伪代码来描述这一算法：

```
def prefix(str,prefixArr):
	prefixArr[0]
	当前最大公共前后缀len=0
	
	while i < len(str):
		if str[len] == str[i]:
			将当前prefixArr的最大公共前后缀值设置为len+1
			增加len、i
		else
			将len设置前面字符串的次公共前后缀长度
			if 前面已经没有次公共前后缀:
				prefixArr[i++] == 0
```

使用C++语言对此进行实现：

```c++
void prefix_table(const string &pattern, int prefix[], int n) {
	int len = 0, i = 1;
	prefix[0] = 0;
    
	while (i < n) {
		if (pattern[i] == pattern[len]) {
			len++;
			prefix[i] = len;
			i++;
		}
        else {
			if (len > 0)
				len = prefix[len - 1];
			else
				prefix[i++] = len;
		}
	}
}
```



##### 5.3.2.3  计算next数组

只需要对上面的prefix数组每一个元素右移一位即可，不过第一个元素需要设置为-1，表示当前模式字符串第一个字符和文本字符串当前字符不相同，此时需要对文本字符串中的下标i+1，使得游标向前进一格。



#### 5.3.3 Boyer-Moore字符串查找算法

Boyer-Moore字符串查找算法的核心就是**基于模式串的字符集合生成一个字符不匹配时的跳跃表（辅助数组），这个表可以告诉程序在字符发生不匹配时文本串的下标该跳跃到哪一个位置，然后再开始从右向左的匹配**（注意：Boyer-Moore算法是从右向左开始匹配的）。虽然程序看起来文本串的下标i一直都是处在跳跃的状态，但实际上由于文本串中的字符是基于i+j进行匹配的，所以Boyer-Moore算法是存在文本串字符重复比较（即真正的回溯）的现象的。



> 下面是以前不好的甚至是错误的观点：
>
> 与KMP算法类似，这些算法都是**基于模式字符串中生成一个辅助数组**（KMP中是next数组，告诉模式字符串在不匹配的时候下标该跳到哪里；对于Boyer-Moore数组指的是跳跃表，它用来告诉文本串在发生不匹配的时候该跳到哪个位置）**，并在发生字符不匹配的时候避免文本串下标回溯。两者的算法核心的不同在于：KMP利用的是模式串最大公共前后缀有无的特点，而Boyer-Moore利用的是当前未匹配成功的字符是否存在于模式字符串这一特点**。其表现形式的不同在于：KMP中下标跳跃的模式串中的下标（向前跳），而在Boyer-Moore算法中跳跃的是文本串中的下标（向后跳）。

##### 5.3.3.1  跳跃的过程

该算法的另一个特点在于它的比较过程是从右向左的，而不是从左向右的！在比较的过程中，若当前文本串中的字符和模式串中的字符不同，则需要通过如下的处理让文本串中的下标进行跳跃式步进，而模式串中的下标也可能发生更新：

1. **若当前匹配文本串字符存在于模式串的字符集合中，且模式串当前位置-跳跃表查询结果>0，则让文本串下标增大这个差值**；
2. **若当前匹配文本串字符存在于模式串的字符集合中，但模式串当前位置-跳跃表查询结果<0，则让文本串下标递增1步**；
3. **若当前匹配文本串字符不存在于模式串的字符集合中，故跳跃表查询结果为-1，则让文本串下标递增1步**。

下图展示了当前字符没有匹配成功，但该字符在模式串的字符集合之中，此时本文串下标跳跃的情况：

<img src="image/2020-12-11 110925.png" alt="2020-12-11 110925" style="zoom: 67%;" />

下图展示了当前字符没有匹配成功，且该字符不在模式串的字符集合之中，此时的文本串下标跳跃情况：

<img src="image/2020-12-11 111216.png" alt="2020-12-11 111216" style="zoom:67%;" />

##### 5.3.3.2  跳跃表的计算

跳跃表其实就是一个字符集合数组，若模式字符串出现了哪一个字符（遍历时最后出现）就在相应的额下标位置上记录该字符在模式字符串中的下标即可。若没有出现则在数组中初始化-1即可。



java代码实现：

```java
import edu.princeton.cs.algs4.StdOut;
import java.util.Arrays;

public class BoyerMoore {
    private int[] right;
    private String pat;

    //计算跳跃表
    BoyerMoore(String pat) {
        this.pat = pat;
        int M = pat.length();
        int R = 256;
        right = new int[R];
        Arrays.fill(right, -1);
        for (int j = 0; j < M; j++)
            right[pat.charAt(j)] = j;
    }

    public int search(String txt) {
        int M = txt.length();
        int N = pat.length();
        int skip;//文本串需要向右步进的量

        for (int i = 0; i <= M - N; i += skip) {
            skip = 0;
            for (int j = N - 1; j >= 0; j--)
                /* 若不匹配，则skip会被设置为正整数
                 * 1. 一种情况是当前匹配的文本串字符存在于模式串字符集合中，
                 *    且模式串当前位置-跳跃表查询得到的值>0；
                 * 2. 一种情况是当前匹配的文本串字符存在于模式串字符集合中，
                 *    但模式串当前位置-跳跃表查询得到的值<0；
                 * 3. 一种情况是当前匹配的文本串字符不存在于模式串字符集合中，
                 *    则查询跳跃表的结果<0。
                 * */
                if (pat.charAt(j) != txt.charAt(i + j)) {
                    skip = j - right[txt.charAt(i + j)];
                    if (skip < 1) skip = 1;
                    break;
                }
            if (skip == 0) return i;
        }
        return -1;
    }

    public static void main(String[] args) {
        String txt = "hello world", pat = "world";
        BoyerMoore boyerMoore = new BoyerMoore(pat);
        int b = boyerMoore.search(txt);
        StdOut.println(b);
        if (b != -1) StdOut.println(txt.substring(b));
    }
}

```

下面展示了一次完整的匹配过程：

<img src="image/2020-12-11 112850.png" alt="2020-12-11 112850" style="zoom:67%;" />

C++实现：

```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;

static void jump_table(const string &pat, vector<int> &jump) {
	fill(jump.begin(), jump.end(), -1);
	for (int i = 0; i < pat.length(); ++i)
		jump[i] = static_cast<int>(pat[i]);
}

int BoyerMooreSearch(const string &txt, const string &pat) {
	int M = txt.size(), N = pat.size();
	vector<int> jump(256);
	int skip;

	jump_table(pat, jump);
	for (int i = 0; i < M - N; i += skip) {
		skip = 0;
		for (int j = N - 1; j >= 0; --j)
			if (txt[i + j] != pat[j]) {
				skip = jump[txt[i + j]];
				if (skip < 1)
					skip = 1;
				break;
			}
		if (skip == 0)
			return i;
	}
	return -1;
}

int main() {
	string txt("talk is cheap, show me the code"), pat("show");
	int res = BoyerMooreSearch(txt, pat);
	cout << res << endl;
	if (res >= 0)
		cout << txt.substr(res, pat.size());

	return 0;
}
```



#### 5.3.4 Rabin-Karp指纹字符串查找算法

Rabin-Karp算法是一种基于Hash函数的字符串查找算法。其核心思想就是：**计算模式字符串的Hash值，然后用相同的Hash函数计算文本中所有可能的M个字符长度的子字符串的Hash值并一一匹配。若匹配成功，则再进行一次检验**（可能两两计算使用更大质数得到的Hash值）**，然后返回对应的子字符串起始下标。**

对于Hash值的计算主要是通过Horner算法逐位累加计算：
$$
当前字符串的Hash值=(上一个子字符串Hash值*R+当前位置字符值) \% Q
$$
而对于文本串中的Hash值是通过滑动窗口来计算得到的

<img src="image/Rabnihash.jpg" alt="Rabnihash" style="zoom:50%;" />

我们可以将其中一串子字符串的数值通过如下的表达式进行表达：
$$
x_i=t_iR^{M-1}+t_{i+1}R^{M-2}+...+t_{i+M-1}*R^0
$$
而通过滑动窗口得到的下一个字符串的数值表达式为：
$$
x_{i+1}=x_iR-t_iR^{M-1}R+t_{i+M}R^0\\
=(x_i-t_iR^{M-1})+t_{i+M}
$$
因此我们可以从上面推导出来的表达式得知：我们可以从之前计算得到关于$x_i$的hash值，进而通过上述的公式计算下一个子字符串的hash值。

这样我们就可以根据模式字符串的hash和文本串在滑动过程产生的hash值一一比较，然后找到那个想要的子字符串的起始下标位置。

```java
import edu.princeton.cs.algs4.StdOut;

import java.math.BigInteger;
import java.util.Random;

public class RobinKarp {
    private long patHash;
    private int R = 256;
    private long Q;
    private int M;
    private long RM;    //R^(M-1) % Q

    //对Hash值匹配一致的字符串再次执行检验，不过我们这里并没有真正这么做
    private boolean check(int i) {
        return true;
    }

    //计算一个长素数
    private static long makeprime() {
        BigInteger prime = new BigInteger(31, new Random());
        return prime.longValue();
    }

    //使用Horner方法计算R进制M长字符串的Hash值
    private long hash(String str, int M) {
        long h = 0;
        for (int i = 0; i < M; ++i)
            h = (R * h + str.charAt(i)) % Q;
        return h;
    }

    RobinKarp(String pat) {
        M = pat.length();
        Q = makeprime();
        RM = 1;
        for (int i = 1; i < M; ++i)
            RM = (R * RM) % Q;
        patHash = hash(pat, M);
    }

    public int search(String txt) {
        int N = txt.length();
        long txthash = hash(txt, M);

        //若txt中的第一个子字符串就是想要找的，那么直接检验后返回
        if (txthash == patHash && check(0)) return 0;
        for (int i = M; i < N; ++i) {
            //计算：[(x_i + R^(M - 1)) * R + t_(i + M)] mode Q
            txthash = (txthash + Q - RM * txt.charAt(i - M) % Q) % Q;
            txthash = (txthash * R + txt.charAt(i)) % Q;
            if (txthash == patHash && check(i - M + 1))
                return i - M + 1;
        }
        return -1;
    }

    public static void main(String[] args) {
        String txt = "hello world", pat = "world";
        RobinKarp robinKarp = new RobinKarp(pat);
        int index = robinKarp.search(txt);

        StdOut.println(index);
        if (index != -1)
            StdOut.println(txt.substring(index));
    }
}
```



各种子字符串查找算法对比总结：

|    算法     | 时间复杂度（最坏） | 时间复杂度（一般） | 空间复杂度 | 是否存在文本重复比较（回溯） |
| :---------: | :----------------: | :----------------: | :--------: | :--------------------------: |
|  暴力匹配   |        $MN$        |       $1.1N$       |    $1$     |              ✔               |
|     KMP     |        $3N$        |       $1.1N$       |    $M$     |              ✘               |
| Boyer-Moore |        $MN$        |       $N/M$        |    $R$     |              ✘               |
| Rabin-Karp  |        $7N$        |        $7N$        |    $1$     |              ✔               |

其中KMP和Rabin-Karp算法的时间复杂度在线性阶，Boyer-Moore算法的时间复杂度在亚线性阶，但两者都需要额外的辅助空间。



### 5.4 正则表达式

