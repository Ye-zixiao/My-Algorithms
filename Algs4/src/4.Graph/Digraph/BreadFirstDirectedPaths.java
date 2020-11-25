import edu.princeton.cs.algs4.*;

public class BreadFirstDirectedPaths {
    private boolean[] marked;
    private int[] parents;
    private final int s;

    //广度优先搜索路径方法
    private void bfs(Digraph G, int s) {
        Queue<Integer> queue = new Queue<Integer>();
        queue.enqueue(s);
        marked[s] = true;
        parents[s] = s;

        while (!queue.isEmpty()) {
            int t = queue.dequeue();
            for (int w : G.adj(t)) {
                if (!marked[w]) {
                    queue.enqueue(w);
                    marked[w] = true;
                    parents[w] = t;
                }
            }
        }
    }

    public BreadFirstDirectedPaths(Digraph G, int s) {
        marked = new boolean[G.V()];
        parents = new int[G.V()];
        this.s = s;
        bfs(G, s);
    }

    public boolean hasPathTo(int v) {
        return marked[v];
    }

    //返回从起点s到指定点v的路径容器引用
    public Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v)) return null;

        Stack<Integer> stack = new Stack<Integer>();
        for (int p = v; p != s; p = parents[p])
            stack.push(p);
        stack.push(s);
        return stack;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        int s = Integer.parseInt(args[1]);
        BreadFirstDirectedPaths paths = new BreadFirstDirectedPaths(digraph, s);

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
