## 4.图

### 4.1 无向图

使用邻接表组织的无向图类API：`public class Graph`

- `Graph(int V)`
- `Graph(In in)`
- `int V()`
- `int E()`
- `void addEdge(int v,int w)`
- `Iterable<Integer> adj(int v)`
- `String toString()`

邻接表组织无向图：

所需空间：$E+V$

添加一条边时间复杂度：$1$

遍历指定顶点v所有边时间复杂度：$degree(v)$

检查某一条边的存在性：$degree(v)$

```java
import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class Graph {
    private final int V;
    private int E;
    private Bag<Integer>[] adj;

    public Graph(int V) {
        this.V = V;
        this.E = 0;
        adj = (Bag<Integer>[]) new Bag[V];
        for (int v = 0; v < V; v++)
            adj[v] = new Bag<Integer>();
    }

    public Graph(In in) {
        this(in.readInt());
        int E = in.readInt();
        for (int i = 0; i < E; i++) {
            int v = in.readInt();
            int w = in.readInt();
            addEdge(v, w);
        }
    }

    //图中顶点数
    public int V() {
        return V;
    }

    //图中边数
    public int E() {
        return E;
    }

    //向图中添加一条边
    public void addEdge(int v, int w) {
        adj[v].add(w);
        adj[w].add(v);
        E++;
    }

    //返回顶点v的所有的邻接点
    public Iterable<Integer> adj(int v) {
        return adj[v];
    }

    public String toString() {
        String s = V + " vertices, " + E + "edges\n";
        for (int v = 0; v < V; v++) {
            s += v + ": ";
            for (int w : this.adj(v))
                s += w + " ";
            s += "\n";
        }
        return s;
    }

    //计算指定顶点的入度
    public static int degree(Graph G, int v) {
        int degree = 0;
        for (int w : G.adj(v)) degree++;
        return degree;
    }

    //计算有向图中的最大顶点入度
    public static int maxDegree(Graph G) {
        int max = 0;
        for (int v = 0; v < G.V(); v++)
            if (degree(G, v) > max)
                max = degree(G, v);
        return max;
    }

    //计算有向图中的平均入度
    public static double avgDegree(Graph G) {
        return 2.0 * G.E() / G.V();
    }

    //计算有向图中的自环个数
    public static int numberOfSelfLoops(Graph G) {
        int count = 0;
        for (int v = 0; v < G.V(); v++)
            for (int w : G.adj(v))
                if (v == w) count++;//有一点连到自己的顶点存在
        return count / 2;
    }
}
```

邻接表如图所示：

<img src="image/2020-11-21 095630.png" alt="2020-11-21 095630" style="zoom:67%;" />



#### 4.1.1  深度优先搜索

深度优先搜索也可以称为深度优先遍历，因为它实际上是通过对图中的每一个与指定顶点连通的顶点进行遍历的方式获知图中的哪些顶点与之相连。其步骤很简单：

1. 将起点标记为已访问；
2. 然后递归方法问它的所有没有被标记过的邻居顶点。

