/* 
 * from a string find the rotation that is the smallest lexicographically
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
#include <sys/time.h>

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


#define R 256


//comparator for the sorting of the indices
struct rotsorter {
    rotsorter(const uint8_t * buff, int len) : m_s(buff), m_length(len) {}
    bool operator()(int o1, int o2) {
        //return memcmp(m_s, sp.m_s, BUFFERSIZE) < 0;
        const uint8_t * p1 = &m_s[o1];
        const uint8_t * p2 = &m_s[o2];
        const uint8_t * end = &m_s[m_length]; //one past last 

        for(int i = 0; i < m_length; i++) {
            if(*p1 < *p2)
                return true;
            if (*p1 > *p2)
                return false;
            //otherwise continue comparing
            if (p1 >= end)  p1 = m_s;
            else p1++;
            if (p2 >= end)  p2 = m_s;
            else p2++;
        }
        return false; //equal, so return false
    }

    const uint8_t * m_s;
    int m_length;
};

struct rotsorter2 {
    rotsorter2(const uint8_t * buff, int len) : m_s(buff), m_length(len) {}
    bool operator()(int o1, int o2) {
        //return memcmp(m_s, sp.m_s, BUFFERSIZE) < 0;
        const uint8_t * p1 = &m_s[o1];
        const uint8_t * p2 = &m_s[o2];
        const uint8_t * ahead = p1;
        const uint8_t * behind = p2;
        const uint8_t * end = &m_s[m_length]; //one past last 
        bool p1ahead = true;
        int counter = 0;

        if(p1 < p2) {
            ahead = p2;
            behind = p1;
            p1ahead = false;
        }

        while( ahead < end && counter < m_length) {
            if(*ahead < *behind)
                return p1ahead;
            if(*ahead > *behind)
                return !p1ahead;
            ahead++;
            behind++;
            counter++;
        }
        ahead = m_s;
        while( behind < end && counter < m_length) {
            if(*ahead < *behind)
                return p1ahead;
            if(*ahead > *behind)
                return !p1ahead;
            ahead++;
            behind++;
            counter++;
        }
        behind = m_s;
        while(counter < m_length) {
            if(*ahead < *behind)
                return p1ahead;
            if(*ahead > *behind)
                return !p1ahead;
            ahead++;
            behind++;
            counter++;
        }
        return false; //equal, so return false
    }

    const uint8_t * m_s;
    int m_length;
};

//this is even worse
struct rotsorter3 {
    rotsorter3(const uint8_t * buff, int len) : m_s(buff), m_length(len) {}
    bool operator()(int o1, int o2) {
        //return memcmp(m_s, sp.m_s, BUFFERSIZE) < 0;
        for(int i = 0; i < m_length; i++) {
            uint8_t c1 = m_s[o1 % m_length];
            uint8_t c2 = m_s[o2 % m_length];
            if(c1 < c2)
                return true;
            if(c1 > c2)
                return false;
            o1++;
            o2++;
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
//a circular array so we need to wrap around the string in question
//and so s[x + i] needs to be modded
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


//
//perform counting sort to get the order of the letters in the string
//such order is needed to compute the inverse transform
void counting_sort_other(uint8_t * str, int len, std::vector<int> &v) 
{
    int counts[R+1] = {0};
    //get counts
    for(int i = 0; i < len; i++) {
        counts[str[i]]++;
    }

    //accumulate
    for(int i = 0; i < R; i++) {
        counts[i+1]+= counts[i];
    }

    v.resize(len);
    for(int i = 0; i < len; i++) {
        int newpos = counts[str[i]]++;
        v[newpos] = i;
    }

}


//this is counting sort for radix msd sort, needs to return the counts
void counting_sort(const char * string, std::vector<int> &v, 
        std::vector<int> &aux, int start, int end, int chrindx, int counts[])
{
    //do counting sort on the l-th column
    for(int i = start; i < end; i++) {
        int offset = v[i]; //offset of the ith string
        const char c = string[offset + chrindx];
        counts[c + 2]++;
        out("%d) strings[%d]=%s  counts[%c + 1]=%d \n",i, offset, &string[offset], string[offset+chrindx], counts[string[offset+chrindx] + 1]);
    }

    //accumulate the counts
    for(int i = 0; i < R+1; i++) {
        if(counts[i+1] > 0)
            out("counts[%c]=%d+%d\n",i-1, counts[i + 1], counts[i]);
        counts[i + 1] += counts[i];
    }

    for(int i = start; i < end; i++) {
        int offset = v[i]; //offset of the ith string
        const char c = string[offset + chrindx];
        aux[counts[c + 1]++ ] = v[i];
        out("aux[%d]=%d\n", counts[c], v[i]);
    }

    out("chrindx=%d\n",chrindx);
    for(int i = start; i < end; i++) {
        v[i] = aux[i - start];
        out("%d) strings[%d]=%s\n", i, v[i], &string[v[i]]);
    }
}

//recursive call, first we count sort on the leftmost column,
//then we proceed to recursively sort the next column
//aux is passed so we dont reallocate every time the helper array
void msd_radix_sort(const char * string, std::vector<int> &v, std::vector<int> &aux, int start, int end, int chrindx)
{
    out("msd_radix_sort %d, %d, %d\n", start, end, chrindx);
    if(end - start < 2) return;
    /*
    if(end - start < 24) {
        insertion_sort(string, v, aux, start, end, chrindx);
        return;
    }
    */

    for(int i = start; i < end; i++) {
        out("h %s\n", &string[v[i]]);
    }

    int counts[R + 2] = {0};
    counting_sort(string, v, aux, start, end, chrindx, counts);

    for(int r = 0; r < R; r++) {
        if(counts[r+1] - counts[r] > 1) {
            msd_radix_sort(string, v, aux, start + counts[r], 
                    start + counts[r + 1], chrindx + 1);
        }
    }

    for(int i = start; i < end; i++) {
        out("s %s\n", &string[v[i]]);
    }

}


