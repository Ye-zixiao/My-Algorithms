import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DepthFirstOrder {
    private boolean[] marked;
    private Queue<Integer> pre;
    private Queue<Integer> post;
    private Stack<Integer> reversePost;

    private void dfs(Digraph G, int v) {
        pre.enqueue(v);//前序遍历

        marked[v] = true;
        for (int w : G.adj(v))
            if (!marked[w]) dfs(G, w);

        post.enqueue(v);//后序遍历
        reversePost.push(v);//逆后序遍历，得到的正是深度优先排序
    }

    public DepthFirstOrder(Digraph G) {
        pre = new Queue<Integer>();
        post = new Queue<Integer>();
        reversePost = new Stack<Integer>();
        marked = new boolean[G.V()];
        for (int v = 0; v < G.V(); ++v)
            if (!marked[v]) dfs(G, v);
    }

    //返回前序遍历
    public Iterable<Integer> pre() {
        return pre;
    }

    //返回后序遍历
    public Iterable<Integer> post() {
        return post;
    }

    //返回逆后序遍历
    public Iterable<Integer> reversePost() {
        return reversePost;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        DepthFirstOrder order = new DepthFirstOrder(digraph);

        for (int v : order.reversePost())
            StdOut.print(v + " ");
        StdOut.println();
    }
}
