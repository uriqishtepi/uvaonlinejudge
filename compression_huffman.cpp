/* 
 * With huffman, we create a tree structure with frequencies of the 
 * nodes in decreasing order (going down the tree)
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
#include <sys/mman.h> //for memory mapping


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

    while(read(fin, &buf, 1) > 0) {
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
    inline void writeBit(uint8_t p) { writeByte(p, 1); }
    inline void writeStringAsBits(const std::string & s) { 
        for(std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
            writeBit(*it - '0');
        }
    }

    ~ByteWriter(){
        //assert((m_count %8) == 0 && " this should always be mult of 8");
        if(m_count > 0)
            write(m_fout, &m_byte, 1); 
    }

private:
    int m_fout;
    uint8_t m_count;
    uint8_t m_byte;
};




struct node { 
    node(char c) : m_c(c), m_left(NULL), m_right(NULL) {}
    node(char c, node * left,  node * right) : m_c(c), m_left(left), m_right(right) {}
    char m_c;
    node * m_left;
    node * m_right;
};

struct symbol {
    symbol(int freq, char c) : m_freq(freq)
    {
        m_nptr = new node(c);
    }

    symbol(const symbol &s1, const symbol &s2) : m_freq(s1.m_freq + s2.m_freq)
    {
        m_nptr = new node('\0', s1.m_nptr, s2.m_nptr);
    }

    int m_freq;
    node * m_nptr;
    bool operator> (const symbol & s) const { return this->m_freq > s.m_freq; }
    bool operator< (const symbol & s) const { return this->m_freq < s.m_freq; }
};

typedef std::map <char, std::string> MCS;

void traverse_tree(ByteWriter bw, node * nptr, MCS & chmap, std::string s)
{
    if(nptr == NULL) return;
    if(nptr->m_c != '\0') {
        out("nptr c='%c' '%s'\n", nptr->m_c, s.c_str());
        chmap.insert(make_pair(nptr->m_c, s));
        //this is leaf node, write to fout (via bytewriter)
        bw.writeBit(true);
        bw.writeStringAsBits(s);
    }
    else
        bw.writeBit(false); //write as internal  node

    traverse_tree(bw, nptr->m_left, chmap, s+"0");
    traverse_tree(bw, nptr->m_right, chmap, s+"1");
}



//FFFF FF00 translates to 32+16, 16
//memory map the file so it is simpler to traverse it
//maybe a better way would have been to work with the file and read it
//chunk at a time 1MB into memory, process that piece, then repeat.
//this way can handle input from stdin as well as from file 
void encode(int argc, char**argv)
{
    int fin = 0; //stdin
    int fout = 1; //stdout
    char *addr;

    struct stat sb;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }


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

    ssize_t flsize = sb.st_size;
    addr = (char*) mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fin, 0);

    int freq[256] = {0};

    //first get the frequencies of the symbols
    for(int i =0; i < flsize; i++) {
        printf("%c", addr[i]);
        freq[addr[i]]++;
    }

    typedef std::multiset<symbol, std::less<symbol> > MSS;
    MSS mh;

    //build structure -- could use binary trie to store the symbols
    for(int i = 0; i < 256; i++) {
        if(freq[i]==0) continue;
        symbol s(freq[i],i);
        mh.insert(s);
    }

    for(MSS::iterator it = mh.begin(); it != mh.end(); ++it) {
        out("Freq=%d, c=%c\n", it->m_freq, it->m_nptr->m_c);
    }

    while(mh.size() > 1) { 
        symbol first = *mh.begin();
        mh.erase(mh.begin());
        symbol second = *mh.begin();
        mh.erase(mh.begin());
        symbol newnod(first , second);
        mh.insert(newnod);
    }
    
    //finally we are left with the tree in first.m_nptr
    MCS chmap;
    ByteWriter bw(fout);

    traverse_tree(bw, mh.begin()->m_nptr, chmap, ""); //will write to file

    for(int i =0; i < flsize; i++) {
        bw.writeStringAsBits(chmap[addr[i]]); //write to file encoding of char
    } 

    close(fin);
    close(fout);
}




int main(int argc, char**argv)
{
    out("starting ... \n");
    std::cerr << " Huffman coding " << std::endl;
    for(int i = 0; i < 8; i++)
        assert(bit(0xFF,0x1 << i) == 1 && "err 1");

    encode(argc, argv);
    //decode(argc, argv);
    return 0;
}
