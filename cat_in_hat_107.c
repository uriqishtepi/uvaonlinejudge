#include<stdio.h>


int main()
{
  int h;
  int w; /*workers */

  while(scanf("%d %d", &h, &w) != EOF && !(h == 0 && w == 0) ) {

    if(h == 1) {
        printf("0 1\n"); /* zero nonworkers and 1 height */
        /* continue; */
        continue;
    }
    if(w == 1) {
        /* height halves each time: log h number of cats */
        int nonw = 0;
        int toth = 1;
        while(h > 1) { 
            nonw += 1;
            toth += h;
            h = h / 2;
        }
        printf("%d %d\n", nonw, toth);
        continue; 
    }

    /* find depth */
    int x = 1; /* x is the N factor */
    int d = 0;
    int tot = 1;
    int nonw = 1;
    int toth = h;
    int lvl = 1;
    int lvlh = h;
    int cntnrh = 1;
    int maxd = 1<<30;
    int found = 0;


    while(++x <= w) {
        d = 0;
        tot = 1;
        nonw = 1;
        toth = h;
        lvl = 1;
        lvlh = h;
        cntnrh = 1;

        while(lvl < w && cntnrh < h && d+1 < maxd) {
            lvl *= x;
            lvlh /= x + 1;
            cntnrh *= (x + 1);

            tot += lvl;
            d++;
            if(lvl < w) {
                nonw += lvl;
            }
            toth += lvl*lvlh;
/*printf("x %d cntnrh %d, lvl %d tot %d lvlh %d toth %d d %d maxd %d\n", x, cntnrh, lvl, tot, lvlh, toth, d, maxd); */
        }
        if(lvl == w && lvlh == 1) {
            found = 1;
            break;
        }
        if(d == 1)
            break;
    }
    if(found)
        printf("%d %d\n", nonw, toth);
  }
  return 0;
}
