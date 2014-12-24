#include <stdio.h>
int main ()
{
    int n;
    scanf("%d", &n);

    int count = 0;
    while(count++ < n) {
        int f;
        scanf("%d", &f);
        int farmer = 0;
        int sum = 0;
        while(farmer++ < f) {
            int size, numA, c;
            scanf("%d %d %d\n", &size, &numA, &c);
            sum += size * c;
        }
        printf("%d\n", sum);
    }
    return 0;
}
