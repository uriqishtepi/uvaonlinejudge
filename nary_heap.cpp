/* This is an example of a two way heap how to insert into it 
 * and how to turn an array with data into a min heap.
 *
 * It seems that at about 4 way heap you get most gains.
 */
#include <vector>
#include <algorithm>
#include <functional>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define SZ (22222232-1)
#define WAYS 4

int swapcounter = 0;

inline void swap (int &a, int &b)
{
    int t = b;
    b = a;
    a = t;
    swapcounter++;
}

#define parent(a) ((a-1)/WAYS)
#define left(a) (WAYS*a + 1) //right is left + 1
//get in minchild the offset of the smallest child of el
//if no children, will not change minchild
inline void getMinChild(std::vector<int> &arr, int el, int & minchild, int sz)
{
    int l = left(el);
    int n;
    if(l >= sz) 
        return;
    minchild = l;
    //printf("left of %d is %d\n", el, l);
    for(int i=1; (i < WAYS) && ((n=l + i) < sz); i++) {
        //printf("right of %d is %d\n", el, l+i);
        if(arr[minchild] > arr[n])
            minchild = n;
    }
    //printf("minchild of %d is %d\n", el, minchild);
}


//percolate from el up to sz to have min heap property
//this way of building the heap takes O(n) (not nlogn)
inline void siftDown(std::vector<int> &arr, int el, int sz)
{
    int minchild = -1; //min child of el, if it exists
    getMinChild(arr, el, minchild, sz);

    while(el < minchild && arr[el] > arr[minchild]) 
    {
        swap(arr[el], arr[minchild]);
        el = minchild;
        getMinChild(arr, el, minchild, sz);
    } 
}

void heapify(std::vector<int> &arr)
{
    //start at last parent element down to 0, perform siftDown
    //last element is (SZ-1), and its parent is
    int sz = arr.size(); 
    for(int i = parent(arr.size() - 1); i >= 0; i--) { siftDown(arr, i, sz); }
}


//assume we want a MIN heap 
void siftUp(std::vector<int> &arr, int nodeOffset)
{
    while(nodeOffset > 0) {
        int p = (nodeOffset-1) / WAYS;
        if(arr[p] <= arr[nodeOffset]) 
            break; //nothing to do
        swap(arr[p], arr[nodeOffset]);
        nodeOffset = p;
    }
}

//insert new element into the heap
void heap_insert(std::vector<int> &arr, int newel)
{
    arr.push_back(newel);
    siftUp(arr, arr.size() - 1);
}

void heap_verify (std::vector<int> &arr)
{
    int i = arr.size() - 1;
    while(i > 0) {
        int p = parent(i);
        if(arr[p] > arr[i]) {
            printf("arr[%d] (%d) > arr[%d] (%d)\n", p, arr[p], i, arr[i]);
            forl(j, 0, i+1) { printf("%d %d\n",j, arr[j]); }
            break;
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
    //if i were to sort, then heapify would be log(n) times faster
    //std::sort(arr.begin(), arr.end(), std::greater<int>());
    //memcpy(arr2,arr,sizeof(arr2));
    std::vector<int> arr2(arr);

    printf("arr size %d %d\n", arr.size(), arr2.size());
    //printf("unsorted:\n"); forl(i, 0, SZ) { printf("%d %d\n",i, arr[i]); }

    swapcounter = 0;
    printf("doing heap insert\n");
    timediff("starting timer");
    forl(i, 1, SZ) { siftUp(arr, i); }
    timediff("using heap_insert()");
    printf("swapcounter=%d\n",swapcounter);
    printf("check arr1\n");
    //forl(i, 0, SZ) { printf("%d %d\n",i, arr[i]); }
    heap_verify(arr);

    //best to start at the end, and substitute with the parent as you go
    swapcounter = 0;
    //for each item in the left half, percolate to right to get heap
    timediff("starting timer");
    heapify(arr2);
    timediff("using heapify()");
    printf("swapcounter=%d\n",swapcounter);
    printf("check arr 2\n");
    //forl(i, 0, SZ) { printf("%d %d\n",i, arr2[i]); }
    heap_verify(arr2);

    return 0;
}
