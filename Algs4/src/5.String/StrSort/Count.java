import edu.princeton.cs.algs4.Alphabet;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class Count {
    public static void main(String[]args){
        Alphabet alphabet=new Alphabet(args[0]);
        int R=alphabet.R();
        int[] count=new int[R];

        In in=new In(args[1]);
        String s=in.readAll();
        int N=s.length();
        for(int i=0;i<N;++i)
            if(alphabet.contains(s.charAt(i)))
                count[alphabet.toIndex(s.charAt(i))]++;

        for(int c=0;c<R;c++)
            StdOut.println(alphabet.toChar(c)+" "+count[c]);
    }
}
