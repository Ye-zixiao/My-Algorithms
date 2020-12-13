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