深度优先搜索的原理是通过栈（递归的本质就是栈）来实现对图中顶点的完全遍历

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DepthFirstSearch {
    private boolean[] marked;
    private int count;

    //实现递归实现的深度优先搜索
    private void dfs(Graph G, int v) {
        marked[v] = true;
        count++;
        for (int w : G.adj(v))
            if (!marked[w]) dfs(G, w);
    }

    //使用栈实现的深度优先搜索
    private void dfs1(Graph G, int v) {
        Stack<Integer> stack = new Stack<Integer>();
        marked[v] = true;
        stack.push(v);
        count++;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int vertex : G.adj(t)) {
                if (!marked[vertex]) {
                    marked[vertex] = true;
                    stack.push(vertex);
                    count++;
                }
            }
        }

    }

    public DepthFirstSearch(Graph G, int s) {
        marked = new boolean[G.V()];
        dfs1(G, s);
    }

    public boolean marked(int w) {
        return marked[w];
    }

    public int count() {
        return count;
    }

    public static void main(String[] args) {
        Graph G = new Graph(new In(args[0]));
        int s = Integer.parseInt(args[1]);
        DepthFirstSearch search = new DepthFirstSearch(G, s);

        StdOut.println("start vertex(" + s + ") connects: ");
        for (int v = 0; v < G.V(); v++)
            if (search.marked(v))
                StdOut.print(v + " ");
        StdOut.println();
        StdOut.println("connected count: " + search.count());
    }
}
```

书中的图很好的展示了DFS所谓的“深度”是为何意，因为这孩子比较皮，老喜欢跑远的跑到更深的地方😂

<img src="image/2020-11-18 105725.png" alt="2020-11-18 105725" style="zoom: 67%;" />



##### 4.1.1.1   使用DFS路径搜索

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DepthFirstPaths {
    private boolean[] marked;
    private int[] edgeTo;//存储递归过程中当前点的前一个点的索引
    private final int s;

    //使用栈实现的深度优先搜索路径方法
    private void dfs(Graph G, int s) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(s);
        marked[s] = true;
        edgeTo[s] = s;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int ver : G.adj(t)) {
                if (!marked[ver]) {
                    stack.push(ver);
                    marked[ver] = true;
                    edgeTo[ver] = t;
                }
            }
        }
    }

    //使用递归实现的深度优先搜索路径方法
    private void dfs1(Graph G, int s) {
        marked[s] = true;
        for (int w : G.adj(s)) {
            if (!marked[w]) {
                edgeTo[w] = s;
                dfs1(G, w);
            }
        }
    }

    public DepthFirstPaths(Graph G, int s) {
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        this.s = s;
//        edgeTo[s]=s;
//        dfs1(G,s);
        dfs(G, s);
    }

    public boolean hasPathTo(int v) {
        return marked[v];
    }

    //返回从s->v的路径
    public Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v)) return null;

        Stack<Integer> stack = new Stack<Integer>();
        for (int x = v; x != s; x = edgeTo[x])
            stack.push(x);
        stack.push(s);
        return stack;
    }

    public static void main(String[] args) {
        Graph graph = new Graph(new In(args[0]));
        int s = Integer.parseInt(args[1]);
        DepthFirstPaths paths = new DepthFirstPaths(graph, s);

        for (int v = 0; v < graph.V(); ++v) {
            StdOut.print(s + " to " + v + ": ");
            if (paths.hasPathTo(v))
                for (int x : paths.pathTo(v))
                    if (x == s) StdOut.print(x);
                    else StdOut.print("-" + x);
            StdOut.println();
        }
    }
}
```



##### 4.1.1.2  使用DFS寻找连通分量

虽然理论上使用DFS实现图中连通分量的寻找与V+E成正比，看上去和union-find算法应该相近，但是由于其在使用前必须对图进行构造，因此它的性能实际上没有比union-find并查集算法更好。

检测所需时间与$V+E$成正比。

