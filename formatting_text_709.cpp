#include<stdio.h>
#include<math.h>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<functional>
#include<vector>
#include<bitset>
#include<set>
#include<map>
#include <limits>
#include <string.h>
#include <iomanip>
#include <assert.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define vi std::vector<int>
#define vd std::vector<double>
#define mtsi std::multiset<int, std::greater<int> >
#define si std::set<int>
#define ss std::set<std::string>
#define mi std::map<int, int>
#define mmi std::multimap<int, int>
#define msi std::map<std::string, int>
#define INF 1<<30;

//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif



//similar to matrix but under the diagonal has all zeros
template <typename T>
struct uppertriang {
    uppertriang (unsigned int i) : _rows(i), _cols(i) { _m.resize(i + (i*(i-1))/2);}
    T & operator()(unsigned int i, unsigned int j) { 
        //out("(%d,%d)\n", i,j);
        assert(i<_rows);assert(j<_cols);
        if(i > j) return _res;
        else return _m[ i * _cols + j - ((i+1)*i)/2]; 
    }
    void print() 
    {
        unsigned int i = 0;
        unsigned int j = 0;
        for(typename std::vector<T>::const_iterator it = _m.begin();
                it != _m.end(); ++it) 
            std::cout << *it;
        std::cout << std::endl;

        for(typename std::vector<T>::const_iterator it = _m.begin();
                it != _m.end(); ++it) 
        {
            ++i;
            std::cout << *it;
            if(i < _cols) 
                std::cout <<"\t\t";
            else if(++j < _rows) {
                i = 0;
                std::cout <<"\n" ; 
                while(i++ < j)
                    std::cout <<"0\t\t";
                i--; //went one too far
            }
        }

        std::cout << std::endl; 
    }
    unsigned int rows() {return _rows;}
    unsigned int cols() {return _cols;}

    std::vector<T> _m; //matrix body
    unsigned int _rows;
    unsigned int _cols;
    T _res;
};



template <typename T>
struct matrix {
    matrix (unsigned int i, unsigned int j) : _rows(i), _cols(j) { _m.resize(i*j);}
    T& operator()(unsigned int i, unsigned int j) { assert(i<_rows);assert(j<_cols);
        return _m[ i * _cols + j]; }
    void print() 
    {
        int i = 0;
        for(typename std::vector<T>::const_iterator it = _m.begin();
                it != _m.end(); ++it)
            std::cout << std::setw(8) << *it << ((++i % _cols == 0) ? "\n" : "");

        std::cout << std::endl; 
    }
    unsigned int rows() {return _rows;}
    unsigned int cols() {return _cols;}

    std::vector<T> _m; //matrix body
    unsigned int _rows;
    unsigned int _cols;
};


int mypow(int x, int y)
{
    int res = 1;
    for(int i = 0; i < y; i++)
        res *= x;
    return res;
}

struct quatr {
    int val;
    int i;
    int k;
    int j;
};

std::ostream & operator << (std::ostream &os, const quatr &p) { 
    os << p.val <<","<< p.i <<","<< p.k <<","<< p.j ;
    return os;
}


void getMinPars(matrix< quatr > &O, std::vector<int> &res, int i, int j)
{
    //how things were picked
    //start from E(0,n) and find which was the min

    if(i==j) {
        out ( "one line [%d, %d]\n", i, j);
        res.push_back(j);
        return;
    }

    quatr el = O(i, j);
    assert((el.k == -1 && el.i <= el.j) || 
           (el.i <= el.k && el.k <= el.j));


    //left side, then print curr, then right side
    if(el.k == -1) { //from i to j fit in one line
        out ( "one line2 [%d, %d]\n", i, j);
        res.push_back(j);
    }
    else {
        //i,j came from i,k and k+i,j
        getMinPars(O, res, el.i,   el.k);
        getMinPars(O, res, el.k+1, el.j);
    }
}



//compute error given the length of the words, and the number of words
//this can be computed with formula, no need to iterate
int compute_err(int spaceLen, int nSpaces)
{
    assert(spaceLen >= 0);
    assert(nSpaces <= spaceLen);
    if(nSpaces == spaceLen) return 0;
    //distribute evenly the count - 1 spaces
    //spaces will fill from the last to the first: 
    //   1 1 1, then 1 1 2, then 1 2 2, then 2 2 2
    //that's really spaceLen = M - L, spaces[i] = spaceLen / nSpaces,
    //then from nSpaces + 1 to spaceLen % nSpaces, populate spaces[i] + 1
    //then error_sum = sum(pow(spaces[i],2))
    int minspace = spaceLen / nSpaces;
    int maxspace = minspace+1;
    int maxspaceCnt = spaceLen % nSpaces;
    int minspaceCnt = nSpaces - maxspaceCnt;

    int err = mypow(minspace-1,2)*minspaceCnt + mypow(maxspace-1,2)*maxspaceCnt;
    out("compute_err(%d, %d) : %d\n", spaceLen, nSpaces, err);
    return err;
}


