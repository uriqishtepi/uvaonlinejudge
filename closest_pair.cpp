/* closest pair will search for the pair of points scattered in a plane, 
 * which has the smallest euclidian distance. 
 *
 * we use distance squared for most computations to avoid expense of 
 * computing sqrt.
 *
 * there are two algorithms here, one the naive one which has a double for loop
 * iterating over each pair of points to get their distance Theta(n^2)
 * and the divide and conquer algorithm which sorts the pts in x and in y
 * before dividing into left and right halves, and finding the closest pair
 * in the left, right, and strip centered at midpt with radius min dist
 * found so far. 
 *
 * trick is to pass to each divide step subsets of the sorted arrays 
 * which contain the left pts only and the right pts only.
 *
 * If a pt is dup, then min dist is 0. 
 *
 */
#include <algorithm>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

#include <sys/time.h>

#define forl(i,init, max) for(int i = init; i < max; i++) 
#define SZ 1000
#define vp std::vector<point> 


//#define DEBUG true
#ifdef DEBUG
#define out printf
#else
#define out
#endif


int swapcounter = 0;

void swap (int &a, int &b)
{
    int t = b;
    b = a;
    a = t;
    swapcounter++;
}

void timediff(const char * s) {
    static timeval tv;
    timeval tmp;

    gettimeofday(&tmp, NULL);
    int sec = (tmp.tv_sec - tv.tv_sec)*1000000;
    int msec = (tmp.tv_usec - tv.tv_usec);
    printf("%20.20s diff = %12.dusec\n", s, sec + msec);
    tv = tmp;
}
struct point {
    int x;
    int y;
};

void print_arr(const vp &v) {
    for(vp::const_iterator cit = v.begin(); cit != v.end(); ++cit)
        out("(%d,%d) ", cit->x, cit->y);
    out("\n");
}

bool xle(const point & p1, const point & p2) { if(p1.x == p2.x) return p1.y < p2.y; return p1.x < p2.x; }
bool yle(const point & p1, const point & p2) { if(p1.y == p2.y) return p1.x < p2.x; return p1.y < p2.y; }

//dist keep it squared
uint64_t dist (const point & a, const point &b)
{
    uint64_t xdif = a.x-b.x;
    uint64_t ydif = a.y-b.y;
    return xdif*xdif + ydif*ydif;
}

uint64_t closest_pair_in_strip(const vp & arrx, const vp & arry, int midpt, uint64_t m)
{
    //start from rightmost x in the left
    //center is arrx[xend/2]
    double delta = sqrt(m);
    point center = arrx[midpt];
    for(unsigned int i = 0; i < arry.size(); i++) {
        //if outside the strip, ignore it
        if(arry[i].x < center.x - delta || arry[i].x > center.x + delta)
            continue;

        //start at y at 0 up to the last y, if x outside of range, continue
        //else 
        unsigned int j = 1;
        while (j <= 7 && i+j < arry.size()) {
            uint64_t d = dist(arry[i],arry[i+j]);
            if(m > d) m = d;
            j++;
        }
    }
    return m;
}


uint64_t closest_pair(const vp & arrx, const vp & arry)
{
    //base case, two points
    assert(arrx.size() > 1 && "one or less element");
    out("\ncps x: "); print_arr(arrx);
    out("\ncps y: "); print_arr(arry);
    assert(arrx.size() == arry.size() && "arrx and arry diff size");
    if(arrx.size() == 2) return dist(arrx[0],arrx[1]);

    vp lx; //left sorted in x
    vp rx; //right sorted in x
    vp ly; //left sorted in y
    vp ry; //right sorted in y

    //linear work populating the sorted arrays lx,rx,ly,ry
    int xsize = arrx.size();
    int midpt = xsize / 2;
    out("[%d %d %d]", arrx[0].x,arrx[midpt].x,arrx.back().x);
    for(int i = 0; i <= midpt; i++) {
        lx.push_back(arrx[i]);
    }
    for(int i = midpt; i < xsize; i++) {
        rx.push_back(arrx[i]);
    }

    int ysize = arry.size();
    for(int i = 0; i < ysize; i++) {
        if(xle(arry[i], arrx[midpt]))
            ly.push_back(arry[i]);
        else if(xle(arrx[midpt], arry[i]))
            ry.push_back(arry[i]);
        else {
            ly.push_back(arry[i]);
            ry.push_back(arry[i]);
        }
    }

    //get midpoint of the sequence to determine the split left to right
    uint64_t l = closest_pair(lx, ly);
    out("l %d ", l);
    uint64_t r = closest_pair(rx, ry);
    out("r %d ", r);
    uint64_t m = std::min(l,r);
    out("m %d ", m);
    
    //linear work to get the closest in the strip
    uint64_t c = closest_pair_in_strip(arrx, arry, midpt, m);
    out("c %d\n", c);
    return std::min(c,m);
}

double closest_pair_naive(const vp & arrx)
{
    uint64_t min_d = 10000000;
    for(unsigned int i = 0; i < arrx.size() - 1; i++) {
        for(unsigned int j = i+1; j < arrx.size(); j++) {
            uint64_t d = dist(arrx[i], arrx[j]);
            if(min_d > d) min_d = d;
            out("d (%d,%d:%d,%d) = %d, min_d=%d\n", arrx[i].x , arrx[i].y,arrx[j].x,arrx[j].y,d,min_d);
        }
    }
    return min_d;
}

void readInput(vp &vx)
{
  int N; //nodes
  scanf("%d\n", &N);
  out("N %d\n",N);
    
  while(N-- > 0) {
    point p;
    scanf("%d,%d", &p.x, &p.y);

    vx.push_back(p);
  }
}

int main (void)
{
    vp vx;
    /*
    */
    static timeval now;
    gettimeofday(&now, 0);
    srand(now.tv_usec);


    forl(i, 0, SZ) {
        point p;
        p.x = rand() % (SZ*10);
        p.y = rand() % (SZ*10);
        vx.push_back(p);
    }

    //readInput(vx);

    vp vy = vx;

    //sort arr by x, and arry by y
    std::sort(vx.begin(), vx.end(), xle);
    std::sort(vy.begin(), vy.end(), yle);

    out("vx: "); print_arr(vx);
    out("vy: "); print_arr(vy);

    //detect duplicate point -- in that case distance is zero
    for(vp::const_iterator cit = vx.begin()+1; cit != vx.end(); ++cit) {
        //out("checking (%d,%d) vs (%d,%d)\n", (cit-1)->x, (cit-1)->y, cit->x, cit->y);
        if(xle(*(cit-1),*cit)) continue;
        else if(xle(*cit,*(cit-1))) continue;
        else {
            printf("Duplicate point (%d,%d), d=0\n", cit->x, cit->y);
            return 0;
        }
    }

    timediff("setting time");
    uint64_t d_n = closest_pair_naive(vx);
    timediff("naive: ");
    uint64_t d = closest_pair(vx, vy);
    timediff("nlog: ");

    printf("closest pair; naive %lld vs %lld\n", d_n, d);
    if(d_n != d) {
        forl(i, 0, SZ) { 
            printf("%d (%d,%d)\n",i, vx[i].x, vx[i].y); 
        }
    }
    assert(d_n == d && "not same as naive");

    return 0;
}
