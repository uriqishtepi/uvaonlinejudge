import java.math.BigInteger;
import java.io.*;

class ones {

//return true if b is multiple of a
//quotient = divide b by a
//if (b == quotient * a) then return true
//else return false
static boolean isMult(BigInteger a, BigInteger b)
{
    BigInteger quotient = b.divide(a);
    if(a.multiply(quotient).equals(b)) 
        return true;
    else
        return false;
}

public static void main(String[] args) {
    try {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        while(true) {
            String l1 = br.readLine().trim();
            if(l1 == null) break;
            if(l1.equals("0")) continue; 

            BigInteger b1 = new BigInteger(l1);
            BigInteger two = new BigInteger("2");
            BigInteger five = new BigInteger("5");
            if(isMult(two, b1) ) continue;
            if(isMult(five, b1) ) continue;

            BigInteger ten = new BigInteger("10");
            BigInteger one = new BigInteger("1");
            BigInteger multiple = one;
            int count = 0;
            while(count++ < 10000) {
                if(isMult(b1, multiple)) break;       
                multiple = multiple.multiply(ten).add(one);
            }
            //System.out.print("num " + b1 + " count " + count + " multiple " + multiple +" \n");
            System.out.print(count +"\n");
        }
    } catch(Exception e) {}
}

}
