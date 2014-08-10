/* This is an example of a two way heap how to insert into it 
 * and how to turn an array with data into a min heap.
 */
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define SZ (2122332-1)

int swapcounter = 0;

void swap (int &a, int &b)
{
    int t = b;
    b = a;
    a = t;
    swapcounter++;
}

#define parent(a) ((a-1)/2)
inline int left(int a) { return 2*(a+1) - 1; } //right is left + 1

//percolate from el up to sz to have min heap property
//this way of building the heap takes O(n) (not nlogn)
void siftDown(std::vector<int> &arr, int sz, int el)
{
    int min = -1;
    int l = 0;
    int r = 0;

    if((l=left(el)) < sz) 
        min = l;
    if((r=l+1) < sz && arr[r] < arr[l])
        min = r;

    while(min > el && arr[min] < arr[el]) 
    {
        swap(arr[min], arr[el]);
        el = min;

        if((l=left(el)) < sz) 
            min = l;
        if((r=l+1) < sz && arr[r] < arr[l])
            min = r;
        assert(min < sz && "not possible to be larger than sz");
    } 
}

void heapify(std::vector<int> &arr, int sz)
{
    //start at last parent element down to 0, perform siftDown
    //last element is (SZ-1), and its parent is
    for(int i = parent(SZ-1); i >= 0; i--) { siftDown(arr, SZ, i); }
}


//assume we want a MIN heap 
void heap_insert(std::vector<int> &arr, int sz, int el)
{
    while(el > 0) {
        int p = (el-1) / 2;
        if(arr[p] <= arr[el]) 
            break; //nothing to do
        swap(arr[p], arr[el]);
        el = p;
    }
}

void heap_verify (std::vector<int> &arr, int sz)
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


void timediff(const char * s) {
    static timeval tv;
    timeval tmp;

    gettimeofday(&tmp, NULL);
    int sec = (tmp.tv_sec - tv.tv_sec)*1000000;
    int msec = (tmp.tv_usec - tv.tv_usec);
    printf("%20.20s diff = %12.dusec\n", s, sec + msec);
    tv = tmp;
}


int main (void)
{
    //int arr[SZ];
    //int arr2[SZ];

    std::vector<int> arr(SZ);

    forl(i, 0, SZ) {
        arr[i] = rand() % SZ*10;
    }
    //memcpy(arr2,arr,sizeof(arr2));
    std::vector<int> arr2(arr);

    printf("unsorted:\n");
    //forl(i, 0, SZ) { printf("%d %d\n",i, arr[i]); }

    swapcounter = 0;
    printf("doing heap insert\n");
    timediff("starting timer");
    forl(i, 1, SZ) { heap_insert(arr, SZ, i); }
    timediff("using heap_insert()");
    printf("swapcounter=%d\n",swapcounter);
    printf("sorted1:\n");
    //forl(i, 0, SZ) { printf("%d %d\n",i, arr[i]); }
    heap_verify(arr, SZ);

    //best to start at the end, and substitute with the parent as you go
    swapcounter = 0;
    //for each item in the left half, percolate to right to get heap
    timediff("starting timer");
    heapify(arr2, SZ);
    timediff("using heapify()");
    printf("swapcounter=%d\n",swapcounter);
    printf("sorted2:\n");
    //forl(i, 0, SZ) { printf("%d %d\n",i, arr2[i]); }
    heap_verify(arr2, SZ);

    return 0;
}
