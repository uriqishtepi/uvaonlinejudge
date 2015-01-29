import java.math.BigInteger;
import java.io.*;

class product {
public static void main(String[] args) {
    try { 
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while(true) {
            String l1 = br.readLine().trim();
            String l2 = br.readLine().trim();
            if(l1 == null || l2 == null) 
                break;
            if(l1.equals("0") || l2.equals("0")) {
                System.out.print("0\n");
                continue;
            }
            BigInteger b1 = new BigInteger(l1);
            BigInteger b2 = new BigInteger(l2);
            System.out.print(b1.multiply(b2) + "\n");
        }
    } catch(Exception e) {}
}

}

