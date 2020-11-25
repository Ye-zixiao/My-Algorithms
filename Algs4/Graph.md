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

##### 4.2.3.1  Kosaraju算法

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



##### 4.2.3.2  有向图中顶点对的可达性问题

在无向图中问顶点v是否可到达顶点w，其本质就是连通性问题。但是在有向图中，这个问题并非如此，只有两个相互可达才能被称为强连通，所以这本质上是两个问题。解决能够随机查询点v到点w是否可达，可以通过对每一个顶点执行深度优先搜索算法，并把DFS结果存放在一个容器之中（在这里使用到一个存放DirectedDFS类对象的引用数组）。

```java
public class TransitiveClosure {
    private DirectedDFS[] all;
    
    TransitiveClosure(Digraph G){
        all=new DirectedDFS[G.V()];
        for(int v=0;v<G.V();++v)
            all[v]=new DirectedDFS(G,v);
    }
    
    boolean reachable(int v,int w){
        return all[v].marked(w);
    }
}
```



### 4.3 最小生成树

图的生成图指的是它的一棵含有其所有顶点的无环连通子图。一幅加权无向图的最小生成树(MST)是它的一棵权值（树中所有边的权值之和）最小的生成树。

切分定理：在一幅加权图中，给定任意的切分，它的横截边中权重最小者必然是属于图的最小生成树。按照这一规则，我们就有了最小生成树的贪心算法：将图中初始状态下的所有边标记为灰色，找到其中一种切分，它产生的横截边均不为黑色。将它的权重最小横截边标记为黑色。反复，知道标记V-1条黑色边为止。如下图：

<img src="image/2020-11-22 113517.png" alt="2020-11-22 113517" style="zoom:67%;" />

#### 4.3.1  加权无向图的表示

我们所有的最小生成树计算都是基于加权无向图这一数据结构，其与无向图数据结构最大的区别在于它使用类对象Edge来代替了原始临界表中的原始数据类型int。

<img src="image/2020-11-22 112013.png" alt="2020-11-22 112013" style="zoom:67%;" />

```java
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
```



#### 4.3.2  Prim算法

Prim算法的核心思想就是：在最小生成树MST生长的过程中，每一次迭代总是将不在MST中但与之连接的顶点且权重最小的边加入到MST之中。

##### 4.3.2.1  Prim算法延时实现

其具体的做法就是：

1. 先将图中的某一点加入到MST之中（通过marked标记），并将其所有的邻边加入到最小优先队列MinPQ中；
2. 接着MinPQ从中取出最小连接边，若对端的顶点没有被标记，然后紧接着对对端的顶点执行步骤1，将其所有有效邻边加入到MinPQ；
3. 实际上MST不仅维护着一群顶点（通过marked布尔类型数组），而且还维护着一群边（通过一个容器）。

这样我们就可以不断地重复1-2步骤，就可以生成最小生成树MST了，具体如下图所示：

<img src="image/2020-11-23 101251.png" alt="2020-11-23 101251" style="zoom:67%;" />

时间复杂度：$ElogV$

空间复杂度：$V$

```java
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
```



##### 4.3.2.2  Prim算法即时实现

Prim算法延时实现和及时实现的区别在于：

- Prim算法的延时实现的关键在于让最小优先队列MinPQ维护着MST中点的所有未加入MST邻边（这些邻边中本身还包括无效的边，即它们的两端顶点已经加入到MST之中），然后在每一次迭代中取出权值最小的有效邻边和那个对端点加入到MST之中；
- 而Prim算法的及时实现的关键在于让最小索引优先队列IndexMinPQ维护着未加入到MST的剩余顶点到MST的最小权重距离，这些权重距离（有些是多条边权重的叠加，有些是就是直接的邻边的权重）。然后我们在每一次迭代中取出连接到MST代价最小的未加入点，让该点加入到MST之中，随便添加那条连接边。

所以我们可以看到，延时实现的关键在于维护**未加入MST的邻边**，而问题在于邻边可能有些是无效的；而及时实现的关键在于维护**未加入MST的所有点以及它们到MST的距离**，这些距离对点而言都是唯一的，当这个点到MST距离最小时一定这个距离指的就是连接两者的那条邻边。

![2020-11-24 105338](image/2020-11-24 105338.png)

