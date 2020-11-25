import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DepthFirstPaths {
    private boolean[] marked;
    private int[] edgeTo;//存储递归过程中当前点的前一个点的索引
    private final int s;

    //使用栈实现的深度优先搜索路径方法
    private void dfs(Graph G, int s) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(s);
        marked[s] = true;
        edgeTo[s] = s;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int ver : G.adj(t)) {
                if (!marked[ver]) {
                    stack.push(ver);
                    marked[ver] = true;
                    edgeTo[ver] = t;
                }
            }
        }
    }

    //使用递归实现的深度优先搜索路径方法
    private void dfs1(Graph G, int s) {
        marked[s] = true;
        for (int w : G.adj(s)) {
            if (!marked[w]) {
                edgeTo[w] = s;
                dfs1(G, w);
            }
        }
    }

    public DepthFirstPaths(Graph G, int s) {
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        this.s = s;
//        edgeTo[s]=s;
//        dfs1(G,s);
        dfs(G, s);
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

        Cycle cycle=new Cycle(graph);
        if(cycle.hasCycle())
            StdOut.println("has cycle");
        else StdOut.println("has no cycle");
    }
}