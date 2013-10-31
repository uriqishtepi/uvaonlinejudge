#include<stdio.h>
#include<math.h>
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
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

#define Nmax 8
float P[1 << 2*Nmax];
bool  F[1 << 2*Nmax];

float findMin(int c)
{
    if(c == 0) {
        printf("ERROR c = 0\n");
        exit(0);
    }

    if(F[c]) {
        return P[c];
    }

    int first = (-c) & c;
    int rem = c ^ first;

    while(rem) {
        int next = (-rem) & rem;
        int pair = first | next;
        int withoutpair = c ^ pair;
        float newval = P[pair] + findMin(withoutpair);

        P[c] = std::min(P[c], newval);
        rem = rem ^ next;
    }

    F[c] = true;
    return P[c];
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    int N = 0;
    int count = 0;
    while(scanf("%d\n",&N) != EOF && N != 0) {
        short loc[16][2] = {0};

        forl(i,0,sizeof(P)/sizeof(P[0]))
            P[i] = INF;
        memset(F, 0, sizeof(F));

        out("N= %d \n", N);
        int M = 2*N;
        forl(i,0,M) {
            int x = 0;
            int y = 0;
            char name[21] = {0};
            scanf("%s %d %d\n",&name, &x, &y);
            loc[i][0] = x;
            loc[i][1] = y;
            out("%s %d %d \n", name, x, y);
            P[ (1<<i) | (1<<i)] = 0;

            forl(j,0,i) {
                int x2 = loc[j][0];
                int y2 = loc[j][1];
                int dx = (x - x2);
                int dy = (y - y2);
                float d = sqrt(dx*dx + dy*dy);
                out("setting %d %d = %f\n",i,j,d);
                int offset = (1<<i) | (1<<j);
                out("offset %d\n",offset);
                P[offset] = d;
                F[offset] = true;
            }
        }

        //compute min distances
        int s = ((unsigned int)(-1) << (32-M)) >> (32-M);
        printf("Case %d: %.2f\n", ++count, findMin(s));
    }

    return 0;
}
