import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class KosarajuCC {
    private boolean[] marked;
    private int[] id;
    private int count;

    //使用递归实现的深度优先遍历算法，以将同一个强连通分量中的顶点进行标识
    private void dfs(Digraph G, int v) {
        marked[v] = true;
        id[v] = count;
        for (int w : G.adj(v))
            if (!marked[w])
                dfs(G, w);
    }

    //使用栈实现的深度优先遍历算法，以将同一个强连通分量中的顶点进行标识
    private void dfs1(Digraph G, int v) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(v);
        marked[v] = true;
        id[v] = count;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int w : G.adj(t)) {
                if (!marked[w]) {
                    stack.push(w);
                    marked[w] = true;
                    id[w] = count;
                }
            }
        }
    }

    public KosarajuCC(Digraph G) {
        marked = new boolean[G.V()];
        id = new int[G.V()];
        DepthFirstOrder order = new DepthFirstOrder(G.reverse());
        for (int s : order.reversePost())
            if (!marked[s]) {
                dfs1(G, s);
                count++;
            }
    }

    public boolean stronglyConnected(int v, int w) {
        return id[v] == id[w];
    }

    public int id(int v) {
        return id[v];
    }

    public int count() {
        return count;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        KosarajuCC cc = new KosarajuCC(digraph);

        int M = cc.count();
        StdOut.println(digraph.V() + " vertexes, " + M +
                " strongly connected components:");

        Bag<Integer>[] bags = new Bag[M];
        for (int i = 0; i < M; ++i)
            bags[i] = new Bag<Integer>();
        for (int i = 0; i < digraph.V(); ++i)
            bags[cc.id(i)].add(i);

        for (int i = 0; i < M; ++i) {
            for (int v : bags[i])
                StdOut.print(v + " ");
            StdOut.println();
        }
    }
}
