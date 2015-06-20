#include<stdio.h>

/* b    e    t  r
 * 1    0    1  1
 * 2    1    3  0
 * 3    1    4  1
 * 4    1+1  6  0
 * 5    1+1  7  1
 * 6    2+1  9  0
 * 7    3   10  1
 * 8    3+1 12  0
 * 9    3+1 13  1
 *10    4+1 15  0
 */

int main()
{
    int a[201] = {0};
    int wb[201] = {0}; /*without borrow */
    int rem[201] = {0}; /* orig remainder */
    int i = 0;
    a[1] = 1;
    
    for(i=2;i<=200;i++) {
        int rem = i % 2;
        a[i] = a[i-1] + 1 + (!rem);
        /* printf("%d %d\n", i, a[i]); */
    }
    int N;
    while(scanf("%d", &N) != EOF) { printf("%d\n", a[N]); }

    return 0;
}
