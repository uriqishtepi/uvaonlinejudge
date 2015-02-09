#include <stdio.h>
#include <stdlib.h>
struct pair {
    int numerator;
    int denominator;
};
#define MAXS 10000000
int main()
{
    int i, j, num;
    struct pair * arr = malloc(MAXS * sizeof(struct pair));
    int count = 0;
    int down;
    int up;
    int direction = 0;
    for(i = 1; count < MAXS; i++) {
        for(j = 0; j < i && count < MAXS; count++, j++) {
            if(direction == 1) {
                down = i - j;
                up = j + 1;
            } else {
                up = i - j;
                down = j + 1;
            }

            arr[count].numerator = up;
            arr[count].denominator = down;

        }
        direction = !direction;
    }
    while(scanf("%d\n", &num) != EOF) {
        printf("TERM %d IS %d/%d\n", num, arr[num-1].numerator, 
                arr[num-1].denominator);
    }
    return 0;
}
