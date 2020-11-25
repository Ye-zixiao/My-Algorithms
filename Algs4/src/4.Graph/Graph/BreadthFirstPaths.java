import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class BreadthFirstPaths {
    private boolean[] marked;
    private int[] edgeTo;//存储递归过程中当前点的前一个点的索引
    private final int s;

    private void bfs(Graph G, int s) {
        Queue<Integer> queue = new Queue<Integer>();
        queue.enqueue(s);
        edgeTo[s] = s;
        marked[s] = true;

        while (!queue.isEmpty()) {
            int t = queue.dequeue();
            for (int w : G.adj(t))
                if (!marked[w]) {
                    queue.enqueue(w);
                    edgeTo[w] = t;
                    marked[w] = true;
                }
        }
    }

    public BreadthFirstPaths(Graph G, int s) {
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        this.s = s;
        bfs(G, s);
    }

    public boolean hasPathTo(int v) {
        return marked[v];
    }

    //返回从s->v的路径
    public Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v)) return null;

        Stack<Integer> stack = new Stack<Integer>();
        for (int x = v; x != s; x = edgeTo[x])
            stack.push(x);
        stack.push(s);
        return stack;
    }

    public static void main(String[] args) {
        Graph graph = new Graph(new In(args[0]));
        int s = Integer.parseInt(args[1]);
        DepthFirstPaths paths = new DepthFirstPaths(graph, s);

        for (int v = 0; v < graph.V(); ++v) {
            StdOut.print(s + " to " + v + ": ");
            if (paths.hasPathTo(v))
                for (int x : paths.pathTo(v))
                    if (x == s) StdOut.print(x);
                    else StdOut.print("-" + x);
            StdOut.println();
        }
    }
}