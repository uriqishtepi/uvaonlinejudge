/* lsd radix sort
 * utilizes counting sort to sort on the rightmost column first, 
 * going leftwards until the first column. 
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

#define R 256 //radix 2^8

void counting_sort(const std::vector<std::string> & strings, std::vector<int> & v, int N, int l) 
{
    //do counting sort on the l-th column
    int counts[R + 1] = {0};

    for(int i = 0; i < N; i++) {
        int offset = v[i]; //offset of the ith string
        const std::string & currstr = strings[offset];
        counts[(currstr.at(l)) + 1]++;
        out("%d) strings[%d]=%s  counts[%c + 1]=%d \n",i, offset, strings[offset].c_str(), currstr.at(l),  counts[(currstr.at(l)) + 1]);
    }

    //accumulate the counts
    for(int i = 0; i < R; i++) {
        if(counts[i+1] > 0)
            out("counts[%c]=%d+%d\n",i, counts[i + 1], counts[i]);
        counts[i + 1] += counts[i];
    }

    std::vector<int> aux(N); //map to sorted strings
    for(int i = 0; i < N; i++) {
        int offset = v[i]; //offset of the ith string
        const std::string & currstr = strings[offset];
        int newpos = counts[currstr.at(l)]++; //++ for next occurnc of this char
        aux[newpos] = v[i];
        out("aux[%d]=%d\n",counts[currstr.at(l)], v[i]);
    }

    for(int i = 0; i < N; i++) {
        v[i] = aux[i];
    }
}

//for every column do counting sort on the column
//and update the v[] which is the mapping to the real strings
//since we dont want to move strings around, we oonly update the mapping
//v[] will have the final sorted order with v[0] being the first sorted string
//
//counting sort works by first getting the counts of each letter in the column
//then accumulating the counts so we have v[R] to be N at the end
void lsd_radix_sort(const std::vector<std::string> & strings, int N)
{
  std::vector<int> v(N); //map to sorted strings

  for(int i = 0; i < N; i++)
      v[i] = i; //all v's entries point to initial respective locations 

  for(int i = 0; i < N; i++) {
      out("%s\n", strings[v[i]].c_str());
  }

  /* we assume that the length of the strings is the same, 
   * we start from the least significant place (right) and move to the left 
   */
  for(int l = strings.front().length() - 1; l >= 0; l--) {
      counting_sort(strings, v, N, l);
  

      out("l=%d\n",l);
      for(int i = 0; i < N; i++) {
          out("strings[%d]=%s\n", v[i], strings[v[i]].c_str());
      }
  }
  
  for(int i = 0; i < N; i++) {
      std::cout << strings[v[i]] << std::endl;
  }

}


int main(void)
{
  out("starting ...\n");
  std::cout << " LSD radix sort " << std::endl;

  std::vector<std::string> strings;
  
  int N = 0;
  scanf("%d",&N);

  //start from 
  for(int i = 0; i < N; i++) {
      std::string str;
      std::cin >> str;
      strings.push_back(str);
  }

  lsd_radix_sort(strings, N);


  return 0;
}
