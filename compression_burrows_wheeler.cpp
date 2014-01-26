/* 
 * Burrows-Wheeler
 * Transform to get a modified version of the input string:
 * form all the rotations, sort them, then take the last column
 * of the NxN matrix and that's the transformed msg.
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
 */
#include <stack>
#include <queue>
#include <assert.h>
#include <vector>
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


#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


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

#define BUFFERSIZE  1024
#define R 256 //radix 2^8

struct strpair {
    strpair(const uint8_t * s, int value) : m_s(s), m_value(value) {} 
    bool operator <(const strpair & sp) const {
        return memcmp(m_s, sp.m_s, BUFFERSIZE) < 0;
    }
    const uint8_t * m_s;
    int m_value;
};

typedef std::set<strpair, std::less<strpair> > SP;

//inverse transform is ingenuous:
//sort the letters in the string, after assigning a node id
//the mapping node id to what it was, is mapping of sorted follows unsorted
//in the original string, thus we can do a simple search (DFS style) to get from
//the first to the last node 
//we can use radix sort, or counting sort and it will get us linear time sorting
void inverse_transform(uint8_t * s, int len, int firstpos)
{
    char counts[R+1] = {0};

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


    std::vector<int> from(len);
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

    for(int i = 0; i < len; i++) {
        //std::cout << values[i];
        out("%d: value %c from %d to %d\n", i, values[i], from[i], to[i]);
    }
    std::cout << std::endl;

    //values contain the sorted output, from contains positin each letter came from
    //we start from $, find the from until $ again
    //mark $ will now be the first in the values, so we start from from[0]
    int next = firstpos;  //start at $ mark
    do {
        next = from[next];  //get the next and print it
        std::cout << s[next];
    } while (next != firstpos);  //until we dont reach firstpos

    std::cout << std::endl;
}


//we can use radix sort to sort the substrings so we get linear time sorting
//return the position of the zeroth character
int transform(const uint8_t * buffer, int len, uint8_t * ret)
{
    SP postfixes;
    int initialpos = 0;

    for(int i = 0; i < len; i++) {
        out("%.2d: %*.s %*.*s \n",i ,i," ", i, len+1, buffer + i);
        strpair sp(buffer + i, i);
        postfixes.insert(sp);
    }

    int index = 0;
    for(SP::iterator it = postfixes.begin(); it != postfixes.end(); it++)
    {
        out("%c %.*s : %d \n", it->m_s[len-1], len, it->m_s, it->m_value);
        //printf("%c\n",it->m_s[len], it->m_value);
        if(it->m_value == 0) { 
            out("offset %d\n", index);
            initialpos = index;
        }
        ret[index++] = it->m_s[len-1];
    }
    return initialpos;
}


int main(int argc, char**argv)
{
    out("starting ... Burrows - Wheeler transform %d\n", argc);

    std::fstream in;
    if(argc > 1)
        in.open(argv[1], std::ifstream::in); 
    std::istream & fin = in.is_open() ? in : std::cin;

    uint8_t c = 0;
    uint8_t buffer[3 * BUFFERSIZE]; //TODO chabnge to 2
    uint8_t res[BUFFERSIZE];
    int count = 0;
    int offset = 0;

    while(fin >> c) {
        buffer[count++] = c;
        out("c=%x ",c);
        if(count >= BUFFERSIZE - 1) {
            memcpy(buffer + BUFFERSIZE, buffer, count);
            offset = transform(buffer, count, res);
            break;
            count = 0; 
        }
    }
    if(count > 0) {
        memcpy(buffer + count, buffer, count);
        offset = transform(buffer, count, res);
    }

    std::cout << "'" ;
    for(int i = 0; i < count; i++)
        std::cout << res[i];
    std::cout << "'" ;
    std::cout << std::endl;

    inverse_transform(res, count, offset);
    return 0;
}
