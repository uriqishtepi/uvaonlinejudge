/* compute median of the list 
 */
#include <set>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include<stdio.h>
#include<assert.h>
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
#define si std::multiset<int>
#define vi std::vector<int>

int main (void)
{
    int in;
    si coll;
    si items;
    int i = 0;
    int sum = 0;
    while(scanf("%d\n", &in) != EOF) {
        ++i;
        items.insert(in);
        int med = (i+1) / 2 - 1;
        si::iterator it = items.begin();
        //printf("%d ", med);
        for(; med > 0; ++it, --med);
        //printf("%d \n", *it);
        sum = (sum + *it) % 10000;
    }
    printf("\nsum=%d\n",sum);
    return 0;
}

