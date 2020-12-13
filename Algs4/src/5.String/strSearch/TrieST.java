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
        for (String str : trieST.keys())
            StdOut.println(str);
    }
}
