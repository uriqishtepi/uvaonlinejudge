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

    int H, U, D, F;
    while(scanf("%d %d %d %d\n",&H, &U, &D, &F) != EOF && H != 0) 
    {
        out("Params: %d %d %d %d\n",H, U, D, F);
        float curr = 0;
        float up = U;
        int day = 0;
        do {
            day++;
            out("%d pre: H=%d up=%f D=%d F=%d curr=%f\n",day, H, up, -D, F, curr);
            curr += up;
            if(curr > H) break;
            out("%d pst: H=%d up=%f D=%d F=%d curr=%f\n",day, H, up, -D, F, curr);
            curr -= D;
            up -= ((float)U*F)/100;
            if(up < 0) up = 0;
            out("%d ptt: H=%d up=%f D=%d F=%d curr=%f\n",day, H, up, -D, F, curr);
        } while(curr <= H && curr >= 0);

        if(curr > H)
            printf("success on day %d\n", day);
        else
            printf("failure on day %d\n", day);
    }

    return 0;
}
