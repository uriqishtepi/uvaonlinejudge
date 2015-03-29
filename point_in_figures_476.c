#include<stdio.h>


/* (x1,y1) 
 * *-----------------------------+
 * |                             |
 * |                             |
 * |                             |
 * +-----------------------------* (x2,y2)
 */
struct rect {
    float x1;
    float y1;
    float x2;
    float y2;
};

void printRec(struct rect * r ) {
    printf("(%f, %f) (%f, %f)\n", r->x1, r->y1, r->x2, r->y2);
}

int isInRect(struct rect * r, float x, float y)
{
    return(r->x1 < x  && x < r->x2 && r->y1 > y && y > r->y2);
}

int abs(float x) {
    if (x < 0) return -x;
    return x;
}

int main()
{

    char * buf = NULL;
    int bsz;
    int readingpts = 0;
    struct rect arr[11];
    int count = 0;
    int pointcounter = 0;
    while( getline(&buf, &bsz, stdin) > 0 ) {
        if(buf[0]=='*') {
            readingpts = 1;
        }
        else if(readingpts == 0) {
            struct rect *r = &arr[count++];
            char c;
            sscanf(buf,"%c %f %f %f %f", &c, &r->x1, &r->y1, &r->x2, &r->y2);
            /* printRec(r); */
        }
        else {
            int i;
            int found = 0;
            float x, y;
            sscanf(buf,"%f %f", &x, &y);
            /* printf("Point %d is %f %f\n", pointcounter, x, y); */
            if(abs(x - 9999.9)  < 0.00001 && abs(y - 9999.9)  < 0.00001) break;

            pointcounter++;
            for(i = 0; i < count; i++) {
                struct rect * r = &arr[i];
                if( isInRect(r, x, y) ) {
                    printf("Point %d is contained in figure %d\n", pointcounter, i+1);
                    found = 1;
                }
            }
            if(!found)
                printf("Point %d is not contained in any figure\n", pointcounter);
        }
    }

    return 0;
}
