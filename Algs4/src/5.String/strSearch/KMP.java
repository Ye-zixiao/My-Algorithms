import edu.princeton.cs.algs4.StdOut;

public class KMP {
    private static int[] next;

    private static void prefix_table(String pat) {
        int i = 1, len = 0;

        while (i < pat.length()) {
            if (pat.charAt(len) == pat.charAt(i)) {
                len++;
                next[i++] = len;
            } else {
                if (len > 0)
                    len = next[len - 1];
                else
                    next[i++] = 0;
            }
        }
    }

    private static void create_next(String pat) {
        next = new int[pat.length()];
        prefix_table(pat);
        for (int i = pat.length() - 1; i > 0; --i)
            next[i] = next[i - 1];
        next[0] = -1;
    }

    public static int kmp(String str, String pat) {
        int i, M = str.length();
        int j, N = pat.length();
        create_next(pat);

        for (i = 0, j = 0; i < M && j < N; ) {
            if (str.charAt(i) == pat.charAt(j)) {
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
        if (j == N) return i - N;
        else return -1;
    }

    public static void main(String[] args) {
        String txt = "hello world", pat = "world";
        int k = kmp(txt, pat);
        StdOut.println(k);
        if (k >= 0) StdOut.println(txt.substring(k));
    }
}