每次将一个点加入到MST之后，就需要利用现有的信息更新所有为加入到MST顶点到MST权重距离。



最小生成树生成时间复杂度：$ElogV$

空间复杂度：$V$

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.IndexMinPQ;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdOut;

public class PrimMST {
    private Edge[] edgeTo;
    private double[] distTo;
    private boolean[] marked;
    private IndexMinPQ<Double> pq;

    /* 访问结点v的所有邻边，若该边有效且它的权重比现有w到最小生成树的权
        重还要低，则将其替换为最新边edgeTo[w]=...和权重值distTo[w]=... */
    private void visit(EdgeWeightedGraph G, int v) {
        marked[v] = true;
        for (Edge e : G.adj(v)) {
            /* 每加入一个顶点到MST之后，就遍历它的所有临近顶点，
	            更新加入到MST的权重路径信息 */
            int w = e.other(v);
            if (!marked[w] && e.weight() < distTo[w]) {
                edgeTo[w] = e;
                distTo[w] = e.weight();
                if (pq.contains(w)) pq.change(w, distTo[w]);
                else pq.insert(w, distTo[w]);
            }
        }
    }

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
```

过程图示：

<img src="image/2020-11-24 112736.png" alt="2020-11-24 112736" style="zoom:50%;" />



#### 4.3.3 Kruskal算法

算法原理：按照权重顺序（从小到大）处理它们，将边加入到最小生成树MST之中，加入到的边不会形成环，直到树中不会含有V-1条边为止。即由一片森林变成一棵树。

时间复杂度：$ElogE$

空间复杂度：$E$

```java
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
        UF uf = new UF(G.V());//并查集用来检测换的存在性
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
```

各个最小生成树算法总结（假设为V个顶点E条边的连通图，在最坏情况下）：

| 算法           | 空间复杂度 | 时间复杂度 |
| -------------- | ---------- | ---------- |
| 延时的Prim算法 | $E$        | $ElogE$    |
| 即时的Prim算法 | $V$        | $ElogV$    |
| Kruskal算法    | $E$        | $ElogE$    |

其中即时的Prim算法是这里面最好的。

### 4.4 最短路径

加权有向图的数据结构表示:`public EdgeWeightDigraph`

- `EdgeWeightDigraph(int V)`
- `EdgeWeightDigraph(In in)`
- `void addEdge(DirectedEdge edge)`
- `int V()`
- `int E()`
- `Iterable<DirectedEdge> adj(int v)`
- `Iterable<DirectedEdge> edges()`

```java
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
```



#### 4.4.1  Dijkstra算法

Dijkstra算法的核心思想其实与Prim算法类似，**Prim的核心在于每一次迭代的过程中添加离MST最近的未加入MST顶点，而Dijkstra算法的核心在于每次迭代的过程中添加离起点最近的未加入SPT的顶点**（其中MST指的是最小生成树，SPT指的是最短路径树）。

在Prim算法中，我们最重要的操作就是`visit()`：我们每次向最小生成树MST加入一个顶点之后，就会通过它的所有邻边去更新剩余未加入顶点到MST的距离信息distTo[]和edgeTo[]（distTo[]也必然是在索引最小优先队列IndexMinPQ之中）。完成这些更新操作之后，Prim算法就会从队列中取出下一个最小顶点重复上面的操作。这里的`visit()`操作的本质就是①加入一个顶点和②更新剩余的顶点信息

同样的，在Dijkstra算法中也有类似的操作，可以说基本上与Prim算法类似，即书中所谓的放松`relax()`操作：我们每次向最短路径树加入一个顶点之后，就会通过它的所有邻边去更新剩余未加入顶点到起点的距离信息distTo[]和指入边edgeTo[]（distTo[]同样的也是在索引最小优先队列IndexMinPQ之中）。完成这些操作之后，Dijkstra算法就会从队列中取出下一个最小顶点重复上面的操作。因此，我们可以认为Dijkstra算法其实本质上和Prim算法有很多相似的地方🧐。下面演示的是顶点v加入到SPT之后对distTo[w]和edgeTo[w]的`relax()`更新操作：

<img src="image/2020-11-25 120429.png" alt="2020-11-25 120429" style="zoom: 80%;" />

```java
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.IndexMinPQ;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

public class DijkstraSP {
    private DirectedEdge[] edgeTo;
    private double[] distTo;
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
```

