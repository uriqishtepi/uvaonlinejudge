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
#define mci std::map<char, int>
#define mic std::map<int, char>
#define mmi std::multimap<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


//returns true if a is smaller than b
int count_inversions(std::vector<int> &v)
{
    int count = 0;
    for(int i = 0; i < v.size() - 1; i++) 
        for(int j = i+1; j < v.size(); j++) 
            if(v[i] > v[j])
                count++;
    return count;
}

long long int merge_and_count(std::vector<int> &v, int s, int mid, int e, std::vector<int> &c)
{
    int k = s;
    int i = s;
    int j = mid;
    long long int count = 0;
    while(k < e && i < mid && j < e) {
        if(v[i] <= v[j]) {
            c[k] = v[i];
            i++;
        }
        else {
            c[k] = v[j];
            count += (mid-i);
            j++;
        }
        k++;
    } 
    while(i < mid) {
        c[k] = v[i];
        i++;
        k++;
    }
    while(j < e) {
        c[k] = v[j];
        j++;
        k++;
    }
    for(int i = s; i < e; i++) {
        v[i] = c[i];
    }
    return count;
}


long long int sort_and_count(std::vector<int> &v, int s, int e, std::vector<int> &c)
{
    if (s >= e - 1) { //if only one element
        return 0;
    }
    int  mid = (s + e) / 2;
    long long int x = sort_and_count(v, s, mid, c);

    long long int y = sort_and_count(v, mid, e, c);

    long long int z = merge_and_count(v, s, mid, e, c);

    return x + y + z;
}

int main(int argc, char **argv)
{
    out("Starting...\n");
    int m;
    std::vector<int> v;

    while(scanf("%d", &m) != EOF)
    {
        v.push_back(m);
    }
    printf("size=%d\n", v.size());
    std::vector<int> c;
    c.resize(v.size());
    //printf("inversions=%d\n", count_inversions(v));
    printf("inversions2=%lld\n", sort_and_count(v, 0, v.size(), c));
    return 0;
}

