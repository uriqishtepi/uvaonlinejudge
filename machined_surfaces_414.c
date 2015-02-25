#include<stdio.h>

int main()
{
    int N;
    while(scanf("%d\n", &N) != EOF && N != 0) {
        int totsp = 0;
        int minsp = 30;
        int lncount = N;
        char buff[30];
        while(--N >= 0) {
            int nsz;
            fgets(buff, 27, stdin);
            /* printf("line %d: '%s'\n", N, buff); */
            int i;
            int leftdone = 0;
            int sp = 0;
            for(i=0;i<25;i++) {
                if(buff[i] == ' ') {
                    if(!leftdone)
                        leftdone=1;
                    sp++;
                }
            }
            totsp += sp;
            if(minsp > sp) minsp = sp;
        }
        printf("%d\n", totsp - minsp*lncount);

    }

    return 0;
}