```java
import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class CC {
    private boolean[] marked;
    private int[] id;
    private int count;

    //使用栈实现的DFS
    private void dfs(Graph G, int v) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(v);
        marked[v] = true;
        id[v] = count;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int w : G.adj(t)) {
                if (!marked[w]) {
                    stack.push(w);
                    marked[w] = true;
                    id[w] = count;
                }
            }
        }
    }

    //使用递归实现的DFS
    private void dfs1(Graph graph, int v) {
        marked[v] = true;
        id[v] = count;
        for (int w : graph.adj(v))
            if (!marked[w])
                dfs(graph, v);
    }

    public CC(Graph G) {
        marked = new boolean[G.V()];
        id = new int[G.V()];
        /* 将同一个连通分量下的顶点全部标记为同一个id，
           若已经标记过就不再执行dfs，而是遍历剩下的顶
           点让它们归入到新的连通分量组之中 */
        for (int s = 0; s < G.V(); s++)
            if (!marked[s]) {
                dfs(G, s);
                count++;
            }
    }

    public boolean connected(int v, int w) {
        return id[v] == id[w];
    }

    public int id(int v) {
        return id[v];
    }

    public int count() {
        return count;
    }

    public static void main(String[] args) {
        Graph graph = new Graph(new In(args[0]));
        CC cc = new CC(graph);

        int M = cc.count();
        StdOut.println(graph.V() + " vertexes");
        StdOut.println(M + " components");

        Bag<Integer>[] components = (Bag<Integer>[]) new Bag[M];
        for (int i = 0; i < M; ++i)
            components[i] = new Bag<Integer>();
        for (int i = 0; i < graph.V(); i++)
            components[cc.id[i]].add(i);

        for (int i = 0; i < M; i++) {
            for (int v : components[i])
                StdOut.print(v + " ");
            StdOut.println();
        }
    }
}
```

图中有3个连通分量：

<img src="image/2020-11-18 115733.png" alt="2020-11-18 115733" style="zoom: 67%;" />

##### 4.1.1.3  使用DFS检测环

我们可以使用DFS判断一个从一个起点到终点是否有环：假设在DFS遍历的过程中遇到了一个已经标记过的顶点，这就说明从起点到这个顶点至少有多条路径到终点，即有环。

```java
public class Cycle {
    private boolean[] marked;
    private boolean hasCycle;

    private void dfs(Graph G, int v, int u) {
        marked[v] = true;
        for (int w : G.adj(v))
            if (!marked[w])
                dfs(G, w, v);
            else if (w != u)
                hasCycle = true;
    }

    public Cycle(Graph G) {
        marked = new boolean[G.V()];
        for (int s = 0; s < G.V(); ++s)
            if (!marked[s])
                dfs(G, s, s);
    }

    public boolean hasCycle() {
        return hasCycle;
    }
}
```





#### 4.1.2  广度优先搜索

广度优先搜索BFS与深度优先搜索DFS相反，它是通过队列来实现对图中顶点的完全遍历，这种方法的好处在于它在顶点遍历的过程中实际上用到了贪心的思想，总是会先去找它（顶点）身边最近的那几个顶点进行遍历。其主要步骤如下：

1. 从队列中弹出下一个顶点并标记（其实也可以在入队的时候标记）
2. 然后将与v相邻的所有未被标记的顶点加入到队列之中

