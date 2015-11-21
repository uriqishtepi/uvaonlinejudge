/* find longest string x whose permutation is a subsequence strings a and 
 * a permutation is a subseq of b
 *
 * this means that we need to find longest common characters in a and b
 */

#include <stdio.h>
#include <sys/param.h>

#define forl(i, S, E) for(i = S; i < E; i++) 


/* given str populate arr with letter frequency */
void populate_arr(int * arr, char * str) {
    char * p = str;
    while(*p) {
        arr[ (*p) - 'a' ] ++;
        p++;
    }
}


int main()
{
    char a[1001] = {0};
    char b[1001] = {0};

    while( scanf("%s %s", a, b) != EOF) {
        int arr1[26] = {0};
        int arr2[26] = {0};
        populate_arr(arr1, a);
        populate_arr(arr2, b);

        int i;
        forl(i,0,26) {
            int m = MIN(arr1[i], arr2[i]);
            int j;
            forl(j,0,m) {
                printf("%c", i+'a');
            }
        }
        printf("\n");
    }
    return 0;
}
