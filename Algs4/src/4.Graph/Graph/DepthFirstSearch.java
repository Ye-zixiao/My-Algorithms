import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DepthFirstSearch {
    private boolean[] marked;
    private int count;

    //实现递归实现的深度优先搜索
    private void dfs(Graph G, int v) {
        marked[v] = true;
        count++;
        for (int w : G.adj(v))
            if (!marked[w]) dfs(G, w);
    }

    //使用栈实现的深度优先搜索
    private void dfs1(Graph G, int v) {
        Stack<Integer> stack = new Stack<Integer>();
        marked[v] = true;
        stack.push(v);
        count++;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int vertex : G.adj(t)) {
                if (!marked[vertex]) {
                    marked[vertex] = true;
                    stack.push(vertex);
                    count++;
                }
            }
        }

    }

    public DepthFirstSearch(Graph G, int s) {
        marked = new boolean[G.V()];
        dfs1(G, s);
    }

    public boolean marked(int w) {
        return marked[w];
    }

    public int count() {
        return count;
    }

    public static void main(String[] args) {
        Graph G = new Graph(new In(args[0]));
        int s = Integer.parseInt(args[1]);
        DepthFirstSearch search = new DepthFirstSearch(G, s);

        StdOut.println("start vertex(" + s + ") connects: ");
        for (int v = 0; v < G.V(); v++)
            if (search.marked(v))
                StdOut.print(v + " ");
        StdOut.println();
        StdOut.println("connected count: " + search.count());
    }
}
