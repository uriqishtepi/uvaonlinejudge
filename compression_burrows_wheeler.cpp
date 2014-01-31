/* 
 * Burrows-Wheeler
 * Transform to get a modified version of the input string:
 * form all the rotations, sort them, then take the last column
 * of the NxN matrix and that's the transformed msg.
 * Before i was using s + s to compute the rotations, but 
 * I switched to using modulus which may or may not be faster.
 *
 * The inverse transform is quite ingenuous, need to sort the 
 * string, remembering where the characters came from and then
 * follow the from list (like dfs) to find all the characters
 * in the original string.
 *
 * It works because when we sort the first column in the forward 
 * transform, and take the last column, when we sort the latter
 * and we note the froms, the froms denote the location where 
 * the original was, thus printing it, you get the original.
 *
 * There is an issue with repeating strings such as:
 *   abc
 *   abc
 * in decoding i just need to continue until reaching correct count
 *
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


struct strpair {
    strpair(const uint8_t * s, int offset, int len) : m_s(s), m_offset(offset), m_length(len) {} 
    bool operator < (const strpair & sp) const {
        //return memcmp(m_s, sp.m_s, BUFFERSIZE) < 0;
        for(int i = 0; i < m_length; i++) {
            int off1 = (m_offset + i) % m_length;
            int off2 = (sp.m_offset + i) % m_length;
            assert(off1 < m_length && off2 < m_length && "out of bounds");

            uint8_t a = m_s[off1];
            uint8_t b = m_s[off2];
            if(a < b)
                return true;
            if (a > b)
                return false;
            //otherwise continue comparing
        }
        return false; //equal, so return false
    }
    const uint8_t * m_s;
    int m_offset;
    int m_length;
};


//perform counting sort to get the order of the letters in the string
//such order is needed to compute the inverse transform
void counting_sort(uint8_t * s, int len, std::vector<int> &from) 
{
    int counts[R+1] = {0};

    //get the counts of the letters in the string
    for(int i = 0; i < len; i++) {
        counts[s[i] + 1]++;  //increase count for next char
        //out("%d: %c %d\n", i, s[i], counts[i]);
    }

    //accumulate counts so we find the positions of each letter, ex a goes to 0, etc.
    for(int i = 0; i < R; i++) {
        counts[i+1] += counts[i];
        //out("%d: %d\n", i, counts[i]);
    }

    from.resize(len);
    std::vector<int> to(len);
    std::vector<char> values(len);
    //assign the new order
    for(int i = 0; i < len; i++) {
        int newpos = counts[s[i]]++; //++ for the next occurrence of this char
        assert(newpos < len && newpos >= 0 && "newpos out of range");
        from[newpos] = i; //where newpos came from i
        to[i] = newpos;   //where i ended up in newpos
        values[newpos] = s[i];
    }

    //values contain the sorted output, from contains positin each letter came from
    for(int i = 0; i < len; i++) {
        out("%d: value %c from %d to %d\n", i, values[i], from[i], to[i]);
    }
}



//inverse transform is ingenuous:
//sort the letters in the string, after assigning a node id
//the mapping node id to what it was, is mapping of sorted follows unsorted
//in the original string, thus we can do a simple search (DFS style) to get from
//the first to the last node 
//we can use radix sort, or counting sort and it will get us linear time sorting
void inverse_transform(uint8_t * s, int len, int initialpos, uint8_t *res)
{
    std::vector<int> from;
    counting_sort(s, len, from);

    //we start from $, find the from until $ again
    //mark $ will now be the first in the values, so we start from from[0]
    int next = initialpos;  //start at $ mark
    
    for(int i = 0; i < len; i++) {
        next = from[next];  //get the next and print it
        out("%c", s[next]);
        res[i] = s[next];
    } 
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


//we can use radix sort to sort the substrings so we get linear time sorting
//return the position of the zeroth character
int transform(const uint8_t * buffer, int len, uint8_t * ret)
{
    out("\nlen=%d\n",len);
    int postfixes[BUFFERSIZE] = {0};
    int initialpos = 0;

    for(int i = 0; i < len; i++) {
        out("%.2d: %*.s %*.*s \n",i ,i," ", i, len, buffer + i);
        postfixes[i] = i;
    }

    rotsorter r(buffer, len);
    std::sort(postfixes, postfixes + len, r); //stable_sort is not needed

    out("\nsorted \n");
    int index = 0;
    for(int i = 0; i < len; i++) {
        //out("%.2d: %.*s : %c : %d \n", index, len, it->m_s, it->m_s[len-1], it->m_offset);
        int offset = postfixes[i];
        int last = (offset + len-1) % len;
        assert(last < len && " last is outside of buffer");

        out("%.2d: %c..%c %d \n", index, buffer[offset], buffer[last], offset);
        if(offset == 0) { 
            out("offset %d\n", index);
            initialpos = index;
        }
        ret[index++] = buffer[last];
    }
    out("\nend sorted\n");
    return initialpos;
}


/* write to file */
inline
void writeOut(int fout, uint8_t * buffer, int count)
{
    for(int i = 0; i < count; i++)
        write(fout, &buffer[i], sizeof(uint8_t));
}

