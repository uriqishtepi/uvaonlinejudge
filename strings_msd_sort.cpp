/* msd radix sort
 * utilizes counting sort to sort on the leftmost column first, 
 * then for each subgroup, calls recursively msdsort 
 * with next letter position
 * going rightwards until the first column. 
 * since it can be expensive to sort a few very long strings,
 * it is commonly optimized to do insertion sort if less than
 * a certain number of items in subgroup.
 */

#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

#define R  256 //radix 2^8


inline
char charat(const std::string & s, int i)
{
    if(i < s.size()) return s.at(i);
    else return -1;
}


inline void swap(int & a, int & b) {
    int tmp = b;
    b = a;
    a = tmp;
}


void insertion_sort(const std::vector<std::string> & strings, std::vector<int> &v, std::vector<int> &aux, int start, int end, int chrindx)
{
    for(int i = start; i < end - 1; i++){
        for(int j = i; j < end; j++) {
            if( strcmp(&strings[v[i]][chrindx], &strings[v[j]][chrindx]) > 0) 
                swap(v[i],v[j]);
        }
    }
}


void counting_sort(const std::vector<std::string> & strings, std::vector<int> &v, std::vector<int> &aux, int start, int end, int chrindx, int counts[])
{
    //do counting sort on the l-th column
    for(int i = start; i < end; i++) {
        int offset = v[i]; //offset of the ith string
        const std::string & currstr = strings[offset];
        counts[charat(currstr,chrindx) + 2]++;
        out("%d) strings[%d]=%s  counts[%c + 1]=%d \n",i, offset, strings[offset].c_str(), charat(currstr,chrindx),  counts[charat(currstr,chrindx) + 1]);
    }

    //accumulate the counts
    for(int i = 0; i < R+1; i++) {
        if(counts[i+1] > 0)
            out("counts[%c]=%d+%d\n",i-1, counts[i + 1], counts[i]);
        counts[i + 1] += counts[i];
    }

    for(int i = start; i < end; i++) {
        int offset = v[i]; //offset of the ith string
        const std::string & currstr = strings[offset];
        aux[counts[charat(currstr,chrindx) + 1]++ ] = v[i];
        out("aux[%d]=%d\n", start + counts[charat(currstr,chrindx)], v[i]);
    }

    out("chrindx=%d\n",chrindx);
    for(int i = start; i < end; i++) {
        v[i] = aux[i - start];
        out("%d) strings[%d]=%s\n", i, v[i], strings[v[i]].c_str());
    }


}

//recursive call, first we count sort on the leftmost column,
//then we proceed to recursively sort the next column
//aux is passed so we dont reallocate every time the helper array
void msd_radix_sort(const std::vector<std::string> & strings, std::vector<int> &v, std::vector<int> &aux, int start, int end, int chrindx)
{
    out("msd_radix_sort %d, %d, %d\n", start, end, chrindx);
    if(end - start < 2) return;
    if(end - start < 24) {
        insertion_sort(strings, v, aux, start, end, chrindx);
        return;
    }

    for(int i = start; i < end; i++) {
        out("h %s\n", strings[v[i]].c_str());
    }

    int counts[R + 1] = {0};
    counting_sort(strings, v, aux, start, end, chrindx, counts);

    for(int r = 0; r < R; r++) {
        if(counts[r+1] - counts[r] > 1) {
            msd_radix_sort(strings, v, aux, start + counts[r], 
                    start + counts[r + 1], chrindx + 1);
        }
    }
}



int main(void)
{
  out("starting ...\n");
  std::cout << " MSD radix sort " << std::endl;

  std::vector<std::string> strings;
  
  int N = 0;

  //start from 
  char str[256] = {0};
  while( scanf("%s",&str) != EOF ) {
      strings.push_back(str);
  }
  N = strings.size();

  std::vector<int> v(N); //map to sorted strings
  for(int i = 0; i < N; i++)
      v[i] = i; //all v's entries point to initial respective locations 

  std::vector<int> aux(N); //map to sorted strings
  msd_radix_sort(strings, v, aux, 0, N, 0);

  out("SORTED strings\n");
  for(int i = 0; i < N; i++) {
      std::cout << strings[v[i]] << std::endl;
  }

  return 0;
}