##### 4.1.2.1  使用BFS路径搜索

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class BreadthFirstPaths {
    private boolean[] marked;
    private int[] edgeTo;//存储递归过程中当前点的前一个点的索引
    private final int s;

    private void bfs(Graph G, int s) {
        Queue<Integer> queue = new Queue<Integer>();
        queue.enqueue(s);
        edgeTo[s] = s;
        marked[s] = true;

        while (!queue.isEmpty()) {
            int t = queue.dequeue();
            for (int w : G.adj(t))
                if (!marked[w]) {
                    queue.enqueue(w);
                    edgeTo[w] = t;
                    marked[w] = true;
                }
        }
    }

    public BreadthFirstPaths(Graph G, int s) {
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        this.s = s;
        bfs(G, s);
    }

    public boolean hasPathTo(int v) {
        return marked[v];
    }

    //返回从s->v的路径
    public Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v)) return null;

        Stack<Integer> stack = new Stack<Integer>();
        for (int x = v; x != s; x = edgeTo[x])
            stack.push(x);
        stack.push(s);
        return stack;
    }

    public static void main(String[] args) {
        Graph graph = new Graph(new In(args[0]));
        int s = Integer.parseInt(args[1]);
        DepthFirstPaths paths = new DepthFirstPaths(graph, s);

        for (int v = 0; v < graph.V(); ++v) {
            StdOut.print(s + " to " + v + ": ");
            if (paths.hasPathTo(v))
                for (int x : paths.pathTo(v))
                    if (x == s) StdOut.print(x);
                    else StdOut.print("-" + x);
            StdOut.println();
        }
    }
}
```

书中的图很好的展示了BFS所谓的“广度”是为何意，因为这孩子比较乖有比较谨慎，起初总是在近的地方玩，之后熟悉了才到远的地方玩😋

<img src="image/2020-11-18 105748.png" alt="2020-11-18 105748" style="zoom:67%;" />



### 4.2 有向图

有向图API：`public class Digraph`

- `Drigraph(int V)`
- `Digraph(In in)`
- `int V()`
- `int E()`
- `void addEdge(int v,int w)`
- `Iterable<Integer> adj(int v)`
- `Digraph reverse()`
- `String toString()`

```java
import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class Digraph {
    private final int V;
    private int E;
    private Bag<Integer>[] adj;

    public Digraph(int V) {
        this.V = V;
        this.E = 0;
        adj = (Bag<Integer>[]) new Bag[V];
        for (int v = 0; v < V; v++)
            adj[v] = new Bag<Integer>();
    }

    public Digraph(In in) {
        this(in.readInt());
        int E = in.readInt();
        for (int i = 0; i < E; i++) {
            int v = in.readInt();
            int w = in.readInt();
            addEdge(v, w);
        }
    }

    public int V() {
        return V;
    }

    public int E() {
        return E;
    }

    public void addEdge(int v, int w) {
        adj[v].add(w);
        E++;
    }

    //返回指定点的指出点集合
    public Iterable<Integer> adj(int v) {
        return adj[v];
    }

    //返回一个反向图
    public Digraph reverse() {
        Digraph R = new Digraph(V);
        for (int v = 0; v < V; v++)
            for (int w : adj[v])
                R.addEdge(w, v);
        return R;
    }

    public String toString() {
        String s = V + " vertices, " + E + " deges\n";
        for (int v = 0; v < V; v++) {
            s += v + ": ";
            for (int w : this.adj(v))
                s += w + " ";
            s += "\n";
        }
        return s;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        StdOut.println(args[0]);

        StdOut.println(digraph);
    }
}
```



#### 4.2.1 可达性问题

##### 4.2.1.1   使用DFS解决可达性问题

```java
import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DirectedDFS {
    private boolean[] marked;

    //使用递归实现的深度优先搜索方法
    private void dfs(Digraph G, int v) {
        marked[v] = true;
        for (int w : G.adj(v))
            if (!marked[w]) dfs(G, w);
    }

    //使用栈实现的深度优先搜索方法
    private void dfs1(Digraph G, int v) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(v);
        marked[v] = true;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int w : G.adj(t)) {
                if (!marked[w]) {
                    stack.push(w);
                    marked[w] = true;
                }
            }
        }
    }

    public boolean marked(int v) {
        return marked[v];
    }

    public DirectedDFS(Digraph G, int s) {
        marked = new boolean[G.V()];
        dfs1(G, s);
    }

    public DirectedDFS(Digraph G, Iterable<Integer> sources) {
        marked = new boolean[G.V()];
        for (int s : sources)
            if (!marked[s]) dfs1(G, s);
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));

        Bag<Integer> sources = new Bag<Integer>();
        for (int i = 1; i < args.length; ++i)
            sources.add(Integer.parseInt(args[i]));

        DirectedDFS reachable = new DirectedDFS(digraph, sources);
        for (int v = 0; v < digraph.V(); v++)
            if (reachable.marked(v)) StdOut.print(v + " ");
        StdOut.println();
    }
}
```



##### 4.2.1.2  使用DFS路径搜索

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DepthFirstDirectedPaths {
    private boolean[] marked;
    private int[] edgeTo;
    private final int s;

    //使用递归实现的深度优先搜索方法
    private void dfs(Digraph G, int s) {
        marked[s] = true;
        for (int w : G.adj(s))
            if (!marked[w]) {
                edgeTo[w] = s;
                dfs(G, w);
            }
    }

    //使用栈实现的深度优先搜索方法
    private void dfs1(Digraph G, int s) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(s);
        edgeTo[s] = s;
        marked[s] = true;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int w : G.adj(t)) {
                if (!marked[w]) {
                    stack.push(w);
                    edgeTo[w] = t;
                    marked[w] = true;
                }
            }
        }
    }

    public DepthFirstDirectedPaths(Digraph G, int s) {
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        this.s = s;
        dfs1(G, s);
    }

    public boolean hasPathTo(int v) {
        return marked[v];
    }

    //返回从起点s到指定点v的路径容器引用
    public Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v)) return null;

        Stack<Integer> stack = new Stack<Integer>();
        for (int p = v; p != s; p = edgeTo[p])
            stack.push(p);
        stack.push(s);
        return stack;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        int s = Integer.parseInt(args[1]);
        DepthFirstDirectedPaths paths = new DepthFirstDirectedPaths(digraph, s);

        for (int v = 0; v < digraph.V(); ++v) {
            StdOut.print(s + " to " + v + ": ");
            if (paths.hasPathTo(v))
                for (int x : paths.pathTo(v))
                    if (x == s) StdOut.print(x);
                    else StdOut.print("-" + x);
            StdOut.println();
        }
    }
}
```



