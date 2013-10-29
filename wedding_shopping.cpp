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
    vi distinct;
    distinct.reserve(MAXMONEY);
    int lastmax = 0;


    while(0 < Ntests--) 
    {
        int M = 0;
        int C = 0;
        scanf("%d %d\n",&M, &C);
        out("M = %d C =%d\n", M, C);

        int perfcounter = 0;

        int garments[20][20] = {0}; //20 garments, 20 of each
        si s1;


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
                s1.insert(d);
            }
        }


        out("s1: ");
        for(si::iterator it = s1.begin(); it != s1.end(); ++it) 
            out(" %d ", *it);
        out("\n");



        int count = 1;

        while (C > count++) 
        {
            int K = 0;
            scanf("%d\n",&K);
            out("K = %d ", K);
            si s2;

            forl(i,0,K) {
                //push v into vector
                int d = 0;
                scanf("%d",&d);
                out(" g%d = %d ", i, d);

                for(si::iterator it = s1.begin(); it != s1.end(); ++it) 
                {
                    int l = *it + d;
                    if(l <= M) {
                        s2.insert(l);
                        perfcounter++;
                    }
                    perfcounter++;
                }
            }
            s1 = s2;
            out("\n");

            out("s1: ");
            for(si::iterator it = s1.begin(); it != s1.end(); ++it) 
                out(" %d ", *it);
            out("\n");


        }

        out("s1: ");
        for(si::iterator it = s1.begin(); it != s1.end(); ++it) 
            out(" %d ", *it);
        out("\n");

        out("Perfcounter: %d\n", perfcounter);
        if(!s1.empty() && *s1.rbegin() <= M)
            printf("%d\n", *s1.rbegin());
        else
            printf("no solution\n");
    }

    return 0;
}
