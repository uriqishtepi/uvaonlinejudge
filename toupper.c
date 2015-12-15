#include<stdio.h>

#define TOUPPER(x) ( ( (x>='a') && (x<='z') ) ? x - 32 : x )
/* 10% gain (from 56% CPU to 46% CPU) in simple program */
#define TOUPPER2(x) ( ( upmap[x] ) ) 
int upmap[256];

int main()
{
    int i;
    for(i = 0; i <=256; i++) upmap[i] = i;
    for(i = 'a'; i <='z'; i++) upmap[i] = i-32;

    unsigned int hash = 0;
    char * cstr = "tnhi snth ISI THI THS";
    char * sptr = cstr;
    for(i = 0; i < 10000000; i++) {
        hash = (((hash%8388013) << 8) | TOUPPER2(*sptr));
        sptr++;
        if(!*sptr) 
            sptr = cstr;
    }
    printf("hash=%d\n", hash);

    return 0;
}