//use counting sort to get the first position sorted,
//then sort second based on the first, then col 3 and 4 based on first two,
//and so on, to get a N*logN solution
//
//
//first iteration of this use std::sort then see if couting sort can be faster
void msd_logn(const char * str, std::vector<int> &v, int start, int end, int chrindx, int len)
{
    for(int i = 0; i < len; i++) {
        v[i] = i;
    }
    
    
}

void timediff(const char * s) {
    static timeval tv;
    timeval tmp;

    gettimeofday(&tmp, NULL);
    int sec = (tmp.tv_sec - tv.tv_sec)*1000000;
    int msec = (tmp.tv_usec - tv.tv_usec);
    printf("%20.20s diff = %12dusec\n", s, sec + msec);
    tv = tmp;
    
}

int main(void)
{
  out("starting ...\n");
  std::cout << " Array of suffices " << std::endl;

  std::string s;
  std::cin >> s;
  //std::cout << " str = " << str << std::endl;
  
  int len = s.length();  
  std::vector<int> suffixes(len);
  
  for(int i = 0; i < len; i++) {
    suffixes[i] = i;
  }
  timediff("setting time");

  std::vector<int> copy1 = suffixes;
  rotsorter r((const uint8_t*) s.c_str(), len);
  std::sort(copy1.begin(), copy1.end(), r); //use std sort
  timediff("quicksort rot");

  out("\noffsets: \n");
  for(std::vector<int >::iterator it = copy1.begin(); it !=copy1.end(); it++)
    out("%d ",*it);

  out("\nsorted strings: \n");
  for(std::vector<int >::iterator it = copy1.begin(); it !=copy1.end(); it++)
    out("%s\n",&s[*it]);
  timediff("reset ");



  {
  std::vector<int> copy2 = suffixes;
  rotsorter2 r2((const uint8_t*) s.c_str(), len);
  std::sort(copy2.begin(), copy2.end(), r2); //use std sort
  timediff("quicksort rot2");

  out("\nsorted strings: \n");
  for(std::vector<int >::iterator it = copy2.begin(); it !=copy2.end(); it++)
    out("%s\n",&s[*it]);
  timediff("reset ");
  assert(copy1 == copy2 && "sorted results differ");
  }

  {
  std::vector<int> copy = suffixes;
  rotsorter3 r3((const uint8_t*) s.c_str(), len);
  std::sort(copy.begin(), copy.end(), r3); //use std sort
  timediff("quicksort rot3");

  out("\nsorted strings: \n");
  for(std::vector<int >::iterator it = copy.begin(); it !=copy.end(); it++)
    out("%s\n",&s[*it]);
  timediff("reset ");
  assert(copy1 == copy && "sorted results differ");
  }

  {
  std::vector<int> copy3 = suffixes;
  threeway_quicksort(s.c_str(), copy3, 0, len, 0, len);
  timediff("three way qsort");

  out("\nsorted strings: \n");
  for(std::vector<int >::iterator it = copy3.begin(); it !=copy3.end(); it++)
    out("%s\n",&s[*it]);
  timediff("reset ");
  assert(copy1 == copy3 && "sorted results differ");
  }

  
  {
  std::vector<int> copy4 = suffixes;
  std::vector<int> aux = suffixes;
  msd_radix_sort(s.c_str(), copy4, aux, 0, len, 0);
  timediff("msd_radix_sort");
  
  out("\noffsets: \n");
  for(std::vector<int >::iterator it = copy4.begin(); it !=copy4.end(); it++)
    out("%d ",*it);

  out("\nsorted strings: \n");
  out("\nsorted strings: \n");
  for(std::vector<int >::iterator it = copy4.begin(); it !=copy4.end(); it++)
    out("%s\n",&s[*it]);
  /*
  for(std::vector<int >::iterator it = copy4.begin(); it !=copy4.end(); it++) {
      for(int i = 0 ; i < len; i++)
        out("%c",charat(s.c_str(), *it, i, len));
      out("\n");
  }
  */

  timediff("reset ");
  assert(copy1 == copy4 && "sorted results differ");
  }



  return 0;
}
