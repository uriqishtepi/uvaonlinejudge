#include<stdio.h>


int main()
{
    int A;
    int L;
    int casecount = 0;
    while(scanf("%d %d\n", &A, &L) != EOF && !(A < 0 && L < 0)) {
        casecount++;
        int terms = 0;
        int val = A;
        while(val != 1 && val <= L) {
            terms++;
            if(val & 0x1) 
                val = 3*val+1;
            else 
                val >>= 1;
        }
        if(val == 1) terms++;

        printf("Case %d: A = %d, limit = %d, number of terms = %d\n", casecount, A, L, terms);
    }

    return 0;
}
