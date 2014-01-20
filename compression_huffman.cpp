/* 
 * With huffman, we create a tree structure with frequencies of the 
 * nodes in decreasing order (going down the tree)
 * this binary trie, is then written to the output, and red from the decoder
 * and rebuilt, and used to decode the rest of the encoded message.
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



struct node { 
    node(char c) : m_c(c), m_left(NULL), m_right(NULL) {}
    node(char c, node * left,  node * right) : m_c(c), m_left(left), m_right(right) {}
    ~node() { if(m_left) delete  m_left; if(m_right) delete m_right; }
    char m_c;
    node * m_left;
    node * m_right;
};


void cleanup_tree(node * nptr) { delete nptr; }


struct ByteReader {
    ByteReader(uint8_t * addr) : m_addr(addr), m_offset(0), m_byteLoc(8) {}

    uint8_t readBit() { 
        uint8_t ret = (m_addr[m_offset] >> (--m_byteLoc)) & 0x1; 
        out("readBit: m_offset=%d m_byteLoc=%d ret=%x\n", m_offset, m_byteLoc, ret);
        if(m_byteLoc <= 0) {
            m_byteLoc = 8; 
            m_offset++;
            out("readBit next offset addr[offset]=");
            print_byte(m_addr[m_offset]);
        }
        return ret; 
    }
    uint8_t readByte() {
        //out("orig part readByte: %x\n", m_addr[m_offset]);
        uint8_t ret = m_addr[m_offset] << (8 - m_byteLoc); 
        //out("ret part readByte: %x\n", ret);
        m_offset++; 
        out("readBit next offset addr[offset]=");
        print_byte(m_addr[m_offset]);
        //out("other part readByte: %x\n", (m_addr[m_offset] >> m_byteLoc));
        ret |= (m_addr[m_offset] >> m_byteLoc);
        out("readByte: %x\n", ret);
        return ret;
    }

    int readInt() {
        int val = 0;
        ((uint8_t*)&val)[0] = readByte();
        ((uint8_t*)&val)[1] = readByte();
        ((uint8_t*)&val)[2] = readByte();
        ((uint8_t*)&val)[3] = readByte();
        return val;
    }

    uint8_t * m_addr;
    int m_offset; //offset in m_addr
    char m_byteLoc; //offset in last byte
};



//every leaf node makes the search stop
//for non leaf nodes, we populate the subtree
node * build_tree(ByteReader & br)
{
    if(br.readBit()) { //this is a leaf node, populate with byte
        char c = br.readByte();
        out("\nleaf: '%c'\n", c);
        return new node(c);
    }

    out("{\n");
    node *left = build_tree(br);
    out("}\n");
    out("{\n");
    node *right = build_tree(br);
    out("}\n");

    return new node('\0',left, right);
}


//do the search on the tree
//follow the paths according to the bits read
char get_char(node * decoding_trie, ByteReader & br) 
{
    static node * last = decoding_trie;
    
    while(last) { //while node of tree
        uint8_t p = br.readBit();
        if(p) { //on bit 1 search right of last
            last = last->m_right;
        }
        else //on bit 0 search to the left
            last = last->m_left;

        if(last->m_c != '\0') {
            char c = last->m_c;
            out("\nfound on leaf: '%c'\n", c);
            last = decoding_trie; //start search from the root
            return c;
        }
    }
}


class ByteWriter {
public:
    ByteWriter(int fout) : m_fout(fout), m_count(0), m_byte(0) {}

    //bit to write, count of bits
    void writeByte(uint8_t p, uint8_t ncnt) {
        out("writeByte: %x ncnt=%d m_count=%d\n", p, ncnt, m_count);
        if(ncnt + m_count > 8) { //copy 8 - m_count, then write m_byte
            for(int i = 0; i < 8 - m_count; i++, ncnt--) {
                m_byte <<= 1;
                m_byte |= p & 0x1; //just in case p contains crap
            }
            writeOut();

            m_count = 0;
            m_byte = 0;
        }
        for(;ncnt > 8; ncnt -= 8, m_byte = 0) { //write 8 bits p at a time
            m_byte = -(p & 0x1); //FF if 1, 0 if 0
            writeOut();
        }
        for(int i = 0; i < ncnt; i++) {
            m_byte <<= 1;
            m_byte |= p & 0x1; //just in case p contains crap
            m_count++;
        }
    }
    inline void writeBit(uint8_t p) { writeByte(p, 1); }
    void writeByte(uint8_t p) {
        out("writeByte: %x\n", p);
        for(int i = 7; i >= 0; i--)
            writeBit((p >> i) & 0x1);
    }
    inline void writeStringAsBits(const std::string & s) { 
        out("writeStringAsBits: ");
        for(std::string::const_iterator it = s.begin(); it != s.end(); ++it) {
            writeBit(*it - '0');
            out("%c", *it);
        }
        out("\n");
    }

    void writeInt(int val) {
        writeByte(((uint8_t*)&val)[0]);
        writeByte(((uint8_t*)&val)[1]);
        writeByte(((uint8_t*)&val)[2]);
        writeByte(((uint8_t*)&val)[3]);
    }

    ~ByteWriter(){
        //assert((m_count %8) == 0 && " this should always be mult of 8");
        flush();
    }
    void flush() {
        if(m_count > 0) writeOut();
    }

private:
    int m_fout;
    char dummy[256];
    uint8_t m_count;
    char dumm2y[256];
    uint8_t m_byte;

    void writeOut() {
        write(m_fout, &m_byte, 1); 
        out("write next offset m_byte=");
        print_byte(m_byte);
    }

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

void print_tree(node * nptr, std::string s)
{
    if(nptr == NULL) return;
    if(nptr->m_c != '\0') {
        out("'%c' '%s'\n", nptr->m_c, s.c_str());
        return; //done leaf node has no children so return
    }

    out("'%d' '%s'\n", nptr->m_c, s.c_str());
    print_tree(nptr->m_left, s+"0");
    print_tree(nptr->m_right, s+"1");
}


void traverse_tree(ByteWriter & bw, node * nptr, MCS & chmap, std::string s)
{
    if(nptr == NULL) return;
    if(nptr->m_c != '\0') {
        out("nptr c='%c' '%s'\n", nptr->m_c, s.c_str());
        chmap.insert(make_pair(nptr->m_c, s));
        //this is leaf node, write to fout (via bytewriter)
        out("traverse_tree: true\n");
        bw.writeBit(true);
        bw.writeByte(nptr->m_c);
        return; //done leaf node has no children so return
    }

    out("traverse_tree: false\n");
    bw.writeBit(false); //write as internal  node
    traverse_tree(bw, nptr->m_left, chmap, s+"0");
    traverse_tree(bw, nptr->m_right, chmap, s+"1");
}





void decode(int argc, char**argv)
{
    int fin = 0; //stdin
    int fout = 1; //stdout

    uint8_t *addr;
    struct stat sb;

    if(argc < 2) {
        return;
    }

    std::string s(argv[1]);
    s += ".out";

    if (stat(s.c_str(), &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

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

    ssize_t flsize = sb.st_size;
    addr = (uint8_t*) mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fin, 0);

    //for(int i =0; i < flsize; i++) { out("%c", addr[i]); } 
    //read tree first
    ByteReader br(addr);
    int outputlen = br.readInt();
    out("outputlen=%d\n", outputlen);

    node * decoding_trie = build_tree(br);

    for(int count = 0; count < outputlen; count++) {
        char c = get_char(decoding_trie, br);
        write(fout, &c, 1); 
    }

    cleanup_tree(decoding_trie);
    munmap(addr, sb.st_size);
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
        out("%c", addr[i]);
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
    bw.writeInt(flsize);
    out("flsize=%d\n", flsize);

    print_tree(mh.begin()->m_nptr, ""); 
    traverse_tree(bw, mh.begin()->m_nptr, chmap, ""); //will write to file
    out("Done traversing tree\n");

    for(int i = 0; i < flsize; i++) {
        bw.writeStringAsBits(chmap[addr[i]]); //write to file encoding of char
    } 

    cleanup_tree(mh.begin()->m_nptr);
    munmap(addr, sb.st_size);

    bw.flush(); //flush before closing file
    close(fin);
    close(fout);
}




int main(int argc, char**argv)
{
    out("starting ... Huffman coding\n");
    for(int i = 0; i < 8; i++)
        assert(bit(0xFF,0x1 << i) == 1 && "err 1");

    encode(argc, argv);
    decode(argc, argv);
    return 0;
}
