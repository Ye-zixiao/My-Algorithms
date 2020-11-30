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

高位优先的字符串排序的基本思想很简单：就是先根据字符串的首字符进行排序，然后再在具有相同起始字符的字符串中排序（而不是全部排序）。例如在String[]{"string","hello","show","surely"}经过第一轮的排序之后，会将s开头的字符串和h开头的字符串分离开来，此时我们第二轮只要在s开头的字符串集合{"tring","how","urely"}之间进行排序，“ello”就不用再参与进来（它只要自己和自己比较行了）。

高位优先排序的难点在于处理不同长度的字符串。在这里我们使用的处理方法就是：不断地递归调用sort，而sort每一次都只根据子字符串中第一个字符对字符串数组进行排序，完成之后对首字符相同的字符串数组部分根据它们的首字符递归调用sort进行排序，直到遇到这个起始字符后面的子字符串数组为空。

如果字符串之间长度不同，那么随着递归的推荐，最终总会有些字符串在sort函数中呈现出的子字符串为空（实际中，我们用字符下标>=字符串长度时，表示检测到子字符串为空），那么显然这些字符串应该自动地放到源字符串数组的前面位置。接着再对剩下的子字符串进行递归比较。如图所示：

<img src="image/MSD.jpg" alt="MSD" style="zoom: 50%;" />

```java
import edu.princeton.cs.algs4.StdOut;

public class MSD {
    private static int R = 256;
    private static final int M = 15;
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



