#include<stdio.h>
#include<math.h>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<functional>
#include<vector>
#include<bitset>
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

int main(int argc, char **argv)
{
    out("Starting...\n");

    char *line = NULL;
    int n, m, c;
    int counter = 0;
    while(scanf("%d %d %d\n", &n, &m, &c) != EOF && n != 0)
    {
        counter++;
        out("In: %d %d %d\n", n, m, c);
        vi consum;
        vi status;

        forl(i,0,n){
           int d;
           scanf("%d\n",&d);
           out("%d ",d);
           consum.push_back(d);
           status.push_back(0);
        }
        out("\n");

        int max = 0;
        vi oper;
        int curr = 0;
        forl(i,0,m){
           int d;
           //toggling i-th device

           scanf("%d\n",&d);
           d--;

           curr = curr + (1-status[d]) * consum[d] + status[d] * (-1) * consum[d];
           status[d] = !status[d];
           out("%d status %d consum %d curr %d\n",d, status[d], consum[d],curr);

           if(max < curr) 
               max = curr;
        }

        printf("Sequence %d\n", counter);
        if(max > c)
            printf("Fuse was blown.\n\n");
        else {
            printf("Fuse was not blown.\n");
            printf("Maximal power consumption was %d amperes.\n\n", max);
        }
    }

    return 0;
}
