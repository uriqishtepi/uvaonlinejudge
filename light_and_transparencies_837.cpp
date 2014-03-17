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
#include<stdio.h>
#include<math.h>
#include<assert.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define mtsi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define ss std::set<std::string>
#define mi std::map<int, int>
#define md std::map<double, double>
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


void minmax(double x1, double x2, double &a, double &b) 
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
            char x1s[128],x2s[128],y1[128],y2[128],rs[128];
            double x1,x2,r,a,b;
            scanf("%s %s %s %s %s\n", &x1s,&y1,&x2s,&y2,&rs);
            x1 = atof(x1s);
            x2 = atof(x2s);
            r = atof(rs);
            out("%lf %s %lf %s %lf\n", x1,y1,x2,y2,r);
            minmax(x1,x2,a,b);
            assert(r <= 1);
            //if you want to not show things with same x1 and x2
            if(x1 == x2) { out("1 C %lf\n", abs(x1 - x2)); continue; }
            //if you wanted to merge two sections with r = 1
            //if((1.0 - r) < 0.000000000001) { out("2 C %lf\n", (1.0 - r));  continue; }
            if(r == 0.0)
                r = 0.00001;

            m.insert(std::make_pair(a,r));
            m.insert(std::make_pair(b,1.0/r));
        }

        if(m.empty()) { 
            printf( "1\n-inf +inf 1.000\n"); 
            continue;
        }

        printf("%d\n", m.size()+1);
        md::iterator it = m.begin();
        double lastp = it->first;
        double lastr = 1.0;
        printf( "-inf %.3lf %.3lf\n" , lastp, lastr);
        lastr = lastr * it->second;
        ++it;
        for(;it != m.end(); ++it) {
            double nextp = it->first;
            out("next x = %lf w = %lf\n",nextp, it->second);
            printf( "%.3lf %.3lf %.3lf\n" , lastp, nextp, lastr);
            lastp = nextp;
            lastr = lastr*it->second;
        }
        printf( "%.3lf +inf %.3lf\n", lastp, lastr);
        if(k < cases-1) printf("\n");
        assert(1.0 - lastr < 0.000000000001);
    }
    return 0;
}