##### 4.2.1.3  使用BFS路径搜索

```java
import edu.princeton.cs.algs4.*;

public class BreadFirstDirectedPaths {
    private boolean[] marked;
    private int[] parents;
    private final int s;

    //广度优先搜索路径方法
    private void bfs(Digraph G, int s) {
        Queue<Integer> queue = new Queue<Integer>();
        queue.enqueue(s);
        marked[s] = true;
        parents[s] = s;

        while (!queue.isEmpty()) {
            int t = queue.dequeue();
            for (int w : G.adj(t)) {
                if (!marked[w]) {
                    queue.enqueue(w);
                    marked[w] = true;
                    parents[w] = t;
                }
            }
        }
    }

    public BreadFirstDirectedPaths(Digraph G, int s) {
        marked = new boolean[G.V()];
        parents = new int[G.V()];
        this.s = s;
        bfs(G, s);
    }

    public boolean hasPathTo(int v) {
        return marked[v];
    }

    //返回从起点s到指定点v的路径容器引用
    public Iterable<Integer> pathTo(int v) {
        if (!hasPathTo(v)) return null;

        Stack<Integer> stack = new Stack<Integer>();
        for (int p = v; p != s; p = parents[p])
            stack.push(p);
        stack.push(s);
        return stack;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        int s = Integer.parseInt(args[1]);
        BreadFirstDirectedPaths paths = new BreadFirstDirectedPaths(digraph, s);

        for (int v = 0; v < digraph.V(); ++v) {
            StdOut.print(s + " to " + v + ": ");
            if (paths.hasPathTo(v))
                for (int x : paths.pathTo(v))
                    if (x == s) StdOut.print(x);
                    else StdOut.print("-" + x);
            StdOut.println();
        }
    }
}
```





#### 4.2.2  拓扑排序

拓扑排序指的是给定一幅有向图，将所有顶点进行排序，使得所有的有向边均从排在前面的元素指向排在后面的元素。需要注意的是，拓扑排序只能在有向无环图上进行，所以我们在拓扑排序之前就是先要判定这个有向图是否有环存在。

<img src="image/2020-11-21 095424.png" alt="2020-11-21 095424" style="zoom:80%;" />

下面的排序顺序就是按照拓扑排序而行。

<img src="image/2020-11-21 095409.png" alt="2020-11-21 095409" style="zoom:67%;" />



##### 4.2.2.1  有向环检测

