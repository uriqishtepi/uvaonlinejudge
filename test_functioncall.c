#include<stdio.h>


void func(int *tot, int i)
{
    *tot += i;
}
void onefunc(int *tot, int max) 
{
    int i = 0;
    while (i < max) {
        *tot += i;
        i++;
    }
}
 
int main()
{

    int tot = 0;
    int i = 0;
    /*
    while (i < 100000000) {
        func(&tot, i);
        i++;
    }
    */
    onefunc(&tot, 100000000);

    return 0;
}
