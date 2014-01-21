#include <assert.h>
#include <vector>
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


//counting sort works by first getting the counts of each letter in list 
//then accumulating the counts to determine where a certain char will go, ex
// for abbc counts will be a:1, b:2, c:1, d:0 ...
// accumulations will be   a:0, b:1, c:3, d:4 ... 
// which means that the first a will go at pos 0, first b will go in pos 1
// first c will go in pos 3 and so on.
//then find the proper locations for all the chars
void counting_sort(const std::string s)
{
    char counts[R+1] = {0};
    int len = s.size();

    //get the counts of the letters in the string
    for(int i = 0; i < len; i++) {
        counts[s[i] + 1]++;  //increase count for next char
        out("%d: %c %d\n", i, s[i], counts[i]);
    }

    //accumulate counts so we find the positions of each letter, ex a goes to 0, etc.
    for(int i = 0; i < R; i++) {
        counts[i+1] += counts[i];
        out("%d: %d\n", i, counts[i]);
    }

    std::vector<char> values(len);
    //assign the new order
    for(int i = 0; i < len; i++) {
        int newpos = counts[s[i]]++; //++ for the next occurrence of this char
        assert(newpos < len && newpos >= 0 && "newpos out of range");
        values[newpos] = s[i];
    }

    for(int i = 0; i < len; i++) 
        std::cout << values[i];
    std::cout << std::endl;
}


int main(void)
{
  out("starting ...\n");
  std::cout << " LSD radix sort " << std::endl;

  //start from 
  std::string str;
  while(std::cin >> str) {
      out ( "read %s with length %d\n", str.c_str(), str.size());
      counting_sort(str);
  }

  return 0;
}

