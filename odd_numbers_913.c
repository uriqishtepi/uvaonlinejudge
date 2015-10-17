/* sums of odd numbers
 * 1
 * 3 5 7
 * 9 11 13 15 17
 * 19 21 23 25 27 29 31
 * 33 35 37 39 41 43 45 47 49
 *
 * 1 3 5 7 9 11 13 15 17 19 21 23 25 27 29 31...
 * n=2*lvl - 1
 * lvl = (n+1) / 2
 *
 * how many (n+1)/2 * (n+1)/2
 * order (n+1)^2 / 4
 * ANSW = (2 * order - 3) * 3
 *
 *
 * 5 -> 6*6 / 4 = 36/4 = 9 -> 9+4 => 18 + 1
 * 7 -> 8*8 / 4 = 64/4 = 16 -> 16 + 4 => 32 + 1
 * 9 -> 10*10 /4=100/4 = 25 => 50+1
 *
 */
#include <stdio.h>


int main() 
{
    int n;
    while(scanf("%d", &n) != EOF && n > 1) {
        unsigned long long int order = (n + 1);
        order = order * order;
        order = order / 4;

        unsigned long long int answer = (2 * order - 3) * 3;
        printf("%lld\n", answer);
    }
    return 0;

}
