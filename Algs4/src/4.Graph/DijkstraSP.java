import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.IndexMinPQ;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DijkstraSP {
    private DirectedEdge[] edgeTo;  //edgeTo[w]表示s->w最短路径中w的父顶点v到w的那条边
    private double[] distTo;        //distTo[w]表示s->w最短路径中s到w的最短路径权重距离
    private IndexMinPQ<Double> pq;

    public DijkstraSP(EdgeWeightDigraph G, int s) {
        edgeTo = new DirectedEdge[G.V()];
        distTo = new double[G.V()];
        pq = new IndexMinPQ<Double>(G.V());

        for (int v = 0; v < G.V(); ++v)
            distTo[v] = Double.POSITIVE_INFINITY;
        distTo[s] = 0.0;

        pq.insert(s, 0.0);
        while (!pq.isEmpty())
            relax(G, pq.delMin());
    }

    /* 放松操作：将指定点v的所有邻边信息去更新edgeTo[w]和distTo[w]，
     *   若到通过这条边到w的距离更小就更新，否则不更新 */
    private void relax(EdgeWeightDigraph G, int v) {
        for (DirectedEdge e : G.adj(v)) {
            int w = e.to();
            if (distTo[w] > distTo[v] + e.weight()) {
                distTo[w] = distTo[v] + e.weight();
                edgeTo[w] = e;
                if (pq.contains(w)) pq.changeKey(w, distTo[w]);
                else pq.insert(w, distTo[w]);
            }
        }
    }

    public double distTo(int v) {
        return distTo[v];
    }

    public boolean hasPathTo(int v) {
//        return edgeTo[v]!=null;
        return distTo[v] < Double.POSITIVE_INFINITY;
    }

    public Iterable<DirectedEdge> pathTo(int v) {
        if (!hasPathTo(v)) return null;
        Stack<DirectedEdge> path = new Stack<DirectedEdge>();
        for (DirectedEdge e = edgeTo[v]; e != null; e = edgeTo[e.from()])
            path.push(e);
        return path;
    }

    public static void main(String[] args) {
        EdgeWeightDigraph digraph = new EdgeWeightDigraph(new In(args[0]));
        DijkstraSP dijkstraSP = new DijkstraSP(digraph, 0);

        for (int v = 1; v < digraph.V(); ++v) {
            StdOut.print(0 + "->" + v + ": ");
            double weight = 0.0;
            for (DirectedEdge edge : dijkstraSP.pathTo(v)) {
                weight += edge.weight();
                if (edge.from() != 0)
                    StdOut.printf("->%d", edge.to());
                else
                    StdOut.printf("%d->%d", edge.from(), edge.to());
            }
            StdOut.printf("   (total weight: %.2f)\n", weight);
        }
    }
}