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

int main (void)
{
    int arr[SZ];
    int arr2[SZ];
    forl(i, 0, SZ) {
        arr[i] = rand() % SZ*10;
    }
    memcpy(arr2,arr,sizeof(arr2));

    printf("unsorted:\n");
    forl(i, 0, SZ) { printf("%d %d\n",i, arr[i]); }

    swapcounter = 0;
    printf("doing heap insert\n");
    forl(i, 1, SZ) { heap_insert(arr, SZ, i); }
    printf("swapcounter=%d\n",swapcounter);
    printf("sorted1:\n");
    //forl(i, 0, SZ) { printf("%d %d\n",i, arr[i]); }
    heap_verify(arr, SZ);

    //best to start at the end, and substitute with the parent as you go
    swapcounter = 0;
    printf("doing heapify\n");
    for(int i = (SZ/2 - 1); i >= 0; i--) { heapify(arr2, SZ, i); }
    printf("swapcounter=%d\n",swapcounter);
    printf("sorted2:\n");
    //forl(i, 0, SZ) { printf("%d %d\n",i, arr2[i]); }
    heap_verify(arr2, SZ);

    return 0;
}

