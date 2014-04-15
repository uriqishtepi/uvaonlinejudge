#include <stdlib.h>
#include<stdio.h>
#include<assert.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define SZ 16

void swap (int &a, int &b)
{
    int t = b;
    b = a;
    a = t;
}

//let's assume we have a min heap here
void heap_insert(int arr[], int sz, int &lastel, int el)
{
    arr[lastel] = el;
    int i = lastel;
    while(i > 0) {
        int p = i / 2;
        if(arr[p] > arr[i])
            swap(arr[p], arr[i]);
        i = p;
    }
    lastel++;
}

void heap_verify (int arr[], int sz, int lastel)
{
    int i = lastel - 1;
    while(i > 0) {
        int p = i / 2;
        assert(arr[p] <= arr[i]);
        i = p;
    }
}

int main (void)
{
    int arr[SZ];
    forl(i, 0, SZ) {
        arr[i] = rand() % SZ*10;
    }

    forl(i, 0, SZ) { printf("%d %d\n",i, arr[i]); }

    int lastel = 1;
    forl(i, 1, SZ) { heap_insert(arr, SZ, lastel, arr[i]); }

    forl(i, 1, SZ) { heap_insert(arr, SZ, lastel, arr[i]); }

    forl(i, 0, SZ) { printf("%d %d\n",i, arr[i]); }
    heap_verify(arr, SZ, lastel);

    return 0;
}

