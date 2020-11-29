import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.UF;

import java.util.ArrayDeque;
import java.util.Queue;

public class KruskalMST {
    private Queue<Edge> mst;

    public KruskalMST(EdgeWeightedGraph G) {
        mst = new ArrayDeque<Edge>();
        MinPQ<Edge> pq = new MinPQ<Edge>();
        UF uf = new UF(G.V());
        for (Edge e : G.edges()) pq.insert(e);

        while (!pq.isEmpty() && mst.size() < G.V() - 1) {
            Edge e = pq.delMin();
            int v = e.either(), w = e.other(v);
            /* 若这两条边之前就已经相连了，则此时再添加这条v-w的新边，
             *   必然会导致MST形成一个环，所以我们应该跳过这条边，将其
             *   从最小优先队列中删除 */
            if (uf.connected(v, w)) continue;
            uf.union(v, w);
            mst.add(e);
        }
    }

    public Iterable<Edge> edges() {
        return mst;
    }

    public double weight() {
        double ret = 0.0;
        for (Edge e : mst)
            ret += e.weight();
        return ret;
    }

    public static void main(String[] args) {
        EdgeWeightedGraph graph = new EdgeWeightedGraph(new In(args[0]));
        KruskalMST mst = new KruskalMST(graph);
        for (Edge edge : mst.edges())
            StdOut.println(edge);
        StdOut.printf("total weight: %.2f", mst.weight());
    }
}
