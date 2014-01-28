/* 
 * From all the rotations, choose the one that is lexicographically smallest
 * similar to burrow-wheeler, except that we dont get the last column of the
 * NxN matrix, but rather we get the actual smallest rotation
 */

#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif

#define BUFFERSIZE  1024
#define R 256 //radix 2^8

#define vi std::vector<int>
#define graphtp std::vector< vi > 


inline char bit(char buf, char mask)
{
    return !((buf & mask) == 0);
}
void print_byte(char b)
{
    for(int i = 7; i >= 0; i--)
        out("%d",(b>>i)&0x1);
    out("\n");
}



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




inline 
void do_run(uint8_t * buffer, int len, uint8_t * res) {
    out("\ndo run len=%d\n",len);
    int postfixes[BUFFERSIZE] = {0};
    int initialpos = 0;

    for(int i = 0; i < len; i++) {
        out("%.2d: %*.s %*.*s \n",i ,i," ", i, len, buffer + i);
        postfixes[i] = i;
    }

    rotsorter r(buffer, len);
    std::sort(postfixes, postfixes + len, r); //stable_sort is not needed

    out("\nsorted \n");
    for(int i = 0; i < len; i++) {
        out("%d: %d \n", i, postfixes[i]);
    }
    const uint8_t * p = &buffer[postfixes[0]];
    for(int i = 0; i < len; i++) {
        printf("%c",*p);
        p++;
        if (p - buffer >= len)  
            p = buffer;
    }
    printf("\n");
}


int main(int argc, char**argv)
{
    out("starting ... Burrows - Wheeler transform %d\n", argc);

    int fin = 0; //stdin
    if(argc > 1) {
        int rc = open(argv[1], O_RDONLY);
        if(rc == -1) {
            printf("Error opening file %s\n",argv[1]);
            exit(1);
        }
        fin = rc;
    }

    uint8_t c = 0;
    uint8_t buffer[BUFFERSIZE+1] = {0}; 
    uint8_t res[BUFFERSIZE+1] = {0};
    int count = 0;

    //tricky for larger than buffer, will have to memory map the file
    while(read(fin, &c, 1)) {
        out("c(%d)=%x ",count, c);
        buffer[count++] = c;
        if(count >= BUFFERSIZE - 1) {
            do_run(buffer, count, res);
            count = 0; 
        }
    }

    if(count > 0) {
        do_run(buffer, count, res);
    }

    return 0;
}
