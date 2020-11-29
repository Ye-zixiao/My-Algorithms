import edu.princeton.cs.algs4.*;
import edu.princeton.cs.algs4.DirectedEdge;

import java.util.Arrays;
import java.util.Stack;

public class BellmanFordSPQ {
    private double[] distTo;
    private DirectedEdge[] edgeTo;
    private Queue<Integer> queue;
    private boolean[] onQ;

    //对v->w进行松弛操作
    private void relax(EdgeWeightedDigraph G, int v) {
        for (DirectedEdge e : G.adj(v)) {
            int w = e.to();
            if (distTo[w] > distTo[v] + e.weight()) {
                distTo[w] = distTo[v] + e.weight();
                edgeTo[w] = e;
                //若指出顶点没有在队列之中，那么就将其加入到队列中
                if (!onQ[w]) {
                    onQ[w] = true;
                    queue.enqueue(w);
                }
            }
        }
    }

    //正常执行的前提是该加权有向图中没有负权重环
    public BellmanFordSPQ(EdgeWeightedDigraph G, int s) {
        distTo = new double[G.V()];
        edgeTo = new DirectedEdge[G.V()];
        queue = new Queue<Integer>();
        onQ = new boolean[G.V()];
        Arrays.fill(distTo, Double.POSITIVE_INFINITY);

        /* 这里所用的算法思想（在图中不存在负权重环情况下）就是
            广度优先遍历BFS算法 */
        distTo[s] = 0.0;
        queue.enqueue(s);
        while (!queue.isEmpty()) {
            int v = queue.dequeue();
            onQ[v] = false;
            relax(G, v);
        }
    }

    public boolean hasPathTo(int v) {
        return distTo[v] < Double.POSITIVE_INFINITY;
    }

    public double distTo(int v) {
        return distTo[v];
    }

    public Iterable<DirectedEdge> pathTo(int v) {
        if (!hasPathTo(v)) return null;
        Stack<DirectedEdge> stack = new Stack<DirectedEdge>();
        for (DirectedEdge e = edgeTo[v]; e != null; e = edgeTo[e.from()])
            stack.push(e);
        return stack;
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        int s = Integer.parseInt(args[1]);
        EdgeWeightedDigraph G = new EdgeWeightedDigraph(in);
        BellmanFordSPQ sp = new BellmanFordSPQ(G, s);

        for (int v = 0; v < G.V(); v++) {
            if (sp.hasPathTo(v)) {
                StdOut.printf("%d to %d (%5.2f):  ", s, v, sp.distTo(v));
                for (DirectedEdge e : sp.pathTo(v))
                    StdOut.print(e + "   ");
                StdOut.println();
            } else {
                StdOut.printf("%d to %d           no path\n", s, v);
            }
        }
    }
}

/*


* */
