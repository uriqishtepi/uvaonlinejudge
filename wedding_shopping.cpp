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

        #define MAXMONEY 201

        bool sum[MAXMONEY] = {0};
        int lastmax = 0;

        //populate with first garment
        forl(i, 0, counts[0]) {
            int l = garments[0][i];
            if(l <= M) {
                sum[l] = true;
                if(lastmax < l) { 
                    lastmax = l;
                    perfcounter++;
                }
            }
        }


        //go through next garment, and update sum
        forl(i, 1, C) {
            bool newsum[MAXMONEY] = {0};
            forl(k,0,lastmax+1) {
                if(sum[k]) {
                    forl(j, 0, counts[i]) {
                        int l = k + garments[i][j];
                        perfcounter++;

                        if(l <= M) { 
                            newsum[l] = true;
                            perfcounter++;
                        }
                    }
                }
            }

            lastmax = 0;
            //copy sum to next iteration
            forl(k,0,M+1) {
                sum[k] = newsum[k];
                perfcounter++;

                if(sum[k] && lastmax < k) {
                    lastmax = k;
                    perfcounter++;
                }
                if(lastmax == MAXMONEY) break;
            }
            //forl(i, 0, MAXMONEY) { out("%d ", sum[i]); } out("\n");
        }

        out("Perfcounter: %d\n", perfcounter);
        if(lastmax > 0)
            printf("%d\n", lastmax);
        else
            printf("no solution\n");
    }

    return 0;
}
