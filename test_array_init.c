/* show that setting the entire buffer by line[12] = {0} is slower than
 * setting only a few of the bytes -- although only a little bit slower
 * 0.81s vs 1.38s
 */
#include <stdio.h>
#include <stdlib.h>

void f(char * line)
{
    line[rand() % 1022] = rand();
}

int main(void)
{
    int i = 0;
    const int H = 10000000;
    for (i = 0; i < H; i++)
    {
        char line[1024];
        line[0] = 0;
        line[1023] = 0;
        f(line); //avoid compiler optimization by calling f()
    }

    /*
    for (i = 0; i < H; i++)
    {
        char line[1024] = {0};
        f(line);
    }
    */
    return 0;
}