/*
 * minimize the sum of all badnesses 
 * badness for a gap of n spaces is (n-1)^2
 * find the minimun paragraph error to pretty format a paragraph
 * need to store the number of gaps between each pair of subseq words
 * gap can be zero if at the end of a line, but it has to be 
 * at least 1 otherwise
 *
 * use Opt(i) = min(k=1,i-1) [ Opt(i,k)]
 * with Opt(i,k) = Opt(i-1,k) -D
 * use Opt(i,j) = if sum(k=i:j) [l_k + j - i] < M : M - Sum^3, 
 *                else min (k=i:j) [Opt(i,k) + Opt(k+1,j)]
 *                and Opt(i, n) = 0
 */
std::vector<int> min_paragraph_error(const std::vector<int> & l, int M, uppertriang<int> & L)
{
    out ( "min_paragraph_error()\n");
    int N = l.size(); //number of words

    uppertriang<int> C(l.size()); //count of words partakking -- to compute E
    //matrix<int> L(l.size(), l.size()); //sum of word lengths
    //assert (L.rows() == l.size());
    assert (L.cols() == l.size());
    matrix<int> E(l.size(), l.size()); //error measures
    matrix< quatr > O(l.size(), l.size()); //val AND from where was such opt chosen

    //initialize the matrices
    for(int i = 0; i < N; i++) {
        L(i,i) = l[i];
        C(i,i) = 1;
        E(i,i) = (l[i] == N ? 0 : 500); //all lines with one word get this badness, unless it fits
        quatr el = {E(i,i),i,-1,i};
        O(i,i) = el;
    }
    quatr el = {0, N-1, -1, N-1}; //k = -1 denotes it fits
    O(N-1,N-1) = el;

    //fill from diagonal to upper right corner of L,E and O; d-distance in loop
    for(int d = 1; d < N; ++d)
    {
//std::cout << "Iter " << d << std::endl;
//std::cout << "L:" << std::endl; L.print();
//std::cout << "E:" << std::endl; E.print();
//std::cout << "O:" << std::endl; O.print();

        for(int i = 0; i < N; ++i)
        {
            int j = i + d;
            if(j >= N) break;

            //compute sum of lengths from w_i to w_j
            L(i,j) = L(i,j-1) + l[j]; //length of the words
            C(i,j) = C(i,j-1) + 1; //how many words --  needed for E

            int linelen = L(i,j) + C(i,j) - 1;
out("linelen %d <= %d\n", linelen, M);
            //if that sum fits in paragraph, thats the Opt(i,j)
            if(linelen <= M) {
                assert(i != j);
                E(i,j) = compute_err(M-L(i,j), C(i,j)-1);

                quatr el = { E(i,j), i, -1, j}; //k = -1 denotes it fits
                O(i,j) = el;
                continue;
            }

            //Else words don't fit in a line, need to aggregate more lines

            int minE = std::numeric_limits<int>::max();
            int minK;

            //in matrix, set location * from best of locations # and $
            //         j
            //   . . . .
            // i . # $ *
            //   . . . #
            //   . . . $
            //
            //1,3 = min( (1,1) + (2,1), (1,2)+(3,3)
            for(int k = i; k < j; ++k) {
                int sum = E(i,k) + E(k+1,j);
                if(minE >= sum) {
                    minE = sum;
                    minK = k;
                }
            }

            //if we only were interested in value of Opt we can remove 
            //O and have brief version of the above as:
            //for(int k = i; k <j; ++k)
                //minE = std::min(minE, E(i,k) + E(k+1,j));

            E(i,j) = minE;
            quatr el = { E(i,j), i, minK, j};
            O(i,j) = el;
        }
    }

//std::cout << "Finally ANSW: " << E(0,N-1) << std::endl;
//std::cout << "L:" << std::endl; L.print();
//std::cout << "E:" << std::endl; E.print();
//std::cout << "O:" << std::endl; O.print();

    std::vector<int> res;
    //can only get the resulting path after finding out the final Opt value
    getMinPars(O, res, 0, N-1); //process the records to find the setup
    return res;
}

