import java.math.BigInteger;
import java.io.*;

class Main {

public static void main(String[] args)
{
    try {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

      while(true) {
        String l1 = br.readLine();
        //System.out.print("l1 " + l1 + "\n");

        int n = Integer.parseInt(l1);
        BigInteger res = new BigInteger("1");
        while(n > 1) {
            BigInteger nb = new BigInteger(Integer.toString(n));
            res = res.multiply(nb);
            n--;
        }

        System.out.print(l1 + "!\n" + res + "\n");
      }
    } catch(Exception e) {}
}
}
