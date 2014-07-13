/* Compute completion times 
 * g++ -std=c++11 -Wall -g   algo_class_twosum.cpp   -o algo_class_twosum
 */
#include <set>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define SZ (32-1)

struct pair {
    int w;
    int l;
};


struct cmppairdiff {
    bool operator()(const pair & a, const pair &b) {
        int ad = (a.w - a.l);
        int bd = (b.w - b.l); 
        if(ad == bd) return a.w > b.w;
        else return ad > bd;
    }
};

struct cmppairratio {
    bool operator()(const pair & a, const pair &b) {
        double ar = ((double)a.w / a.l);
        double br = ((double)b.w / b.l); 
        if(ar == br) return a.w > b.w;
        else return ar > br;
    }
};

#define sp std::multiset<pair, cmppairratio>
#define sd std::multiset<pair, cmppairdiff>
#define vi std::vector<long long int>


int main (void)
{
    sp s;
    sd d;
    int counter = 0;
    int n, w, l;
    scanf("%d", &n);

    while(scanf("%d %d\n", &w, &l) != EOF && n-- > 0) {
        pair p;
        p.w = w;
        p.l = l;
        s.insert(p);
        d.insert(p);
        counter++;
    }

    long long unsigned int v1;
    long long unsigned int v2;
    {
        long long unsigned int end_time = 0; 
        long long unsigned int total_weight = 0;
        for(sp::iterator it = s.begin(); it!= s.end(); ++it) {
            end_time += it->l;
            total_weight += end_time*it->w;
            printf("w l et t =  %d %d %lld %lld\n", it->w, it->l, end_time, total_weight);
        }
        v1=total_weight;
    }

    {
        long long unsigned int end_time = 0; 
        long long unsigned int total_weight = 0;
        for(sd::iterator jt = d.begin(); jt!= d.end(); ++jt) {
            end_time += jt->l;
            total_weight += end_time*jt->w;
            printf("w l et t =  %d %d %lld %lld\n", jt->w, jt->l, end_time, total_weight);
        }
        v2=total_weight;
    }
    printf("vd=%lld vs=%lld \n", v2, v1);
    return 0;
}

