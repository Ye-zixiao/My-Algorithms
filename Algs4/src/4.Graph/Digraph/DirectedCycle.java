import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DirectedCycle {
    private boolean[] marked;
    private int[] edgeTo;
    private Stack<Integer> cycle;
    private boolean[] onStack;

    private void dfs(Digraph G, int v) {
        onStack[v] = true;
        marked[v] = true;
        for (int w : G.adj(v)) {
            //若之前已经找到一个环了，则既然已经判定了有环就没有必要再找了
            if (this.hasCycle()) return;
            else if (!marked[w]) {
                edgeTo[w] = v;
                dfs(G, w);
            }
            /* 若w在栈中，说明有个v->w有个环，那么我们就可以沿着edgeTo数组向回找
                以将这个环中的所有结点(v->w->v)加入到cycle中 */
            else if (onStack[w]) {
                cycle = new Stack<Integer>();
                for (int p = v; p != w; p = edgeTo[p])
                    cycle.push(p);
                cycle.push(w);
                cycle.push(v);
            }
        }
        onStack[v] = false;
    }

    public DirectedCycle(Digraph G) {
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        onStack = new boolean[G.V()];
        for (int v = 0; v < G.V(); ++v)
            if (!marked[v]) dfs(G, v);
    }

    public boolean hasCycle() {
        return cycle != null;
    }

    public Iterable<Integer> cycle() {
        return cycle;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        DirectedCycle cycle = new DirectedCycle(digraph);

        if (cycle.hasCycle()) {
            StdOut.println("This Digragh has cycle:");
            for (int v : cycle.cycle()) {
                StdOut.print(v + " ");
            }
            StdOut.println();
        }
    }
}
