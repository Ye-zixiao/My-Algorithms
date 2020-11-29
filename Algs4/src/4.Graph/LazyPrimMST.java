import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

public class LazyPrimMST {
    private boolean[] marked;
    private Queue<Edge> mst;
    private MinPQ<Edge> pq;

    public LazyPrimMST(EdgeWeightedGraph G) {
        pq = new MinPQ<Edge>();
        marked = new boolean[G.V()];
        mst = new Queue<Edge>();

        visit(G, 0);
        while (!pq.isEmpty()) {
            Edge e = pq.delMin();

            int v = e.either(), w = e.other(v);
            /* 之所以需要跳过一些无效的边，是因为这些边之前就被添加到
             *   最小优先队列之中（当时它们确实是有效的），但是随着两端
             *   顶点陆续加入MST就导致这些边变得无效，且仍然存在于MinPQ
             *   之中。因此我们必须通过检查优先队列之中每一条取出边，通过
             *   检查两端的顶点是否加入到MST的方法来检测这条边是否有效。
             *   只有在有效的前提下加入到MST之中 */
            if (marked[v] && marked[w]) continue;
            mst.enqueue(e);
            if (!marked[v]) visit(G, v);
            if (!marked[w]) visit(G, w);

        }
    }

    //将v的所有有效邻边加入到MinPQ之中
    private void visit(EdgeWeightedGraph G, int v) {
        marked[v] = true;
        for (Edge edge : G.adj(v))
            if (!marked[edge.other(v)])
                pq.insert(edge);
    }

    //返回最小生成树中的所有边
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
        LazyPrimMST mst = new LazyPrimMST(graph);

        for (Edge e : mst.edges())
            StdOut.println(e);
    }
}
