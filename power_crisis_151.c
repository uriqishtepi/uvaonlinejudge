#include<stdio.h>

#define out
//#define out printf 

int main()
{
    int N;
    while(scanf("%d\n", &N) != EOF && N != 0) {
        if(N < 13 || N > 99) continue;
        int i;
        for(i = 5; i < 4*N; i++) {
            int arr[100] = {0};
            int val = 1;
            int count = 0;
            int minicount = i-1;
            while(count < N) { /* we start at 0 */
                if(val > N) val = 1;
                if(arr[val] == 1) {
                    out("%d skipping arr[%d] %d minicount %d count %d\n", i, val, arr[val], minicount, count);
                    val++;
                    continue;
                }
                minicount++;
                if(minicount == i) {
                    if(val == 13) {
                        out("%d breaking arr[%d] %d minicount %d count %d\n", i, val, arr[val], minicount, count);
                        break;
                    }
                    out("%d arr[%d] %d minicount %d count %d\n", i, val, arr[val], minicount, count);
                    arr[val] = 1;
                    count++;
                    minicount = 0;
                }
                else
                out("%d counting arr[%d] %d minicount %d count %d\n", i, val, arr[val], minicount, count);
                val++;
            }
            if(count >= N-1 && val == 13) {
                printf("%d\n", i);
                int j;
                for(j = 0; j < N; j++) out("%d ", arr[j]); out("\n");
                break;
            }
        }

    }


    return 0;
}
