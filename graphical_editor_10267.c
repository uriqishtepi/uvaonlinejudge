#include<stdio.h>
#include <string.h>

int main()
{
    char buff[1024];
    char image[250][250];
    char cmd;
    int m = 0;
    int n = 0;
    while(scanf("%c ", &cmd) != EOF && cmd != 'X') {
        printf("c=%c\n", cmd);
        switch(cmd) {
          case '\n': continue;
          case 'I': 
            {
            int i;
            memset(image, 0, sizeof(image)); 
            scanf("%d %d", &m, &n);
            printf("%d %d", m, n);

            for(i = 0; i < n; i++) 
                memset(image[i], 'O', m* sizeof(char)); 
            }
            break;
          case 'C': 
            {
            int i;
            for(i = 0; i < n; i++) 
                memset(image[i], 'O', m* sizeof(char)); 
            }
            break;
          case 'L': 
            {
            int x, y;
            char c;
            scanf("%d %d %c", &x, &y, &c);
            image[y-1][x-1] = c;
            }
            break;
          case 'V': 
            {
                int x, y1, y2;
                char c;
                scanf("%d %d %d %c", &x, &y1,&y2,&c);
                printf("%d %d %d %c", x, y1, y2, c);
                int i;
                for(i = y1; i <= y2; i++) 
                    image[i-1][x-1] = c;
            }
            break;
          case 'H': 
            {
                int x1, x2, y;
                char c;
                scanf("%d %d %d %c", &x1, &x2, &y,&c);
                printf("%d %d %d %c", x1, x2, y, c);
                int j;
                for(j = x1; j <= x2; j++) 
                    image[y-1][j-1] = c;
            }break;
          case 'K': 
            {
                int x1,x2,y1,y2;
                char c;
                scanf("%d %d %d %d %c", &x1, &x2, &y1,&y2,&c);
                printf("%d %d %d %d %c", x1, x2, y1,y2, c);
                int i, j;
                for(i = y1; i <= y2; i++) {
                    for(j = x1; j <= x2; j++) {
                        image[i-1][j-1] = c;
                    }
                    printf("\n");
                }
            }
            break;
          case 'F': 
            {
                int x, y;
                char c;
                scanf("%d %d %c", &x, &y, &c);
                image[y-1][x-1] = c;
            }
            break;
          case 'S': 
            {
                gets(buff); //chew rest of line
                int i, j;
                for(i = 0; i < n; i++) {
                    for(j = 0; j < m; j++) {
                        printf("%c", image[i][j]);
                    }
                    printf("\n");
                }
            }
            break;
          default : 
            gets(buff);
            continue;
        }
    }

    return 0;
}
