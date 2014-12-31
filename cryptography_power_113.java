import java.math.BigInteger;
import java.io.*;

class cryptography_power {
      static BigInteger one = new BigInteger("1");
      static BigInteger two = new BigInteger("2");
    
public static void main(String[] args)
{
    for(int n = 2 ; n <= 200; n++) {
        BigInteger nb = new BigInteger(Integer.toString(n));
        for (int k = 1; k <= 10000; k++) {
            BigInteger kb = new BigInteger(Integer.toString(k));
            BigInteger p = kb.pow(n);
            /*BigInteger solk = solve(n, p);
            if(!solk.equals(kb))
                System.out.print(k + "^" + n + " = " + p + " | " + solk + "\n");
                */
            System.out.print(n + " " + p + "\n");
            System.err.print(k + "\n");
        }
    }
}
public static BigInteger solve(int n, BigInteger p)
{
    //k^n = p
    //k * k * k * k * ... k = p
    if(n == 1) {
        return p;
    }
    //first do binary search from 1 to more than limit:
    BigInteger max = one;
    //System.out.print("0 max " + max + " " + max.pow(n) + "\n");
    while(max.pow(n).compareTo(p) < 0) {
        max = max.add(max);
        //System.out.print("1 max " + max + " " + max.pow(n) + "\n");
    }
    //System.out.print("2 max " + max + "\n");
    if(max.pow(n).equals(p)) {
        return max;
    }

    //binary search from min to max
    BigInteger min = one;
    while(max.compareTo(min) == 1) {
        BigInteger mid = min.add(max).divide(two);

        int res = mid.pow(n).compareTo(p);
        //System.out.print("max " + max + "\n");
        //System.out.print("min " + min + "\n");
        //System.out.print("mid " + mid + "\n");
        if(res == 0) {
            //System.out.print(mid + "\n");
            return mid;
        }
        else if(res == 1) {
            max = mid;
        }
        else min = mid;

        //System.out.print("new max " + max + "\n");
        //System.out.print("new min " + min + "\n");
    }
    return one;
}

public static void solveFromStdIn()
{
    try {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

      while(true) {
        String l1 = br.readLine();
        String l2 = br.readLine();
        //System.out.print("l1 " + l1 + "\n");
        //System.out.print("l2 " + l2 + "\n");

        int n = Integer.parseInt(l1);
        //BigInteger p = new BigInteger("16");
        BigInteger p = new BigInteger(l2);
        BigInteger k = solve(n, p);
        System.out.print(k + "\n");
      }
    } catch(Exception e) {}
}
}