其判断的方法就是使用深度优先搜索DFS算法遍历整个图中的结点，若在遍历到顶点v时发现有一个顶点w已经在栈中了，则说明本来就有一条路径w->v，现在又发现一条路径v->w，即有环。

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DirectedCycle {
    private boolean[] marked;
    private int[] edgeTo;
    private Stack<Integer> cycle;
    private boolean[] onStack;

    private void dfs(Digraph G, int v) {
        onStack[v] = true;
        marked[v] = true;
        for (int w : G.adj(v)) {
            //若之前已经找到一个环了，则既然已经判定了有环就没有必要再找了
            if (this.hasCycle()) return;
            else if (!marked[w]) {
                edgeTo[w] = v;
                dfs(G, w);
            }
            /* 若w在栈中，说明有个v->w有个环，那么我们就可以沿着edgeTo数组向回找
                以将这个环中的所有结点(v->w->v)加入到cycle中 */
            else if (onStack[w]) {
                cycle = new Stack<Integer>();
                for (int p = v; p != w; p = edgeTo[p])
                    cycle.push(p);
                cycle.push(w);
                cycle.push(v);
            }
        }
        onStack[v] = false;
    }

    public DirectedCycle(Digraph G) {
        marked = new boolean[G.V()];
        edgeTo = new int[G.V()];
        onStack = new boolean[G.V()];
        for (int v = 0; v < G.V(); ++v)
            if (!marked[v]) dfs1(G, v);
    }

    public boolean hasCycle() {
        return cycle != null;
    }

    public Iterable<Integer> cycle() {
        return cycle;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        DirectedCycle cycle = new DirectedCycle(digraph);

        if (cycle.hasCycle()) {
            StdOut.println("This Digragh has cycle:");
            for (int v : cycle.cycle()) {
                StdOut.print(v + " ");
            }
            StdOut.println();
        }
    }
}
```

当当前顶点v发现自己身边有一个顶点w已经存放在栈中的时候，这就说明v有路径到w，而且w也有另一条路径到v：

<img src="image/2020-11-21 095747.png" alt="2020-11-21 095747" style="zoom:67%;" />



##### 4.2.2.2  深度优先排序

实际上由于深度优先搜索DFS算法总是会从起点一个劲的向自己深层次所指向的顶点进行搜索，因此在其遍历的过程中有向边的指出顶点是先于有向边的指入顶点而得到遍历。因此我们按照这一规则将先得到遍历的顶点最后放入到容器中，而最根端的顶点先放入到容器之中，那么我们容器中的元素的顺序就是典型的拓扑排序！（而实际中的拓扑排序也正是采用了这种方法来解决）。

排序时间与$V+E$成正比。

```go
//伪代码
func dfs(G,v):
	mark(v)
	for every adjacency vertex of v:
		dfs(G,adj)
	put v to stack
end
```

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DepthFirstOrder {
    private boolean[] marked;
    private Queue<Integer> pre;
    private Queue<Integer> post;
    private Stack<Integer> reversePost;

    private void dfs(Digraph G, int v) {
        pre.enqueue(v);//前序遍历

        marked[v] = true;
        for (int w : G.adj(v))
            if (!marked[w]) dfs(G, w);

        post.enqueue(v);//后序遍历
        reversePost.push(v);//逆后序遍历，得到的正是深度优先排序
    }

    public DepthFirstOrder(Digraph G) {
        pre = new Queue<Integer>();
        post = new Queue<Integer>();
        reversePost = new Stack<Integer>();
        marked = new boolean[G.V()];
        for (int v = 0; v < G.V(); ++v)
            if (!marked[v]) dfs(G, v);
    }

    //返回前序遍历
    public Iterable<Integer> pre() {
        return pre;
    }

    //返回后序遍历
    public Iterable<Integer> post() {
        return post;
    }

    //返回逆后序遍历
    public Iterable<Integer> reversePost() {
        return reversePost;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        DepthFirstOrder order = new DepthFirstOrder(digraph);

        for (int v : order.reversePost())
            StdOut.print(v + " ");
        StdOut.println();
    }
}
```

