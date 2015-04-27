#include<stdio.h>
#include<math.h>
#define EPSILON 0.01

int main()
{
    int x1 =0,y1 =0;
    int x2 =1,y2 =0;
    int x3 =0,y3 =1;

    while(scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2,  &x3, &y3) != EOF) {
        int dax = (x1-x2);
        int day = (y1-y2);
        int dbx = (x3-x2);
        int dby = (y3-y2);
        int dcx = (x1-x3);
        int dcy = (y1-y3);
        double a = sqrt(dax*dax + day*day);
        double b = sqrt(dbx*dbx + dby*dby);
        double c = sqrt(dcx*dcx + dcy*dcy);
        double s = (a+b+c) / 2;
        double triangle_area = sqrt(s* (s-a)*(s-b)*(s-c));
        printf("Heron triangle_area = %lf\n", triangle_area);

        double determinant = fabs((double)(x1*y2 + x2*y3+ x3*y1 - x2*y1 - x3*y2 - x1*y3)) / 2;
        printf("determinant = %lf\n", determinant);

        if(fabs(determinant - triangle_area) > EPSILON) {
            printf("different %lf\n", fabs(determinant - triangle_area));
            exit(1);
        }
    }
    return 0;
}
