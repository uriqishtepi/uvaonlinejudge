#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
#include<set>
#include<map>
#include <string.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define msi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define mi std::map<int, int>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

int main(int argc, char **argv)
{
    out("Starting...\n");

    int Ntests = 0;
    scanf("%d\n",&Ntests);
    out("Ntests = %d \n", Ntests);

    #define MAXMONEY 201

    while(0 < Ntests--) 
    {
        int M = 0;
        int C = 0;
        scanf("%d %d\n",&M, &C);
        out("M = %d C =%d\n", M, C);

        int perfcounter = 0;

        int slots[MAXMONEY] = {0};
        int s1[MAXMONEY] = {0};
        int size = 0;

        //first element
        {
            int K = 0;
            scanf("%d\n",&K);
            out("K = %d ", K);

            forl(i,0,K) {
                //push v into vector
                int d = 0;
                scanf("%d",&d);
                out(" g%d = %d ", i, d);
                s1[size++] = d;
            }
        }

        std::sort(s1, s1+size);
        while (--C > 0) 
        {
            int K = 0;
            scanf("%d\n",&K);
            out("K = %d ", K);

            forl(i,0,K) {
                //push v into vector
                int d = 0;
                scanf("%d",&d);
                out(" g%d = %d ", i, d);
                if(d + s1[0] > M)
                    continue;

                out("size %d\n", size);
                forl(j,0,size)
                {
                    int l = s1[j] + d;
                    if(l <= M) {
                        slots[l] = 1;
                        perfcounter++;
                    }
                    perfcounter++;
                }
            }
            out("\n");

            memset(s1, 0, sizeof(s1));
            size = 0;
            forl(i,0,M+1) {
                if(slots[i])
                    s1[size++] = i;
                slots[i]=0;
            }
        }

        out("Perfcounter: %d\n", perfcounter);
        if(size > 0 && s1[size-1] <= M)
            printf("%d\n", s1[size-1]);
        else
            printf("no solution\n");
    }

    return 0;
}
