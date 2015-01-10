#include<stdio.h>
#include<assert.h>
int main() 
{
    int n;
    int h[50];
    int items = 0;
    while( scanf("%d ", &n) && n != 0) {
        assert(n <= 50);
        items++;
        int i;
        int sum = 0;
        for(i = 0; i < n; i++) {
            scanf("%d", &h[i]);
            sum += h[i];
        }
        int avg = sum / n;
        assert((sum % n) == 0);
        int cnt = 0;
        for(i = 0; i < n; i++) {
            if(h[i] > avg) 
                cnt+=h[i]-avg;
        }
        printf("Set #%d\nThe minimum number of moves is %d.\n\n", items, cnt);
    }
    return 0;
}
