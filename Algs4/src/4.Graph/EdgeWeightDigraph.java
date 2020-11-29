import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class EdgeWeightDigraph {
    private final int V;
    private int E;
    private Bag<DirectedEdge>[] adj;

    public EdgeWeightDigraph(int V) {
        this.V = V;
        this.E = 0;
        adj = (Bag<DirectedEdge>[]) new Bag[V];
        for (int v = 0; v < V; ++v)
            adj[v] = new Bag<DirectedEdge>();
    }

    public EdgeWeightDigraph(In in) {
        this(in.readInt());
        this.E = in.readInt();
        while (!in.isEmpty()) {
            DirectedEdge edge = new DirectedEdge(in.readInt(), in.readInt(), in.readDouble());
            addEdge(edge);
        }
    }

    public int V() {
        return V;
    }

    public int E() {
        return E;
    }

    public void addEdge(DirectedEdge edge) {
        adj[edge.from()].add(edge);
//        E++;
    }

    public Iterable<DirectedEdge> adj(int v) {
        return adj[v];
    }

    public Iterable<DirectedEdge> edges() {
        Bag<DirectedEdge> bag = new Bag<DirectedEdge>();
        for (int v = 0; v < V; ++v)
            for (DirectedEdge edge : adj[v])
                bag.add(edge);
        return bag;
    }

    public static void main(String[] args) {
        EdgeWeightDigraph digraph = new EdgeWeightDigraph(new In(args[0]));

        for (int v = 0; v < digraph.V(); ++v) {
            for (DirectedEdge edge : digraph.adj(v))
                StdOut.print(edge + "  ");
            StdOut.println();
        }
    }
}
