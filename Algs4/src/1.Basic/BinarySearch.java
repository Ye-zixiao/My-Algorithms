import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

import java.util.Arrays;

class BinarySearch {
    public static int rank(int key, int[] a) {
        int lo = 0, hi = a.length - 1, mid;

        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (key < a[mid]) hi = mid - 1;
            else if (key > a[mid]) lo = mid + 1;
            else return mid;
        }
        return -1;
    }

    public static int rrank(int key, int[] a, int low, int high) {
        if (low > high) return -1;

        int mid = low + (high - low) / 2;
        if (key < a[mid])
            return rrank(key, a, low, mid - 1);
        else if (key > a[mid])
            return rrank(key, a, mid + 1, high);
        else
            return mid;
    }

    public static void main(String[] args) {
        int[] array={1,2,3,4,5,6,7,8,9,10};

        StdOut.println("5's position: "+rank(5,array));
        StdOut.println("5's position: "+rrank(5,array,0,array.length-1));
    }
}