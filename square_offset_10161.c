#include <stdio.h>
#include <math.h>

void getOffset(int N) {
    int s = floor(sqrt(N-1));
    int squared = s*s;
    int l = N - squared;
    int rem = l%(s+1);
    /* printf("N %d  s %d   l %d   rem %d\n",N, s, l, rem); */

    int x;
    int y;
    if(l>=s+1) { 
        x=s+1-rem;
        y=s+1;
    }
    else { 
        y=rem;
        x=s+1;
    }
        

    if(s%2) { /* flip x/y*/ 
        int tmp = y;
        y=x;
        x=tmp;
    }
    printf("%d %d\n", x , y);
}

int main()
{
    int N =9;
    /*for(N=1;N<30;N++) getOffset(N); */

    while(scanf("%d", &N) != EOF && N != 0) {
        getOffset(N);
    }
    return 0;
}
