/* 
 * Move to front is technique to move the most recently seen character 
 * at the front of a queue. 
 *
 */
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <string>

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


#define vi std::vector<int>
#define graphtp std::vector< vi > 

#define R 256

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


void decode(int argc, char**argv)
{
    int fin = 0; //stdin
    int fout = 1; //stdout

    if(argc < 2) {
        return;
    }

    std::string s(argv[1]);
    s += ".out";
    int tmp = open(s.c_str(), O_RDONLY);
    out("\nDecoding: %s\n",s.c_str());

    if(tmp < 0) {
        printf("decode:Can not open file %s\n", s.c_str());
        return;
    }
    else {
        fin = tmp;
        std::string s(argv[1]);
        s += ".verif";
        int tmp2 = creat(s.c_str(), S_IRUSR | S_IWUSR);
        if(tmp2 < 0) {
            printf("decode:Can not open file for writing %s\n", s.c_str());
            return;
        }
        else
            fout = tmp2;
    }

    uint8_t buf;
    uint8_t chmap[R] = {0};
    for(int i =0 ; i < R ; i++) {
        chmap[i] = i;
    }

    while(read(fin, &buf, 1) > 0) 
    {
        out("buf=");
        print_byte(buf);

        write(fout, &chmap[buf], 1); //0 of the other type (ex zeros)
        int tmp = chmap[buf];
        for(int i = buf; i != 0; i--) {
            chmap[i] = chmap[i-1];
        }
        chmap[0] = tmp;
    }

}


inline void swap(uint8_t & a, uint8_t & b)
{
    uint8_t tmp = b;
    b = a;
    a = tmp;
}


void encode(int argc, char**argv)
{
    int fin = 0; //stdin
    int fout = 1; //stdout

    if(argc > 1) {
        int tmp = open(argv[1], O_RDONLY);
        if(tmp < 0)
            printf("encode:Can not open file %s\n", argv[1]);
        else {
            fin = tmp;
            std::string s(argv[1]);
            s += ".out";
            int tmp2 = creat(s.c_str(), S_IRUSR | S_IWUSR);
            if(tmp2 < 0)
                printf("encode:Can not open file for writing %s\n", s.c_str());
            else
                fout = tmp2;
        }
    }

    uint8_t buf;
    uint8_t chmap[R] = {0};
    for(int i =0 ; i < R ; i++) {
        chmap[i] = i;
    }

    while(read(fin, &buf, 1) > 0) 
    {
        out("buf=");
        print_byte(buf);

        uint8_t prev = chmap[0]; //save prev
        for(int i = 0; i < R; i++) {
            out("i%d%d",i,chmap[i]);
            if(chmap[i] == buf) {
                swap(chmap[i], prev);
                write(fout, &i, 1); 
                chmap[0] = buf;
                out("found at %d\n",i);
                break;
            }
            swap(chmap[i], prev);
        }
    }
    /*
    0 1 2 ... a b c
    a 0 1 2.... b c
    b a 0 1 2.... c
    */

    close(fin);
    close(fout);
}

int main(int argc, char**argv)
{
    out("starting ... \n");
    std::cerr << " Move to front coding " << std::endl;

    for(int i = 0; i < 8; i++)
        assert(bit(0xFF,0x1 << i) == 1 && "err 1");

    encode(argc, argv);
    decode(argc, argv);
    return 0;
}