/*
std::string flatten_vector_of_strings(const std::vector<std::string> & parag)
{
    std::string str;
    for(std::vector<std::string>::const_iterator cit = parag.begin();
            cit != parag.end(); ++cit)
    {
        str += *cit + " ";
    }
    return str;
}

void print_paragraph_str(std::string & paragraph, const std::vector<int> & endings)
{
    int space_counter = 0;
    int ecounter = 0;
    for(std::string::iterator it = paragraph.begin(); it != paragraph.end(); ++it) {
        if(*it == ' ') {
            if(space_counter++ == endings[ecounter]) {
                ++ecounter;
                *it = '\n';
            }

        }
    }
    std::cout << paragraph << std::endl;
}
*/

void getNSpaces(int spaceLen, int nSpaces, int & minspace, int & minspaceCnt)
{
    assert(nSpaces >= 0);
    assert(nSpaces <= spaceLen);
    if (nSpaces < 1) return;
    minspace = spaceLen / nSpaces;
    int maxspaceCnt = spaceLen % nSpaces;
    minspaceCnt = nSpaces - maxspaceCnt;
    out("getNSpaces(%d,%d,..) minspace=%d, minspaceCnt=%d\n", spaceLen, nSpaces, minspace, minspaceCnt);
}

// build a paragraph with the words as strings put in a vector
// and the divisions (endings) passed as vector of ints
// could be improved to detect the i-th space and put a endl at that point
std::string build_paragraph(int M, const std::vector<std::string> & paragraph,
        const std::vector<int> & endings, uppertriang<int> & L)
{
    out("build_paragraph(%d, ...)\n", M);
    std::string spaces(' ', 100);
    std::string build;
    int line = 0;
    int start = 0;
    while(line < (int) endings.size())
    {
        int minspace = 0;
        int minspaceCnt = 0;

        int spaceLen = M - L(start, endings[line]);
        getNSpaces(spaceLen, endings[line] - start, minspace, minspaceCnt);

        int word = start;
        int lineWordCounter = 0;
        std::string sstr = std::string(minspace,' ');
        for(; lineWordCounter < minspaceCnt && word < endings[line]; word++, lineWordCounter++) {
            assert(word < (int) paragraph.size());
            out("lineWordCounter=%d, word=%d, minspace=%d, sstr='%s', minspaceCnt=%d\n", lineWordCounter, word, minspace, sstr.c_str(), minspaceCnt);
            build += paragraph[word] + sstr;
            //std::cout << paragraph[word] << " ";
        }
        sstr += ' ';
        for(; word < endings[line]; word++) {
            assert(word < (int) paragraph.size());
            out("word=%d, minspace=%d, sstr='%s', minspaceCnt=%d\n", word, minspace, sstr.c_str(), minspaceCnt);
            build += paragraph[word] + sstr;
            //std::cout << paragraph[word] << " ";
        }
        build += paragraph[endings[line]] + "\n";
        //std::cout << paragraph[endings[line]] << std::endl; 
        start = endings[line]+1;
        line++;
    }
    return build;
}


int main(int argc, char **argv)
{
    out("Starting...\n");

    while(1) {
        int M = 0;
        scanf("%d\n", &M);
        out("M=%d\n",M);

        if(0 == M) return 0;
        assert(M > 0 && M <= 80);

        std::vector<std::string> paragraph;
        std::vector<int> paragraph_lengths;

        char * buff = NULL;
        size_t n;
        int rc = 0;
        while( (rc = getline(&buff, &n, stdin)) > 0) {
            out("buff='%s' rc=%d\n",buff, rc);
            if(!buff || strnlen(buff, 10001) <= 1) break;

            char * tok = strtok (buff, " \n");
            out("tok='%s'\n",tok);
            if(NULL == tok) continue;
            paragraph.push_back(tok);

            while((tok = strtok (NULL, " \n"))) {
                out("tok='%s'\n",tok);
                paragraph.push_back(tok);
            }
        }
        for(int i = 0; i < (int) paragraph.size(); i++){ //1000 words
            paragraph_lengths.push_back(paragraph[i].length());
        }

        uppertriang<int> L(paragraph_lengths.size()); //sum of word lengths
        std::vector<int> endings = min_paragraph_error(paragraph_lengths, M, L);
        std::cout << build_paragraph(M, paragraph, endings, L);
        //std::string str = flatten_vector_of_strings(paragraph);
        //print_paragraph_str(str, endings);

        printf("\n");
    }
}
