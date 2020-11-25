import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DepthFirstDirectedPaths {
    private boolean[] marked;
    private int[] edgeTo;
    private final int s;

    //使用递归实现的深度优先搜索方法
    private void dfs(Digraph G, int s) {
        marked[s] = true;
        for (int w : G.adj(s))
            if (!marked[w]) {
                edgeTo[w] = s;
                dfs(G, w);
            }
    }

    //使用栈实现的深度优先搜索方法
    private void dfs1(Digraph G, int s) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(s);
        edgeTo[s] = s;
        marked[s] = true;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int w : G.adj(t)) {
                if (!marked[w]) {
                    stack.push(w);
                    edgeTo[w] = t;
                    marked[w] = true;
                }
            }
        }
    }

    public DepthFirstDirectedPaths(Digraph G, int s) {
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        this.s = s;
        dfs1(G, s);
    }

    public boolean hasPathTo(int v) {
        return marked[v];
    }

    //返回从起点s到指定点v的路径容器引用
    public Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v)) return null;

        Stack<Integer> stack = new Stack<Integer>();
        for (int p = v; p != s; p = edgeTo[p])
            stack.push(p);
        stack.push(s);
        return stack;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        int s = Integer.parseInt(args[1]);
        DepthFirstDirectedPaths paths = new DepthFirstDirectedPaths(digraph, s);

        for (int v = 0; v < digraph.V(); ++v) {
            StdOut.print(s + " to " + v + ": ");
            if (paths.hasPathTo(v))
                for (int x : paths.pathTo(v))
                    if (x == s) StdOut.print(x);
                    else StdOut.print("-" + x);
            StdOut.println();
        }
    }
}
