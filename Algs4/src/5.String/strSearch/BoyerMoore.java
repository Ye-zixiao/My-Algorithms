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
