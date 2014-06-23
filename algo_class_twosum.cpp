/* compute two sum, sum of two items from input that equals t:
 * compute the number of target values t in the interval [-10000,10000]
 * (inclusive) such that there are distinct numbers x,y in the input file that
 * satisfy x+y=t. 
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

int swapcounter = 0;

void swap (int &a, int &b)
{
    int t = b;
    b = a;
    a = t;
    swapcounter++;
}

inline int left(int a) { return 2*(a+1) - 1; }
inline int right(int a) { return 2*(a+1); }

void heapify(int arr[], int sz, int lastel)
{
    int min = -1;
    int l = 0;
    int r = 0;

    if((l=left(lastel)) < sz) 
        min = l;
    if((r=right(lastel)) < sz && arr[r] < arr[l])
        min = r;

    assert(min < sz && "not possible to be larger than sz");
    if(arr[min] < arr[lastel]) {
        swap(arr[min], arr[lastel]);
        heapify(arr, sz, min);
    }
}

//assume we want a MIN heap 
void heap_insert(int arr[], int sz, int lastel)
{
    int i = lastel;
    while(i > 0) {
        int p = (i-1) / 2;
        if(arr[p] <= arr[i]) 
            break; //nothing to do
        swap(arr[p], arr[i]);
        i = p;
    }
}

void heap_verify (int arr[], int sz)
{
    int i = sz - 1;
    while(i > 0) {
        int p = (i - 1)/ 2;
        if(arr[p] > arr[i]) {
            printf("arr[%d] (%d) > arr[%d] (%d)\n", p, arr[p], i, arr[i]);
            forl(i, 0, SZ) { printf("%d %d\n",i, arr[i]); }
        }
        assert(arr[p] <= arr[i] && "check failed");
        i--;
    }
}

struct point {
    int x;
    int y;
};
#define si std::set<long long int>
#define vi std::vector<long long int>



inline void find_in_cont(long long int & in, const si & coll, bool arr[])
{
    //printf("find_in_cont() in=%lld\n", in);
    //find -10000 - in, do next until > 10000 - in
    si::const_iterator it = coll.lower_bound((-10000 - in));
    while(it != coll.end()) {
        //printf("find_in_cont() looking for (-10000-%lld)=%lld, found it=%lld\n", in, (-10000-in), *it);
        long long int diff = *it + in;
        if(diff > 10000) break;
        if(diff >= -10000) {
            //printf("found diff=%lld  %lld,%lld\n",diff,in, *it);
            arr[diff + 10000] = true;
        }
        it++;
    }
}

int main (void)
{
    long long int in;
    bool arr[200001] = {0};
    si pcoll;
    si ncoll;

    while(scanf("%lld\n", &in) != EOF) {
        if(in > 0) { 
            std::pair<si::iterator,bool> ret = pcoll.insert(in);
            if(ret.second == true)  
                find_in_cont(in, ncoll, arr);
        }
        else {
            std::pair<si::iterator,bool> ret = ncoll.insert(in);
            if(ret.second == true) 
                find_in_cont(in, pcoll, arr);
        }
    }

    int counter = 0;
    for(int i = -10000; i <= 10000; i++) {
        if(arr[i+10000]) counter++;
    }

    printf("counter=%d\n",counter);
    return 0;
}

