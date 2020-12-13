import edu.princeton.cs.algs4.Alphabet;
import edu.princeton.cs.algs4.StdOut;

public class Test {
    public static void main(String[]args) {
        for(int i=0;i<256;++i){
            char c= (char) i;
            StdOut.print(new String(String.valueOf(c)) +' ');}
        StdOut.println();
    }
}
