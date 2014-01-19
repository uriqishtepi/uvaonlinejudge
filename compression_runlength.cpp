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

class ByteWriter {
public:
    ByteWriter(int fout) : m_fout(fout), m_count(0), m_byte(0) {}

    //bit to write, count of bits
    void writeByte(uint8_t p, uint8_t ncnt) {
        if(ncnt + m_count > 8) { //copy 8 - m_count, then write m_byte
            for(int i = 0; i < 8 - m_count; i++, ncnt--) {
                m_byte <<= 1;
                m_byte |= p & 0x1; //just in case p contains crap
            }
            write(m_fout, &m_byte, 1); 
            m_count = 0;
            m_byte = 0;
        }
        for(;ncnt > 8; ncnt -= 8, m_byte = 0) { //write 8 bits p at a time
            m_byte = -(p & 0x1); //FF if 1, 0 if 0
            write(m_fout, &m_byte, 1); 
        }
        for(int i = 0; i < ncnt; i++, m_count++) {
            m_byte <<= 1;
            m_byte |= p & 0x1; //just in case p contains crap
        }
    }

    ~ByteWriter(){
        assert((m_count %8) == 0 && " this should always be mult of 8");
        if(m_count > 0)
            write(m_fout, &m_byte, 1); 
    }

private:
    int m_fout;
    uint8_t m_count;
    uint8_t m_byte;
};


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
    uint8_t turn = 0x1; //start with ones turn
    ByteWriter bw(fout);

    while(read(fin, &buf, 1) > 0) {
        bw.writeByte(turn, buf);
        turn = !turn; //next turn is flipped
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

    uint8_t buf;
    uint8_t turn = 0x1; //start with ones turn
    int count = 0;
    while(read(fin, &buf, 1) > 0) 
    {
        unsigned short mask = 1<<7;
        out("buf=");
        print_byte(buf);
        while(mask > 0) {
            out("mask=%d, turn=%d\n",mask, turn);
            out("turn %d and bit %d, count=%d\n", turn, bit(buf, mask), count);
            if(turn == bit(buf, mask)) { //if turn is same as bit
                count++;
            }
            else { //turn is different from bit, so write out the count of turn
                while(count > 255) {
                    uint8_t eight = 0xff; //255 of the pattern
                    uint8_t none = 0x0;
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

    while(count > 255) {
        uint8_t eight = 0xff; //255 of the pattern
        uint8_t none = 0x0;
        write(fout, &eight, 1); //255 of type turn (ex ones)
        write(fout, &none, 1); //0 of the other type (ex zeros)
        count-=255;
        out("while: count=%d\n",count);
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
    std::cerr << " Runlength coding " << std::endl;
    for(int i = 0; i < 8; i++)
        assert(bit(0xFF,0x1 << i) == 1 && "err 1");

    encode(argc, argv);
    decode(argc, argv);
    return 0;
}
