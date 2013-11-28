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

    char str[21] = {0};
    size_t n;
    int counter = 0;
    char * buff = NULL;
    int hr;
    const double coef = (double) 10000000 / (24 * 60 * 60 * 100);

    while(scanf("%d",&hr) != EOF) 
    {
        out("%d\n",hr);
        int cc = hr%100;
        hr /= 100;
        int ss = hr%100;
        hr /= 100;
        int mm = hr%100;
        hr /= 100;
        out("%d:%d:%d:%d\n",hr,mm,ss,cc);
        
        int regsectime = ((hr * 60 + mm)  * 60 + ss) *100 + cc; 
        out("%d\n",regsectime);
        double dectime = (double)regsectime * coef;
        out("%f\n",dectime);
        printf("%07d\n",(int)dectime);
    }
    return 0;
}
