import edu.princeton.cs.algs4.DirectedEdge;
import edu.princeton.cs.algs4.EdgeWeightedDigraph;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

import java.util.Arrays;
import java.util.Stack;

public class BellmanFordSP {
    private double[] distTo;
    private DirectedEdge[] edgeTo;

    //对指定的边进行松弛操作
    private void relax(DirectedEdge e) {
        int w = e.to(), v = e.from();
        if (distTo[w] > distTo[v] + e.weight()) {
            distTo[w] = distTo[v] + e.weight();
            edgeTo[w] = e;
        }
    }

    //算法正常执行的前提是没有负权重环
    public BellmanFordSP(EdgeWeightedDigraph G, int s) {
        distTo = new double[G.V()];
        edgeTo = new DirectedEdge[G.V()];
        Arrays.fill(distTo, Double.POSITIVE_INFINITY);

        //VE次执行松弛操作
        distTo[s] = 0.0;
        for (int v = 0; v < G.V(); ++v)
            for (DirectedEdge e : G.edges())
                relax(e);
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

        BellmanFordSP sp = new BellmanFordSP(G, s);

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
