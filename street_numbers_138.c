#include<stdio.h>
#include<math.h>


/* pass the own house as parameter i */
int slowtest(long long int i) 
{
    long long int sum = ((1 + i) * i) /2;
    long long int d = 2 *sum + i*i - i;
    
    /* bin srch for L:
       L^2 + L -i^2 +i = 2*sum
       L > i
       so L ^2 + L = L*(L+1)= 2*sum +i^2 - i = d
       also L = (-b + sqrt(b - 4ac) ) / 2
    */

    long long int min = i;
    long long int max = sum;
    static long long int mid = 5;
    while(min < max && mid != min && mid != max) {
        long long int P = mid*(mid+1);
/*printf("search i %lld min %lld max %lld mid %lld P %lld d %lld\n", i, min, max, mid, P, d);  */
        if(P == d) {
            printf("%lld %lld\n", i, mid);
            return 1;
        }
        else if (P > d) {
            max = mid;
        }
        else {
            min = mid;
        }
        mid = (min + max) / 2;
    }
    
    return 0;
}

/* pass the own house as parameteer i */
int best_usesqrt(long long int i)
{
    long long int sum = ((1 + i) * i) /2;
    long long int d = 2 *sum + i*i - i;
 
    double z = (-1.0 + sqrt(1 + 4*d)) / 2;
    long long int L = (int) z;

    if(L*(L+1) == d) {
        printf("%10lld %10lld\n", i, L);
        return 1;
    }
    return 0;

}

/* pass the end house as parameter L */
int better_test(long long int L)
{
    long long int z = (L * L + L ) / 2;
    long long int r = (long long int) sqrt(z);
    if(abs((r * r) - z) < 0.00001) {
        printf("r*r %lld z %lld\n", r*r, z);
        printf("%lld%lld\n", r, L);
        return 1;
    }
    return 0;
}

int compute_result () 
{
    int i = 5;
    int counter = 0;
    while(counter < 10) {
        i++;
        if(best_usesqrt(i)) counter++;
    }
    return 0;
}

void print_result()
{
    
printf("         6         8\n        35        49\n       204       288\n      1189      1681\n      6930      9800\n     40391     57121\n    235416    332928\n   1372105   1940449\n   7997214  11309768\n  46611179  65918161\n");
}

int main()
{
    print_result();
    return 0;
}
