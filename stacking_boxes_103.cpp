/* determine longest nesting sequence of boxes 
 *
 * this is a dynamic programming problem
 * first create sequence of partially sorted boxes, by sorting on
 * first dimension, if equal, by second dimension, etc.
 *
 * in order to get a total fitting, i can take each item in sequence 
 * or not take it and thus continue to next subproblem, filling a matrix. 
 *
 * so in order to get this bottom up, need to have Matrix with pairwise
 * comparisons, fits does not fit to look up (this comparison can be done
 * at the same time as when sorting the sequence).
 *
 * */
#include <vector>
#include <algorithm>
#include <functional>
#include <stdio.h>
#include <assert.h>

#define vi std::vector<int>

/* returns true if box a fits into b */
bool fits(const vi & a, const vi & b) 
{
    for(int i = 0; i < (int) a.size(); i++) {
        if(a[i] >= b[i])
            return false;
        printf("compared %d is less than %d\n", a[i], b[i]);
    }
    return true;
}

vi slines[30]; //array of 30 sorted vectors

struct myltcl {
    /* use this for partial ordering:
     *
     * do this for every dimennsion i
     * returns  true if a < b 
     * returns false if a > b
     * in case a == b, investigate next i 
     *
     * */

    bool operator() (int a, int b)
    {
        const vi & va = slines[a];
        const vi & vb = slines[b];
        for(int i = 0; i < (int) va.size(); i++) {
            if(va[i] < vb[i])
                return true;
            else if(va[i] > vb[i]) 
                return false;
            //else is equal so next i
        }
        return false; //when all are equal
    }

    myltcl(int lines) : _lines(lines)
    { }
    int _lines;
};

void printMat(int m[30][30], int lines)
{   
    for(int i = 0; i < lines; i++) {
        for(int j = 0; j < lines; j++)
            printf(" %d ", m[i][j]);
        printf(" \n ");
    }
}


void printVec(const vi & v)
{   
    for(vi::const_iterator it = v.begin(); it != v.end(); ++it)
        printf(" %d ", *it);
    printf(" \n ");
}

int main()
{
    int lines, dims;
    while(scanf("%d %d", &lines, &dims) != EOF) {
        assert(lines < 30);
        assert(dims < 10);
        int order[30] = {0}; //use this to order the slines rows
        for(int i=0; i<lines;i++) {
            slines[i].clear();
            for(int j = 0; j<dims; j++){
                int v;
                scanf("%d", &v);
                slines[i].push_back(v);
            }
            assert((int)slines[i].size() == dims);
            std::sort(slines[i].begin(), slines[i].end(), std::less<int>());
            printVec(slines[i]);

            order[i] = i;
        }

        struct myltcl mylt(lines);
        //sort array of sets based on partial ordering
        std::sort(order, order+lines, mylt);

        printf("After sorting:\n");
        for(int i=0; i<lines;i++) {
            printVec(slines[order[i]]);
        }
        printf("\n");

        int F[30][30] = {{0}};
        //fill the fitings
        int L[30][30] = {{0}};
        int M[30][30] = {{0}};
        for(int i = 0; i < lines-1; i++) {
            for(int j = i + 1; j < lines; j++) {
                F[i][j] = fits(slines[order[i]], slines[order[j]]);
            }
        }
        printf("F: \n"); printMat(F, lines); printf("\n");
            
        for(int i = 0; i < lines; i++) {
            //in seq a b c.. length of fit a b, etc. is one or zero
            L[i][0] = 1; //lenigth of a substring of size 1, is 1
            M[i][0] = i; //last (max) in subsecuonce
        }

        //L[0][lines] is the answer
        //Recurrence looks like this:
        //L[i][j] = for k from i to j : max(L[i][k] + L[k][j], L[i][k-1] + L[k+1][j]);

        //bottom up approach, consider increasing sequence lengths:
        //a b, b c, c d, d e    then
        //a b c, b c d     then
        //a b c d


        /*
        L 
            pos
        1  1  1  1
           0  0  0
      d       0  0
                 0
                 */

        for(int d = 2; d <= lines; d++) { //join subseq of length d
            for(int s = 0; s <= lines-d; s++) { //start of the subseq
                for(int k = 1; k < d; k++) { //start of the sec subseq
                    int fl = k-1;             //first supseq length
                    int ss = s + k;           //start of second subseq
                    int sl = d - k - 1;       //second supseq length
                    int l1 = L[s][fl];            
                    int l2 = L[ss][sl];

printf("d=%d, s=%d, k = %d, fl=%d, ss=%d, sl=%d, l1=%d,l2=%d, F[M[s][fl]][ss] = %d\n", 
        d,s, k, fl, ss, sl, l1, l2, F[M[s][fl]][ss]);
                    if( F[M[s][fl]][ss] &&  L[s][d-1] < l1 + l2) {
                        L[s][d-1] = l1 + l2;
                        M[s][d-1] = M[ss][sl];
                    } else if(l1 >= l2 &&  L[s][d-1] < l1) {
                        L[s][d-1] = l1;
                        M[s][d-1] = M[s][fl];
                    } else if ( L[s][d-1] < l2) {
                        L[s][d-1] = l2;
                        M[s][d-1] = M[ss][sl];
                    }

                    printMat(L, lines); printf("\n");
                    printMat(M, lines); printf("\n");
                }
            }
        }

        printf("longest %d\n", L[0][lines-1]);
        /* long version:
         a b c -- take a now max el is a          - take b maxel is b
                                                  \ don't take b maxel is a
                  don't take a el maxel is 0      - take b maxel is b
                                                  \ don't take b maxel is 0
         */
         
               
        
    }

    return 0;
}
