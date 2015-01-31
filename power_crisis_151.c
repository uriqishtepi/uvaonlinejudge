#include<stdio.h>
#include<string.h>

#define out 

int main()
{
    int N;
    while(scanf("%d\n", &N) != EOF && N != 0) {
        if(N < 13 || N > 99) continue;
        int i = 0;
        
        for(i=1; i<10*N; i++) {
            unsigned char arr[102] = {0};
            char j = 0;
            for(j=0;j<100;j++) arr[j] = j+1;
            int tot = N;
            int curr = 0;
            /* start at 1, jump every N */
            while(arr[curr] != 13) {
for(j=0;j<tot;j++) out("%d ", arr[j]);
out("\n");
out("looking at curr %d tot %d arr %d;\n", curr, tot, arr[curr]);
                memmove(&arr[curr], &arr[curr+1], tot - curr + 1);
                tot--;
                curr--;
                curr = (curr+i) % tot;
            }
            if(tot == 1) 
                break;
        }
        printf("%d\n", i);

    }


    return 0;
}
