#include<stdio.h>
#include<string.h>
#include<sys/param.h>

/* used this function to test the output of other roman numerals program */
int print_letter_freq_per_line()
{
    char * str = NULL;
    int n;
    while(getline(&str, &n, stdin) != EOF) {
        int arr[256] = {0};
        int len = strlen(str);
        int mx = 0;
        int i;
        for( i = 0; i < len; i++) {
            if((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') )
            arr[(int)str[i]]++;
            mx = MAX(mx, arr[(int)str[i]]);
        }
        int l;
        l = 'I'; printf("%d ", arr[l]);
        l = 'V'; printf("%d ", arr[l]);
        l = 'X'; printf("%d ", arr[l]);
        l = 'L'; printf("%d ", arr[l]);
        l = 'C'; printf("%d", arr[l]);
        printf("\n");
            
    }

    return 0;
}


int main()
{
    enum romdig { I = 0, V = 1, X = 2, L = 3, C = 4};
    int arr[101][6] = {{0}};
    int sums[101][6] = {{0}};

    arr[1][I] = 1;
    sums[1][I] = 1;
    int k = 2;
    while(k <= 100) {
        int * aptr = arr[k];
        memcpy(arr[k], arr[k-1], 5*sizeof(int));
        int rem = k % 10;
        switch(rem) {
            case 0:
                aptr[I] = 0;
                int rem100 = k%100;
                if(rem100 == 90) {
                    aptr[C]++;
                    aptr[L]=0;
                    aptr[X]=1;
                }
                else if(rem100 == 50) {
                    aptr[X]=0;
                }
                else if(rem100 == 40) {
                    aptr[X]=1;
                    aptr[L]=1;
                }
                else if(rem100==0) {
                    aptr[X]=0;
                }
                break;
            case 1:
            case 2:
            case 3:
            case 6:
            case 7:
            case 8:
                aptr[I]++;
                break;
            case 4:
                aptr[V]++;
                aptr[I] = 1;
                break;
            case 5:
                aptr[I] = 0;
                break;
            case 9:
                aptr[I] = 1;
                aptr[V] = 0;
                aptr[X]++;
        }

        int t;
        for(t = 0; t <= C; t++) {
            sums[k][t] = sums[k-1][t] + aptr[t];
        }
        /*printf("%d: %d %d %d %d %d\n", k, aptr[I], aptr[V], aptr[X], aptr[L], aptr[C]);
        printf("%d: %d i, %d v, %d x, %d l, %d c\n", k, sums[k][I], sums[k][V], sums[k][X], sums[k][L], sums[k][C]);
        */
        k++;
    }
    while(scanf("%d", &k) != EOF && k != 0) {
        printf("%d: %d i, %d v, %d x, %d l, %d c\n", k, sums[k][I], sums[k][V], sums[k][X], sums[k][L], sums[k][C]);
    }
    return 0;
}
