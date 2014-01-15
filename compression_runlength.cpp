/* 
 * Encode the subsequent runs of zeros and of ones
 * so 16 consecutive 1111111111111111 would correspond to 8bit 16: 00010000
 * alternate num of ones with num of zeros, if no zeros put 0
 *
 * some good tests:
 * 00
 * FF
 * E0
 * 07
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

    unsigned char buf;
    char turn = 0x1; //start with ones turn
    int rem = 0; //will accumulate the remainder 
    int cnt = 0;
    unsigned char pat = 0; //need to accumulate here and write when cnt is 8

    while((cnt = read(fin, &buf, 1)) > 0) {
        print_byte(buf);
        cnt = buf;
        int sum = rem + cnt;
        out("rem=%d, cnt=%d, sum=%d\n turn:",rem, cnt, sum);
        print_byte(turn);

        if(rem > 0 && sum > 8) {

            //write the remaining of the byte from cnt
            for(int i = 0; i < (8-rem); i++) {
                pat <<= 1;
                pat |= turn;
                out("1pat=");
                print_byte(pat);
            }
            
            //write pattern and set cnt = sum - rem
            cnt = cnt - (8 - rem); //wrote 8 bytes
            out("1writing x=%d, turn=%d\n", pat, turn);
            write(fout, &pat, 1); 
            rem = 0;
            pat = 0;
        }

        //write out bytes full of ones or of zeros (whatever turn is)
        while(cnt >= 8) {
            out("consuming cnt=%d, sum=%d\n", cnt, sum);
            pat = - turn; //if turn is 0, pat is 0, else -1

            out("2writing x=%d, turn=%d\n", pat, turn);
            write(fout, &pat, 1);
            cnt -= 8;
            pat = 0;
        }
        //if anything remains, we need to write it to pat
        for(int i = 0; i < cnt; i++) {
            pat <<= 1;
            pat |= turn;
            out("2pat=");
            print_byte(pat);

        }

        turn = !turn; //next turn is flipped
        rem += cnt;
    }

    out("rem=%d, cnt=%d \n turn:",rem, cnt);
    print_byte(turn);
    if(rem > 0) {
        //write pattern and set cnt = sum - rem
        out("writing x=%d, turn=%d\n", pat, turn);
        write(fout, &pat, 1); 
    }
}


//FFFF FF00 translates to 32+16, 16
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

    unsigned char buf;
    char turn = 0x1; //start with ones turn
    int count = 0;
    while(read(fin, &buf, 1) > 0) 
    {
        unsigned short mask = 1<<7;
        print_byte(buf);
        while(mask > 0) {
            out("mask=%d, turn=%d\n",mask, turn);
            out("turn %d and bit %d, count=%d\n", turn, bit(buf, mask), count);
            if(turn == bit(buf, mask)) { //if turn is same as bit
                count++;
            }
            else { //turn is different from bit, so write out the count of turn
                while(count > 255) {
                    char eight = 0x8;
                    char none = 0x0;
                    write(fout, &eight, 1); //255 of type turn (ex ones)
                    write(fout, &none, 1); //0 of the other type (ex zeros)
                    count-=255;
                    out("while: count=%d\n",count);
                }

                out("last same: writing count=%d turn=%d\n",count, turn);
                write(fout, &count,1);//finally write the count which is < 255
                turn ^= 0x1; //flip to next
                count = 1;
                out("resetting: count=%d turn=%d\n",count, turn);
            }

            mask >>= 1;
        }
    }

    if(count > 0) {
        out("last last: writing count=%d turn=%d\n",count, turn);
        write(fout, &count,1);//finally write the count which is < 255
    }
    close(fin);
    close(fout);
}

int main(int argc, char**argv)
{
    out("starting ... \n");
    //If you want grep, uncomment next line: 
    //grep(argc, argv); exit(1);

    std::cerr << " Runlength coding " << std::endl;
    for(int i = 0; i < 8; i++)
        assert(bit(0xFF,0x1 << i) == 1 && "err 1");

    encode(argc, argv);
    decode(argc, argv);
    return 0;
}
