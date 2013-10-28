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

#define DEBUG true
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
        int counts[20] = {0}; //20 garments

        int count = 0;
        while (C > count++) {
            int K = 0;
            scanf("%d\n",&K);
            out("K = %d ", K);
            counts[count-1] = K;

            forl(i,0,K) {
                //push v into vector
                int d = 0;
                scanf("%d",&d);
                garments[count-1][i] = d;
                out(" g%d = %d ", i, d);
            }
            out("\n");
        }

        lastmax = 0;
        distinct.clear();

        //populate with first garment
        forl(i, 0, counts[0]) {
            int l = garments[0][i];
            if(l <= M) {
                distinct.push_back(l);
                if(lastmax < l) { 
                    lastmax = l;
                    perfcounter++;
                }
            }
        }


        //go through next garment, and update sum
        forl(i, 1, C) 
        {
            perfcounter++;
            bool sum[MAXMONEY] = {0};

            for(vi::iterator it = distinct.begin(); it < distinct.end(); ++it) 
            {
                perfcounter++;
                forl(j, 0, counts[i]) 
                {
                    int l = *it + garments[i][j];
                    perfcounter++;

                    if(l == M && i == C) { 
                        lastmax = M;
                        goto ENDOFITEM; //found, get out
                    }
                    else if(l < M) { 
                        sum[l] = true;
                        perfcounter++;
                    }
                }
            }

            lastmax = 0;

            distinct.clear();
            out("sum: ");
            forl(k,0,M+1) {
                if(sum[k]) {
                    out(" %d", k);
                    distinct.push_back(k);
                }
                perfcounter++;
            }
            out("\n");
            lastmax = distinct.back();
        }

ENDOFITEM:
        out("Perfcounter: %d\n", perfcounter);
        if(lastmax > 0 && lastmax < M)
            printf("%d\n", lastmax);
        else
            printf("no solution\n");
    }

    return 0;
}
