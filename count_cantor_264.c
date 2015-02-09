#include <stdio.h>

int main()
{
    int i, j, num;
    while(scanf("%d\n", &num) != EOF) {
        int count = 0;
        int down;
        int up;
        for(i = 1; count < num; i++) {
            for(j = 0; j < i && count < num; count++, j++) {
                down = i - j;
                up = j + 1;
            }
        }
        printf("TERM %d IS %d/%d\n", count, up, down);
    }
    return 0;
}
