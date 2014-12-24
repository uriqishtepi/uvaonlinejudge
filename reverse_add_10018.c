#include<stdio.h>
void itoarr(unsigned char dest[], char destlen, int n)
{
    char i = destlen;
    if(0 == n) { dest[0] = '0'; return ;}
    while(i-- > 0 && n > 0) {
        dest[i] = (n % 10) + '0';
        n /= 10;
    }
}

void process(long long int num)
{
    int count = 0;
    while(++count < 1000 && num < 4294967295) {
        //get reverse

        //sum = num + reverse
        //if palindrome done
        //else num = sum
    }
}

int main()
{
    unsigned int n;
    scanf("%u\n", &n);
    while(n-- > 0) {
        long long int num;
        scanf("%lld\n", &num);
        process(num);
    }
}
