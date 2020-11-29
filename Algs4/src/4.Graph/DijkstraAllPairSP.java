import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class DijkstraAllPairSP {
    private DijkstraSP[] all;

    public DijkstraAllPairSP(EdgeWeightDigraph G) {
        all = new DijkstraSP[G.V()];
        for (int v = 0; v < G.V(); ++v)
            all[v] = new DijkstraSP(G, v);
    }

    public Iterable<DirectedEdge> path(int s, int t) {
        return all[s].pathTo(t);
    }

    public double dist(int s, int t) {
        return all[s].distTo(t);
    }

    public static void main(String[] args) {
        EdgeWeightDigraph digraph = new EdgeWeightDigraph(new In(args[0]));
        DijkstraAllPairSP sp = new DijkstraAllPairSP(digraph);

        StdOut.printf("weight of 0 to 6: %.2f", sp.dist(0, 6));
    }
}
