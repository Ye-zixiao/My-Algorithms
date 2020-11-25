import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DirectedDFS {
    private boolean[] marked;

    //使用递归实现的深度优先搜索方法
    private void dfs(Digraph G, int v) {
        marked[v] = true;
        for (int w : G.adj(v))
            if (!marked[w]) dfs(G, w);
    }

    //使用栈实现的深度优先搜索方法
    private void dfs1(Digraph G, int v) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(v);
        marked[v] = true;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int w : G.adj(t)) {
                if (!marked[w]) {
                    stack.push(w);
                    marked[w] = true;
                }
            }
        }
    }

    public boolean marked(int v) {
        return marked[v];
    }

    public DirectedDFS(Digraph G, int s) {
        marked = new boolean[G.V()];
        dfs1(G, s);
    }

    public DirectedDFS(Digraph G, Iterable<Integer> sources) {
        marked = new boolean[G.V()];
        for (int s : sources)
            if (!marked[s]) dfs1(G, s);
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));

        Bag<Integer> sources = new Bag<Integer>();
        for (int i = 1; i < args.length; ++i)
            sources.add(Integer.parseInt(args[i]));

        DirectedDFS reachable = new DirectedDFS(digraph, sources);
        for (int v = 0; v < digraph.V(); v++)
            if (reachable.marked(v)) StdOut.print(v + " ");
        StdOut.println();
    }
}
