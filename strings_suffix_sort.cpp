/* form an array of suffices 
 * then sort it using a functor
 * this utilizes the built in std::sort 
 * a potentially better method to use is three way quicksort which i
 * implemented at strings_substring_search.cpp where we find lcs as well
 */

#include <algorithm>
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
#include <stdint.h>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif



//comparator for the sorting of the indices
struct rotsorter {
    rotsorter(const uint8_t * buff, int len) : m_s(buff), m_length(len) {}
    bool operator()(int o1, int o2) {
        //return memcmp(m_s, sp.m_s, BUFFERSIZE) < 0;
        const uint8_t * p1 = &m_s[o1];
        const uint8_t * p2 = &m_s[o2];

        for(int i = 0; i < m_length; i++) {
            if(*p1 < *p2)
                return true;
            if (*p1 > *p2)
                return false;
            //otherwise continue comparing
            p1++;
            p2++;
            if (p1 - m_s >= m_length)  p1 = m_s;
            if (p2 - m_s >= m_length)  p2 = m_s;
        }
        return false; //equal, so return false
    }

    const uint8_t * m_s;
    int m_length;
};



inline void swap(int & a, int & b) {
    int tmp = b;
    b = a;
    a = tmp;
}


//differs from the one in three way sord .cpp because we are dealing with
//a circular array so we need to wrap around
inline char charat(const char * s, int x, int i, int len) {
    int offset = (x + i) % len;
    return s[offset];
}

void insertion_sort(const std::vector<char *> & strings, std::vector<int> &v, int start, int end, int chrindx)
{
    for(int i = start; i < end - 1; i++){
        for(int j = i; j < end; j++) {
            if( strcmp(&strings[v[i]][chrindx], &strings[v[j]][chrindx]) > 0) {
                swap(v[i], v[j]);
            }
        }
    }

}



//pick a pivot, maybe randomly
//put all points above, less than and equal to in separate places of v[i]
//NOTICE: that we dont swap characters or strings, but rather utilize
//a vector of indices which is the one that determines the sorted order 
void threeway_quicksort(const char * string, 
        std::vector<int> &v, int start, int end, int chrindx, int len)
{
    int n = end - start;
    if(n < 2) return;
    //if(n < 20) { insertion_sort(strings, v, start, end, chrindx); return; }

    //get the pivot
    int p = rand() % n;
    int c = charat(string, v[start+p],chrindx, len);

    int lessthan = start;
    int gtthan = end;
    int i = start;
    while(i < gtthan) {
        int lc = charat(string, v[i],chrindx, len);
        if(lc < c) {
            swap(v[lessthan], v[i]);
            lessthan++;
            i++;
        }
        else if(lc > c) {
            gtthan--;
            swap(v[gtthan], v[i]);
        }
        else { //equal
            i++;
        }
    }

    threeway_quicksort(string, v, start, lessthan, chrindx, len);
    if(c >=0) threeway_quicksort(string, v, lessthan, gtthan, chrindx + 1, len);
    threeway_quicksort(string, v, gtthan, end, chrindx, len);
}



int main(void)
{
  out("starting ...\n");
  std::cout << " Array of suffices " << std::endl;

  std::string str;
  std::cin >> str;
  int len = str.length();  
  std::vector<int> suffixes(len);
  
  for(int i = 0; i < len; i++) {
    suffixes[i] = i;
  }

  std::vector<int> copy1 = suffixes;
  rotsorter r((const uint8_t*) str.c_str(), len);
  std::sort(copy1.begin(), copy1.end(), r); //use std sort
  std::cout << "sorted " << std::endl;

  for(std::vector<int >::iterator it = copy1.begin(); it !=copy1.end(); it++)
     std::cout << *it << " " ;

  std::cout << "sorted 1" << std::endl;
  std::cout << &str[*copy1.begin()] << " " ;

  std::cout << "sorted 2" << std::endl;
  std::vector<int> copy2 = suffixes;
  threeway_quicksort(str.c_str(), copy2, 0, len, 0, len);
  std::cout << &str[*copy2.begin()] << " " ;

  return 0;
}
