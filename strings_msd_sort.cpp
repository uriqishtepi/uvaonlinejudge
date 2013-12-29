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

int R = 256; //radix 2^8


void msd_radix_sort(const std::vector<std::string> & strings, std::vector<int> &v, int start, int end, int chrindx)
{

  out("msd_radix_sort %d, %d, %d\n", start, end, chrindx);
  for(int i = start; i < end; i++) {
      out("%s\n", strings[v[i]].c_str());
  }

  
  //do counting sort on the l-th column
  int counts[256 + 1] = {0};

  for(int i = start; i < end; i++) {
      int offset = v[i]; //offset of the ith string
      const std::string & currstr = strings[offset];
      counts[(currstr.at(chrindx)) + 1]++;
      out("%d) strings[%d]=%s  counts[%c + 1]=%d \n",i, offset, strings[offset].c_str(), currstr.at(chrindx),  counts[(currstr.at(chrindx)) + 1]);
  }

  //accumulate the counts
  for(int i = 0; i < R; i++) {
      if(counts[i+1] > 0)
          out("counts[%c]=%d+%d\n",i, counts[i + 1], counts[i]);
      counts[i + 1] += counts[i];
  }

  std::vector<int> aux(end-start+1); //map to sorted strings
  for(int i = start; i < end; i++) {
      int offset = v[i]; //offset of the ith string
      const std::string & currstr = strings[offset];
      aux[start + counts[currstr.at(chrindx)]++ ] = v[i];
      out("aux[%d]=%d\n",start + counts[currstr.at(chrindx)], v[i]);
  }

  for(int i = start; i < end; i++) {
      v[i] = start+aux[i];
  }

  out("chrindx=%d\n",chrindx);

  for(int i = start; i < end; i++) {
      out("%d) strings[%d]=%s\n", i, v[i], strings[v[i]].c_str());
  }

  int last = start;
  for(int i = start+1; i < end; i++) {
      if(i - last > 1 && strings[v[last]].at(chrindx) != strings[v[i]].at(chrindx)
              && strings[v[last]].length() < chrindx && strings[v[i]].length() < chrindx) 
      {
          out("%c != %c\n", strings[v[last]].at(chrindx), strings[v[i]].at(chrindx));
          msd_radix_sort(strings, v, last, i, chrindx+1);
          last = i;
      }
  }
  

}


int main(void)
{
  out("starting ...\n");
  std::cout << " MSD radix sort " << std::endl;

  std::vector<std::string> strings;
  
  int N = 0;
  scanf("%d",&N);

  //start from 
  for(int i = 0; i < N; i++) {
      std::string str;
      std::cin >> str;
      strings.push_back(str);
  }

  std::vector<int> v(N); //map to sorted strings
  for(int i = 0; i < N; i++)
      v[i] = i; //all v's entries point to initial respective locations 

  msd_radix_sort(strings, v, 0, N, 0);

  out("SORTED strings\n");
  for(int i = 0; i < N; i++) {
      std::cout << strings[v[i]] << std::endl;
  }


  return 0;
}
