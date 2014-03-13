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
#define md std::map<float, float>
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


void minmax(float x1, float x2, float &a, float &b) 
{
    if(x1 < x2) {
        a = x1;
        b = x2;
    }
    else {
        a = x2;
        b = x1;
    }
}

int main(int argc, char **argv)
{
    out("Starting...\n");

    int cases;
    scanf("%d\n", &cases);
    out("cases = %d\n", cases);
    forl(k, 0, cases) 
    {
        int nl;
        scanf("%d\n", &nl);
        out("nl = %d\n", nl);

        md m;

        forl(i, 0, nl) {
            float x1,x2,y1,y2,r,a,b;
            scanf("%f %f %f %f %f\n", &x1,&y1,&x2,&y2,&r);
            out("%f %f %f %f %f\n", x1,y1,x2,y2,r);
            minmax(x1,x2,a,b);

            m.insert(std::make_pair(a,r));
            m.insert(std::make_pair(b,1.0/r));
        }

        if(m.empty()) break;

        md::iterator it = m.begin();
        double lastp = it->first;
        double lastr = 1.0;
        printf( "-inf %.3f %.3f\n" , lastp, lastr);
        lastr = lastr * it->second;
        ++it;
        for(;it != m.end(); ++it) {
            double nextp = it->first;
            printf( "%.3f %.3f %.3f\n" , lastp, nextp, lastr);
            lastp = nextp;
            lastr = lastr*it->second;
        }
        printf( "%.3f +inf %.3f\n", lastp, lastr);
    }
    return 0;
}
