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

            for (int r = 0; r < R; r++)
                count[r + 1] += count[r];

            for (int i = 0; i < N; i++)
                aux[count[a[i].charAt(d)]++] = a[i];

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

        LSD.sort(a, a[0].length());
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

