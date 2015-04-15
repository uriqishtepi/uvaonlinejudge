#include<stdio.h>
#include<stdlib.h>
#define MAX 200

unsigned int arr[MAX+1] = {0};
int isPrime(int a)
{
    int i;
    for (i = 0; arr[i] * arr[i] <= a; i++)
        if((a % arr[i]) == 0) return 0;

    return 1;
}

int getRev( int a)
{
    char str[11] = {0};
    char * ptr=str;
    while(a > 0) {
        *ptr++ = (a%10) + '0';
        a /= 10;
    }
    return atoi(str);
}

int lgetRev(int a)
{
    char str[10] = {0};
    /*myitoa(str, a); */
    char rev[10] ={0};
    char * ptr = str;
    while(*ptr != '\0') ptr++;
    ptr--;
    char * to = rev;
    while(ptr != str) *to++ = *ptr--;
    return atoi(rev);
}

void printEmirp(int n) 
{
    if(n == 1) {
        printf("%d is prime.\n", n);
    }
    else if(!isPrime(n)) 
        printf("%d is not prime.\n", n);
    else {
        int rev = getRev(n);
        if(rev != n && isPrime(rev))
            printf("%d is emirp.\n", n);
        else
            printf("%d is prime.\n", n);
    }
}


int main()
{
    int pc = 0;
    arr[pc++] = 2;
    arr[pc++] = 3;
    arr[pc++] = 5;

    int i;
    for (i = 7; pc < MAX; i+=2) {
        if(isPrime(i))  {
            /* printf("last pc %d arr %d\n", pc, i); */
            arr[pc++] = i;
        }
    }

    /* for(i = 0; i < 1000000; i++) printEmirp(i);  */

    int n;
    while(scanf("%d", &n)!=EOF) {
        printEmirp(n);
    }
    

    return 0;
}
