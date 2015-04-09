#include<stdio.h>
#include<math.h>

double myround (double d)
{
    return (double) floor(d + 0.5L);
}

int main()
{

    /* find where the two lines l1 and l2 intersect */
    /* equation of line with normal vector (a, b) and 
     * containing point (x0,y0) is a(x-x0) + b(y-y0) = 0 
     * ax + by = c = a * x0 + b * y0
     *
     * x-x0   y-y0
     * ---- = ----
     *  -b      a
     * 
     * vector (a,b) is line vector for line r = x0 + at, r = y0 + bt
     * and normal vector to line ax + by = 1
     *
     * line y = 2x    =>    2x - y = 0
     *     /
     *    /
     *   / \
     *  /
     * has perpendicular vector (2, -1) and guide vector (1, 2)
     *
     *
     * Origin of circle satisfies both lines l1 and l2 
     * l1 has equation a1 * x + b1 * y = a1 * xm1 + b1 * ym1 = c1
     * l2 has equation a2 * x + b2 * y = a2 * xm2 + b2 * ym2 = c2
     *
     * where perpendicular vector is (-b, a) => so (-b1, a1) = (v1x, v1y)
     * a1 = v1y
     * b1 = - v1x
     *
     * l1 and l2 meet at xO,yO thus satisfies two linear eq l1 and l2:
     *   from l1, expres xO:
     *     xO = (c1 - b1 * yO) / a1 
     *
     *   plug in xO in l2:
     *     a2 * xO + b2 * yO = c2
     *     a2 * ((c1 - b1 * yO) / a1) + b2 *yO = c2
     *     a2 * (c1 - b1 * yO) + a1 * b2 *yO = a1 * c2
     *
     *     a2 * c1 - a2 * b1 * yO + a1 * b2 *yO = a1 * c2
     *
     *     yO * (a1*b2 - a2*b1) = a1*c2 - a2*c1
     *     yO = (a1*c2 - a2*c1) / (a1*b2 - a2*b1)
     *
     *
     *     once found (xO,yO) center of the circle
     *
     *     D = sqrt((x3-x1)^2 + (y3-y1)^2)
     * */
    
    double x1,y1;
    double x2,y2;
    double x3,y3;
    while(scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3) != EOF) 
    {
    /* printf("x1 %lf y1 %lf x2 %lf y2 %lf x3 %lf y3 %lf\n", x1, y1, x2, y2, x3, y3); */
        double v1x = x2-x1;
        double v1y = y2-y1;
        double a1 = v1x;
        double b1 = v1y;
        double xm1 = (x1 + x2) / 2;
        double ym1 = (y1 + y2) / 2;
        /* if a1 is 0 then we can't use this vector, we need to take vector from 1 -> 3 */
        if(a1 == 0.0) {
            v1x = x3 - x1;
            v1y = y3 - y1;
            a1 = v1x;
            b1 = v1y;
            xm1 = (x1 + x3) /2;
            ym1 = (y1 + y3) / 2;
        }

        double v2x = x3-x2;
        double v2y = y3-y2;
        
        double a2 = v2x;
        double b2 = v2y;

        double xm2 = (x2 + x3) / 2;
        double ym2 = (y2 + y3) / 2;

        double c1 = a1 * xm1 + b1 * ym1;
        double c2 = a2 * xm2 + b2 * ym2;

        double yO = (a1*c2 - a2*c1) / (a1*b2 - a2*b1);
        double xO = (c1 - b1 * yO) / a1;

        double dx = xO-x1;
        double dy = yO-y1;
        double R = sqrt(dx*dx + dy*dy);

        /* printf("a1 %.2lf b1 %.2lf a2 %.2lf b2 %.2lf c1 %.2lf c2 %.2lf x0 %.2lf y0 %lf %.2lf\n", a1, b1, a2, b2, c1, c2, xO, yO, 2*R*3.1414926535589793); */

        /* TODO: fix the rounding */
        double C = 2*R*3.141592653589793;
        printf("%.2lf\n", myround(C*100.0) / 100.0);
    }
    return 0;
}
