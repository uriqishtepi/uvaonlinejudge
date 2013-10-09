#include<stdio.h>
#define forl(i,init, max) for(int i = init; i < max; i++) 
#define maxN 1025
int main()
{
    int nscen = 0;
    scanf("%d\n", &nscen);

    forl(i, 0, nscen) {
        int d = 0;
        scanf("%d",&d);

        int grid[maxN+1][maxN+1] = {0}; //create grid
        int maxs = 0;
        int locx, locy;

        int numr = 0;
        scanf("%d",&numr);

        forl(j, 0, numr) {
            int x, y, s;
            scanf("%d %d %d",&x, &y, &s);

            int minx = x - d;
            minx = minx < 0 ? 0 : minx;
            int maxx = x + d+1;
            //maxx = maxx > maxN ? maxN : maxx;
            int tmp = (maxx - maxN);
            maxx = maxN + ((maxx - maxN) & (tmp >> 31));

            int miny = y - d;
            miny = miny < 0 ? 0 : miny;
            int maxy = y + d+1;
            maxy = maxy > maxN ? maxN : maxy;

            forl(l, miny, maxy) {
                forl(k, minx, maxx) {
                    grid[l][k] += s;

                    if(grid[l][k] > maxs) {
                        maxs = grid[l][k];
                        locx = k;
                        locy = l;
                    }
                }
            }
        }
        printf("%d %d %d\n", locx, locy, maxs);
    }
    return 0;
}
