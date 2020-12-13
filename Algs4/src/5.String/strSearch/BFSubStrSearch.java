import edu.princeton.cs.algs4.StdOut;

public class BFSubStrSearch {
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
