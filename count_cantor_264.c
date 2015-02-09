#include <stdio.h>

int main()
{
    int i, j, num;
    while(scanf("%d\n", &num) != EOF) {
        int count = 0;
        int down;
        int up;
        int direction = 0;
        for(i = 1; count < num; i++) {
            for(j = 0; j < i && count < num; count++, j++) {
                if(direction == 1) {
                    down = i - j;
                    up = j + 1;
                } else {
                    up = i - j;
                    down = j + 1;
                }
            }
            direction = !direction;
        }
        printf("TERM %d IS %d/%d\n", count, up, down);
    }
    return 0;
}
