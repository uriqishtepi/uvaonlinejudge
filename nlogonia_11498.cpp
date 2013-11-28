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
#define ss std::set<std::string>
#define mi std::map<int, int>
#define mmi std::multimap<int, int>
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

    char * buff = NULL;
    int K; 
    while( scanf("%d\n", &K) != EOF && K != 0) 
    {
        out("%d\n", K);

        int N, M;
        scanf("%d %d\n", &N, &M);
        out("%d %d\n", N, M);

        forl(i,0,K) {
            int x, y;
            scanf("%d %d\n",&x,&y);
            out("Red %d %d\n",x,y);

            if(x == N || y == M)
                printf("divisa\n");
            else if(x < N && y < M)
                printf("SO\n");
            else if(x < N && y > M)
                printf("NO\n");
            else if(x > N && y > M)
                printf("NE\n");
            else if(x > N && y < M)
                printf("SE\n");
        }
    }
    return 0;
}

