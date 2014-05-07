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

char B[][4] = { 
"BCG",
"BGC",
"CBG",
"CGB",
"GBC",
"GCB"
};

int M[][3] = {
{0,5,7},
{0,4,8},
{2,3,7},
{2,4,6},
{1,3,8},
{1,5,6}
};

int main(int argc, char **argv)
{
    out("Starting...\n");

    int H, U, D, F;
    int count = 0;
    int a[10] = {0};
    int sum = 0;
    while(scanf("%d",a+count) != EOF) 
    {
        sum += a[count];
        count++;
        if(count < 9) continue;

        out("Params: ");
        for(int i=0; i < count; i++)
            out("%d ", a[i]);
        out("\n");

        int min = sum;
        int off = -1;
        for(int i=0; i < 6; i++) {
            int loc = sum;
            for(int j = 0; j < 3; j++) {
                loc -= a[M[i][j]];
            }
            if(min > loc) { 
                min = loc;
                off = i;
            }
        }
        printf("%s %d\n", B[off], min);

        count = 0;
        sum = 0;
    }

    return 0;
}
