#include<stdio.h>
#include<math.h>
#include<iostream>
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

typedef struct {
    int B;
    int D;
    int S;
    vi Ld;
    vi Ud;
    vi Cn;
    int C0;
} dims;

int main(int argc, char **argv)
{
    out("Starting...\n");

    int N = 0;
    int R = 0;
    scanf("%d %d\n", &N, &R);
    out("N=%d R=%d\n",N, R);
    std::map<std::string, dims> m;

    forl(i,0,N) 
    {
        char name[10];
        //base size dimensions
        dims dd;
        scanf("%s %d %d %d ", &name, &dd.B, &dd.S, &dd.D);
        out("name=%s, B=%d, S=%d D=%d\n",name,dd.B,dd.S,dd.D);

        forl(j,0,dd.D) {
            int d;
            scanf("%d ", &d);
            dd.Ld.push_back(d);
            out("d=%d ",d);

            scanf("%d ", &d);
            dd.Ud.push_back(d);
            out("d=%d ",d);
        }
        out("\n");

        dd.Cn.push_back(dd.S);
        dd.C0 = dd.B - dd.Ld[dd.D-1] * dd.S;
        for(int j = dd.D-1; j > 0; j--) {
            int tc = dd.Cn.back() * (dd.Ud[j] - dd.Ld[j] + 1);
            out("j = %d, tc = %d\n", j, tc);

            dd.Cn.push_back(tc);
            dd.C0 -= dd.Ld[j-1] * tc;
        }
        out("size of Cn = %d\n", dd.Cn.size());
        reverse(dd.Cn.begin(), dd.Cn.end());
        m[name] = dd;
    }
    
    forl(i,0,R) {
        char name[10];
        scanf("%s ", &name);
        out("name=%s\n",name);
        dims &dd = m[name];

        int index = dd.C0;
        out("index =%d ", index);

        printf("%s[", name);
        forl(j,0,dd.D) {
            int d;
            scanf("%d ", &d);
            printf("%d",d);

            if(j < dd.D - 1) printf(", ");

            index += d * dd.Cn[j];
            out("\nindex =%d ", index);
            out("j = %d, tc = %d\n", j, dd.Cn[j]);
        }
        printf("] = %d\n", index);
    }


    return 0;
}
