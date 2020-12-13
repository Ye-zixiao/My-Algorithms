import edu.princeton.cs.algs4.Alphabet;
import edu.princeton.cs.algs4.StdOut;

public class MSD {
    private static int R = Alphabet.EXTENDED_ASCII.R();
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