import java.math.BigInteger;
import java.io.*;

class cryptography_power {
    
public static void main(String[] args)
{
    try {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

      while(true) {
        String l1 = br.readLine();
        String l2 = br.readLine();
        //System.out.print(l1 + "\n");
        //System.out.print(l2 + "\n");

        int n = Integer.parseInt(l1);
        BigInteger one = new BigInteger("1");
        BigInteger two = new BigInteger("2");
        //BigInteger p = new BigInteger("16");
        BigInteger p = new BigInteger(l2);
        //k^n = p
        //k * k * k * k * ... k = p
        if(n == 1) {
            System.out.print(p + "\n");
            continue;
        }
        //binary search from min to max
        BigInteger min = one;
        BigInteger max = p;
        while(max.compareTo(min) == 1) {
            BigInteger mid = min.add(max).divide(two);

            int res = mid.pow(n).compareTo(p);
            //System.out.print("max " + max + "\n");
            //System.out.print("min " + min + "\n");
            //System.out.print("mid " + mid + "\n");
            if(res == 0) {
                System.out.print(mid + "\n");
                break;
            }
            else if(res == 1) {
                max = mid;
            }
            else min = mid;

            //System.out.print("new max " + max + "\n");
            //System.out.print("new min " + min + "\n");
        }
      }
    } catch(Exception e) {}
}
}
