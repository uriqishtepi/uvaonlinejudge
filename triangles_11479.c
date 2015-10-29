#include<stdio.h>


void mysort(int a[], int numel)
{
    int i, j;
    for(i = 0; i < numel-1; i++)
        for(j = i+1; j < numel; j++)
            if(a[i] > a[j]) {
                int tmp = a[j];
                a[j] = a[i];
                a[i] = tmp;
            }
}

int main()
{
    int n;
    int cnt;
    scanf("%d", &n);

    while(cnt++ < n) {
        int a[3];
        scanf("%d %d %d", a, a+1, a+2);
        mysort(a, 3);

        /*printf("%d %d %d\n", a[0], a[1], a[2]); */
        printf("Case %d: ", cnt);
        if(a[0] == 0 || a[0] + a[1] < a[2])
            printf("Invalid\n");
        else if(a[0] == a[1] && a[1] == a[2])
            printf("Equilateral\n");
        else if(a[0] == a[1] || a[1] == a[2])
            printf("Isosceles\n");
        else
            printf("Scalene\n");
    }
    return 0;
}
