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
