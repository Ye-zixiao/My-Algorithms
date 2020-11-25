import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class Topological {
    private Iterable<Integer> order;

    public Topological(Digraph G) {
        DirectedCycle cyclefinder = new DirectedCycle(G);
        if (!cyclefinder.hasCycle()) {
            DepthFirstOrder dfs = new DepthFirstOrder(G);
            order = dfs.reversePost();
        }
    }

    public Iterable<Integer> order() {
        return order;
    }

    public boolean isDAG() {
        return order != null;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        Topological topological = new Topological(digraph);

        if (topological.isDAG()) {
            for (int v : topological.order())
                StdOut.print(v + " ");
            StdOut.println();
        }
    }
}
