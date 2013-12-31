/* form an array of suffices */

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



int main(void)
{
  out("starting ...\n");
  std::cout << " Array of suffices " << std::endl;

  std::string str;
  std::cin >> str;
  int len = str.length();  
  std::vector<const char* > suffixes(len);
  
  for(int i = 0; i < len; i++) {
    suffixes[i] = i + str.c_str();
    printf("%2d: %s\n", i, suffixes[i]);
  }

  return 0;
}
