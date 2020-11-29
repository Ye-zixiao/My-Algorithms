import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class EdgeWeightedGraph {
    private final int V;
    private int E;
    private Bag<Edge>[] adj;

    public EdgeWeightedGraph(int V) {
        this.V = V;
        this.E = 0;
        adj = (Bag<Edge>[]) new Bag[V];
        for (int v = 0; v < V; ++v)
            adj[v] = new Bag<Edge>();
    }

    public EdgeWeightedGraph(In in) {
        this(in.readInt());
        int E = in.readInt();
        for (int i = 0; i < E; i++) {
            Edge edge = new Edge(in.readInt(), in.readInt(), in.readDouble());
            addEdge(edge);
        }
    }

    public void addEdge(Edge e) {
        int v = e.either(), w = e.other(v);
        adj[v].add(e);
        adj[w].add(e);
        E++;
    }

    //返回某一顶点的所有邻边
    public Iterable<Edge> adj(int v) {
        return adj[v];
    }

    //返回存放加权无向图中的所有的边的容器
    public Iterable<Edge> edges() {
        Bag<Edge> b = new Bag<Edge>();
        for (int v = 0; v < V; v++)
            for (Edge e : adj[v])
                /* 因为边Edge会在加权无向图中的两个顶点的邻接表中存放两次，
                    所以我们在将边存放到容器中时应当避免存放两次。在这里只
                    获取存放在索引较小的顶点邻接表中的边 */
                if (e.other(v) > v) b.add(e);
        return b;
    }

    public int V() {
        return V;
    }

    public int E() {
        return E;
    }

    public static void main(String[] args) {
        EdgeWeightedGraph graph = new EdgeWeightedGraph(new In(args[0]));

        for (Edge edge : graph.edges())
            StdOut.println(edge);
    }
}
