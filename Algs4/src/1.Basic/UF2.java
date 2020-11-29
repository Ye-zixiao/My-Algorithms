import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class UF2 {
    private int[] id;
    private int count;

    public UF2(int N) {
        id = new int[N];
        count = N;
        for (int i = 0; i < N; i++)
            id[i] = i;
    }

    public int count() {
        return count;
    }

    public int find(int pos) {
        while (pos != id[pos]) pos = id[pos];
        return pos;
    }

    public boolean connected(int p, int q) {
        return find(p) == find(q);
    }

    public void union(int p, int q) {
        int pID = find(p);
        int qID = find(q);

        if (pID != qID) {
            id[pID] = qID;
            count--;
        }
    }

    public static void main(String[] args) {
        int[] array = In.readInts(args[0]);
        int cnt = 0, N = array[cnt++];
        UF2 uf2 = new UF2(N);

        while (cnt < array.length) {
            int p = array[cnt++];
            int q = array[cnt++];
            if (uf2.connected(p, q)) continue;
            uf2.union(p, q);
            StdOut.println(p + " " + q);
        }
        StdOut.println(uf2.count() + " connected");
    }
}
