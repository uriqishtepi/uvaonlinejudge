import java.math.BigInteger;
import java.util.*;
import java.io.*;

class Main {

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
        BigInteger eleven = new BigInteger("11");
        BigInteger b;
        Scanner sc  = new Scanner(System.in);
        while(true) {
            String str = sc.next();
            if(str == null) break;
            b = new BigInteger(str);
            if(b.equals(BigInteger.ZERO)) break; 

            if(b.mod(eleven).equals(BigInteger.ZERO)) { 
                System.out.print(str +" is a multiple of 11.\n");
            }
            else {
                System.out.print(str +" is not a multiple of 11.\n");
            }

        }
    } catch(Exception e) {}
}

}
