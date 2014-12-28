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
        //BigInteger p = new BigInteger("16");
        BigInteger p = new BigInteger(l2);
        BigInteger k;
        //k^n = p
        //k * k * k * k * ... k = p
        if(n == 1) {
            System.out.print(p + "\n");
            continue;
        }
        k = one;
        while(k.compareTo(p) == -1) {
            //System.out.print("k " + k + "\n");
            if(k.pow(n).equals(p)) {
                System.out.print(k + "\n");
                break;
            }
            k = k.add(one);
        }
      }
    } catch(Exception e) {}
}
}
