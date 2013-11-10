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
#include <iomanip>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define mtsi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define mi std::map<int, int>
#define msi std::map<std::string, int>
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

    int n;
    scanf("%d",&n);
    int a, b;

    while(scanf("%d %d",&a, &b) != EOF) 
    {
        out("%d %d\n",a, b);
        float xf = (float)(a + b)/2;
        int x = (int)(a + b)/2;
        int y = a - x;
        if(xf - x > 0 || y < 0)
            printf("impossible\n");
        else
            printf("%d %d\n",x,y);
    }
    return 0;
}