void encode(int argc, char**argv)
{
    int fin = 0; //stdin
    int fout = 1; //stdout

    if(argc > 1) {
        int fin = open(argv[1], O_RDONLY);
        if(fin == -1) {
            printf("Error opening file %s\n",argv[1]);
            exit(1);
        }

        std::string s = std::string(argv[1]) + ".brw";
        int tmp2 = creat(s.c_str(), S_IRUSR | S_IWUSR);
        if(tmp2 < 0)
            printf("encode:Can not open file for writing %s\n", s.c_str());
        else
            fout = tmp2;
    }

    uint8_t c = 0;
    uint8_t buffer[BUFFERSIZE+1] = {0}; 
    uint8_t res[BUFFERSIZE+1] = {0};
    int count = 0;

    while((count = read(fin, buffer, BUFFERSIZE)) > 0) {
        int initialpos = transform(buffer, count, res);
        assert(initialpos >= 0 && initialpos < count && "bad initialpos");
        out("count=%d initialpos=%d\n", count, initialpos);
        write(fout, &initialpos, sizeof(initialpos));
        write(fout, res, count);
    }
}

void decode(int argc, char**argv)
{
    int fin = 0; //stdin
    int fout = 1; //stdout

    if(argc > 1) {
        fin = open(argv[1], O_RDONLY);
        if(fin == -1) {
            printf("Error opening file %s\n",argv[1]);
            exit(1);
        }
        std::string s = std::string(argv[1]) + ".out";
        int tmp2 = creat(s.c_str(), S_IRUSR | S_IWUSR);
        if(tmp2 < 0)
            printf("encode:Can not open file for writing %s\n", s.c_str());
        else
            fout = tmp2;
    }

    int bcounter = 0;
    uint8_t buffer[BUFFERSIZE+1] = {0}; 
    while(1) {
        int initialpos = 0;
        if(read(fin, &initialpos, sizeof(initialpos)) <= 0) {
            break;
        }
        out("initialpos=%d\n",initialpos);
        bcounter++;
        if(!(initialpos >= 0 && initialpos < BUFFERSIZE))
            printf("initialpos=%d bcounter=%d\n", initialpos, bcounter);
        assert(initialpos >= 0 && initialpos < BUFFERSIZE && "bad first byte in file");

        int count = read(fin, buffer, BUFFERSIZE);
        if(count <= 0) {
            break;
        }
        uint8_t res[BUFFERSIZE+1] = {0}; 
        inverse_transform(buffer, count, initialpos, res);
        write(fout, res, count);
    }
}



//this is only for testing, do the transform and the reverse transform
//and check that the final result is same as original buffer
inline void do_run(uint8_t * buffer, int count, int fout) {
    //forward transform
    uint8_t brw[BUFFERSIZE+1] = {0};
    int initialpos = transform(buffer, count, brw);

    //inverse transform
    uint8_t rev[BUFFERSIZE+1] = {0};
    inverse_transform(brw, count, initialpos, rev);
    write(fout, rev, count);
}

void do_both(int argc, char**argv)
{
    int fin = 0; //stdin
    int fout = 1; //stdout
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
    int count = 0;

    while(read(fin, &c, 1)) {
        out("c(%d)=%x ",count, c);
        buffer[count++] = c;
        if(count >= BUFFERSIZE - 1) {
            do_run(buffer, count, fout);
            count = 0; 
        }
    }

    if(count > 0) {
        do_run(buffer, count, fout);
    }
}


int main(int argc, char**argv)
{
    out("starting ... Burrows - Wheeler transform %d\n", argc);

    if(argc > 1)  {
        if(argv[1][0] == '-') {
            encode(argc-1, argv+1);
            return 0;
        }
        if(argv[1][0] == '+') {
            decode(argc-1, argv+1);
            return 0;
        }
    }

    do_both(argc, argv);
    

    return 0;
}
