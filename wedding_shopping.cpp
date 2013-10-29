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
    int lastmax = 0;
    vi s1;
    s1.reserve(MAXMONEY);

    while(0 < Ntests--) 
    {
        int M = 0;
        int C = 0;
        scanf("%d %d\n",&M, &C);
        out("M = %d C =%d\n", M, C);

        int perfcounter = 0;

        int slots[MAXMONEY + 1] = {0};
        s1.clear();

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
                s1.push_back(d);
            }
        }

        std::sort(s1.begin(), s1.end());

        /*
        out("s1: ");
        for(vi::iterator it = s1.begin(); it != s1.end(); ++it) 
            out(" %d ", *it);
        out("\n");
        */


        int count = 1;

        while (C > count++) 
        {
            int K = 0;
            scanf("%d\n",&K);
            out("K = %d ", K);

            forl(i,0,K) {
                //push v into vector
                int d = 0;
                scanf("%d",&d);
                out(" g%d = %d ", i, d);

                for(vi::iterator it = s1.begin(); it != s1.end(); ++it) 
                {
                    int l = *it + d;
                    if(l <= M) {
                        slots[l] = 1;
                        perfcounter++;
                    }
                    perfcounter++;
                }
            }
            out("\n");

            s1.clear();
            forl(i,0,M) {
                if(slots[i])
                    s1.push_back(i);
                slots[i]=0;
            }

            /*
            out("s1: ");
            for(vi::iterator it = s1.begin(); it != s1.end(); ++it) 
                out(" %d ", *it);
            out("\n");
            */

        }

        /*
        out("s1: ");
        for(vi::iterator it = s1.begin(); it != s1.end(); ++it) 
            out(" %d ", *it);
        out("\n");
        */

        out("Perfcounter: %d\n", perfcounter);
        if(!s1.empty() && *s1.rbegin() <= M)
            printf("%d\n", *s1.rbegin());
        else
            printf("no solution\n");
    }

    return 0;
}
