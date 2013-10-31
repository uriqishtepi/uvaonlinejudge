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
float P[2 << 2*Nmax];
bool  F[2 << 2*Nmax];

int countbits(int c)
{
    int count = 0;
    while(c > 0) {
        if(c & 0x1) count++;
        c >>= 1;
    }
    return count;
}

void printbits(int c)
{
    forl(i,1,33) { out("%d",(c & (0x1 << (32-i))) >> (32-i)); }
    out("\n");
}


float findMin(int c)
{
    out("findmin c:"); printbits(c);
    if(c == 0) {
        printf("ERROR c = 0\n");
        exit(0);
    }

    if(F[c]) {
        out("returnint P[c]: %f\n",P[c]);
        return P[c];
    }

    int first = (-c) & c;
    out("firs:"); printbits(first);

    int rem = c ^ first;
    out("\nrem : "); printbits(rem);

    while(rem) {
        int next = (-rem) & rem;
        out("\nnext: "); printbits(next);

        int pair = first | next;
        out("\npair : "); printbits(pair);

        int withoutpair = c ^ pair;
        out("\nwpair : "); printbits(withoutpair);
        float newval = P[pair] + findMin(withoutpair);
        out("old: %f vs new %f\n", P[c], newval);


        P[c] = std::min(P[c], newval);

        out("remp: "); printbits(rem);
        out("next: "); printbits(next);
        rem = rem ^ next;
        out("remo: "); printbits(rem);
    }

    F[c] = true;
    out("\nOUT: "); printbits(rem);

    return P[c];
}

int main(int argc, char **argv)
{
    out("Starting...\n");
    printbits(3);

    int N = 0;
    int count = 0;
    while(scanf("%d\n",&N) != EOF && N != 0) {
        short loc[16][2] = {0};
        float dist[16][16] = {0};

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
            dist[i][i] = 0;
            P[ (1<<i) | (1<<i)] = 0;

            forl(j,0,i) {
                int x2 = loc[j][0];
                int y2 = loc[j][1];
                int dx = (x - x2);
                int dy = (y - y2);
                float d = sqrt(dx*dx + dy*dy);
                out("setting %d %d = %f\n",i,j,d);
                dist[i][j] = d;
                dist[j][i] = d;
                int offset = (1<<i) | (1<<j);
                out("offset %d\n",offset);
                P[offset] = d;
                F[offset] = true;
            }
        }

        //output the dist tbl so we know we have the correct data
        out("DIST\n");
        forl(i,0,M) {
            forl(j,0,M)
                out("%8.3f ",dist[i][j]);
            out("\n");
        }        
        
        out("\nP\n");
        forl(i, 0, M) {
            forl(j,0,M)
                out("%8.3f ",P[(1<<i) | (1<<j)]);
            out("\n");
        }
        
        out("\nF\n");
        forl(i, 0, M) {
            forl(j,0,i+1)
                out("%d ",F[(1<<i) | (1<<j)]);
            out("\n");
        }

        //compute min distances
        
        int s = ((unsigned int)(-1) << (32-M)) >> (32-M);
        printf("Case %d: %.2f\n", ++count, findMin(s));
    }

    return 0;
}
