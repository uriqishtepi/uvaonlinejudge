/* find if triangle is right triangle */
#include <stdio.h>


int main()
{
    int a, b, c;
    while(scanf("%d %d %d", &a, &b, &c) != EOF && !(a==0 && b==0 && c==0)) {
        int smallest;
        int med;
        int largest;

        if(a > b) {
            if(a > c) {
                largest = a;
                if(b > c) {
                    med = b;
                    smallest = c;
                }
                else {
                    med = c;
                    smallest = b;
                }
            }
            else {
                largest = c;
                med = a;
                smallest = b;
            }
        }
        else { 
            if(b > c) {
                largest = b;
                if(a > c) {
                    med = a;
                    smallest = c;
                }
                else {
                    med = c;
                    smallest = a;
                }
            } 
            else {
                largest = c;
                med = b;
                smallest = a;
            }
        }

        if(smallest*smallest + med*med == largest*largest) {
            printf("right\n");
        }
        else {
            printf("wrong\n");
        }
    }
    return 0;
}