前序、后序和逆后序遍历的不同之处：

<img src="image/2020-11-21 101532.png" alt="2020-11-21 101532" style="zoom:80%;" />



##### 4.2.2.3  拓扑排序

一幅有向无环图的拓扑排序即为所有顶点的逆后序排列。

```java
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
```

图示：

<img src="image/2020-11-21 103035.png" alt="2020-11-21 103035" style="zoom:67%;" />



#### 4.2.3 有向图中的强连通性

若有向图中的两个顶点v、w，它们互相可达，则我们称它们为强连通。若在一个顶点集中每一个顶点相互强连通，且这个顶点集是上述条件成立的最大顶点集，则我们称这样的顶点集为强连通分量。更进一步，当有向图中只有一个强连通分量的时候，我们称这样的图为强连通图。

对于有向图中的强连通分量的判断，我们只需要记住Kosaraju算法的结论即可：**使用深度优先搜索算法查找①给定图$G$的反向图$G^R$，根据②由此得到的所有顶点的逆后序③再用深度优先搜索处理有向图$G$，④其构造函数中的每一次递归调用所标记的顶点都在同一个强连通分量之中。**

不过我们也可以细想这是为什么？首先，对给定图$G$的反向图$G^R$计算的逆后序，其原图中的某一个强连通分量中的最深层次的总是会被放置到前面（这里仅仅相对于这个强连通分量而言），因为反向图中的原本处于图中深层次位置的顶点变化了根部位置的顶点。若按照这个顺序遍历，则从处于自己强连通分量之中的深层次顶点开始DFS，则当显然会遍历到属于同一连通分量之中的顶点，但是对处于别的强连通分量之中的顶点它是无法遍历到的。因此有了上面④的结果。

<img src="image/QQ图片20201121121106 (2).jpg" alt="QQ图片20201121121106 (2)" style="zoom: 50%;" />

```java
import edu.princeton.cs.algs4.Bag;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class KosarajuCC {
    private boolean[] marked;
    private int[] id;
    private int count;

    //使用递归实现的深度优先遍历算法，以将同一个强连通分量中的顶点进行标识
    private void dfs(Digraph G, int v) {
        marked[v] = true;
        id[v] = count;
        for (int w : G.adj(v))
            if (!marked[w])
                dfs(G, w);
    }

    //使用栈实现的深度优先遍历算法，以将同一个强连通分量中的顶点进行标识
    private void dfs1(Digraph G, int v) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(v);
        marked[v] = true;
        id[v] = count;

        while (!stack.isEmpty()) {
            int t = stack.pop();
            for (int w : G.adj(t)) {
                if (!marked[w]) {
                    stack.push(w);
                    marked[w] = true;
                    id[w] = count;
                }
            }
        }
    }

    public KosarajuCC(Digraph G) {
        marked = new boolean[G.V()];
        id = new int[G.V()];
        DepthFirstOrder order = new DepthFirstOrder(G.reverse());
        for (int s : order.reversePost())
            if (!marked[s]) {
                dfs1(G, s);
                count++;
            }
    }

    public boolean stronglyConnected(int v, int w) {
        return id[v] == id[w];
    }

    public int id(int v) {
        return id[v];
    }

    public int count() {
        return count;
    }

    public static void main(String[] args) {
        Digraph digraph = new Digraph(new In(args[0]));
        KosarajuCC cc = new KosarajuCC(digraph);

        int M = cc.count();
        StdOut.println(digraph.V() + " vertexes, " + M +
                " strongly connected components:");

        Bag<Integer>[] bags = new Bag[M];
        for (int i = 0; i < M; ++i)
            bags[i] = new Bag<Integer>();
        for (int i = 0; i < digraph.V(); ++i)
            bags[cc.id(i)].add(i);

        for (int i = 0; i < M; ++i) {
            for (int v : bags[i])
                StdOut.print(v + " ");
            StdOut.println();
        }
    }
}
```

