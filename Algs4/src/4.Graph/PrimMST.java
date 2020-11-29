import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.IndexMinPQ;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

public class PrimMST {
    private Edge[] edgeTo;
    private double[] distTo;
    private boolean[] marked;
    private IndexMinPQ<Double> pq;
    /* 所以优先队列的功能就是将一个索引与真正比较优先级的键进行关联，
       在优先队列执行时，放入二叉堆的是索引，通过索引去比较两个键，并对
       索引进行排序 */

    public PrimMST(EdgeWeightedGraph G) {
        edgeTo = new Edge[G.V()];
        distTo = new double[G.V()];
        marked = new boolean[G.V()];
        for (int v = 0; v < G.V(); ++v)
            distTo[v] = Double.POSITIVE_INFINITY;
        pq = new IndexMinPQ<Double>(G.V());

        distTo[0] = 0.0;
        pq.insert(0, 0.0);
        while (!pq.isEmpty())
            visit(G, pq.delMin());
    }

    /* 访问结点v的所有邻边，若该边有效且它的权重比现有w到最小生成树的权
        重还要低，则将其替换为最新边edgeTo[w]=...和权重值distTo[w]=... */
    private void visit(EdgeWeightedGraph G, int v) {
        marked[v] = true;
        for (Edge e : G.adj(v)) {
            int w = e.other(v);
            if (!marked[w] && e.weight() < distTo[w]) {
                edgeTo[w] = e;
                distTo[w] = e.weight();
                if (pq.contains(w)) pq.changeKey(w, distTo[w]);
                else pq.insert(w, distTo[w]);
            }
        }
    }

    //返回最小生成树中的所有边
    public Iterable<Edge> edges() {
        Queue<Edge> queue = new Queue<Edge>();
        for (Edge edge : edgeTo)
            if (edge != null)
                queue.enqueue(edge);
        return queue;
    }

    public double weight() {
        double ret = 0.0;
        for (Edge edge : edges())
            ret += edge.weight();
        return ret;
    }

    public static void main(String[] args) {
        EdgeWeightedGraph graph = new EdgeWeightedGraph(new In(args[0]));
        PrimMST mst = new PrimMST(graph);

        for (Edge edge : mst.edges())
            StdOut.println(edge);
        StdOut.printf("Total price: %.2f", mst.weight());
    }
}