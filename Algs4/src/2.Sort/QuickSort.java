import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import jdk.nashorn.internal.ir.LiteralNode;

public class QuickSort {

    private static boolean less(Comparable lhs, Comparable rhs) {
        return lhs.compareTo(rhs) < 0;
    }

    private static void swap(Comparable[] a, int i, int j) {
        Comparable temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    private static void show(Comparable[] a) {
        for (int i = 0; i < a.length; ++i)
            StdOut.println(a[i]+" ");StdOut.println();
    }

    public static boolean isSorted(Comparable[] a) {
        for (int i = 1; i < a.length; i++)
            if (less(a[i], a[i - 1]))
                return false;
        return true;
    }

    //3取样
    private static int ThreeMid(Comparable[] a, int low, int high) {
        Integer[] temp = {low, low + (high - low) / 2, high};
        for (int i = 1, j; i < temp.length; ++i) {
            Integer t = temp[i];
            for (j = i; j > 0 && less(a[j], a[j - 1]); --j)
                temp[j] = temp[j - 1];
            temp[j] = t;
        }
        return temp[1];
    }

    public static void qsort(Comparable[] a, int low, int high) {
        if (high - low <= 0) return;

        swap(a, low, ThreeMid(a, low, high));//用到了3取样方法
        int lt = low, i = low + 1, gt = high;
        Comparable v = a[low];

        while (i <= gt) {
            int cmp = a[i].compareTo(v);
            if (cmp < 0)
                swap(a, lt++, i++);
            else if (cmp > 0)
                swap(a, gt--, i);
            else
                i++;
        }
        qsort(a, low, lt - 1);
        qsort(a, gt + 1, high);
    }

    public static void sort(Comparable[] a) {
        qsort(a, 0, a.length - 1);
    }

    public static void main(String[] args) {
        Integer[] array=new Integer[100];
        for(int i=0;i< array.length;++i)
            array[i]= array.length-i;

        sort(array);
        show(array);
    }
}
