import edu.princeton.cs.algs4.StdOut;

public class HeapSort {
    private static void swap(Comparable[] a, int i, int j) {
        Comparable temp = a[j];
        a[j] = a[i];
        a[i] = temp;
    }

    private static boolean less(Comparable lhs, Comparable rhs) {
        return lhs.compareTo(rhs) < 0;
    }

    private static void sink(Comparable[] a, int k, int N) {
        while (2 * k + 1 < N) {
            int j = 2 * k + 1;
            if (j < N - 1 && less(a[j], a[j + 1])) j++;
            if (!less(a[k], a[j])) break;
            swap(a, k, j);
            k = j;
        }
    }

    public static void sort(Comparable[] a) {
        int N = a.length;
        for (int k = N / 2 - 1; k >= 0; --k)
            sink(a, k, N);
        while (N > 0) {
            swap(a, 0, --N);
            sink(a, 0, N);
        }
    }

    public static void show(Comparable[] a) {
        for (Comparable item : a)
            StdOut.println(item);
    }

    public static void main(String[] args) {
        Integer[] array = new Integer[100];
        for (int i = 0; i < array.length; ++i)
            array[i] = array.length - i;
        sort(array);
        show(array);
    }
}