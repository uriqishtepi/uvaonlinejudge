#include<stdio.h>
#include<string.h>
#include<assert.h>

int main()
{
    char needle[100256];
    char haystack[100256];
    while(scanf("%s %s", needle, haystack) != EOF)
    {
        int nlen = strnlen(needle, sizeof(needle));
        int hlen = strnlen(haystack, sizeof(haystack));
        int good = 1;
        if(nlen <= hlen) {
            char * nptr = needle;
            char * hptr = haystack;
            while(hptr < haystack + hlen && nptr < needle + nlen) {
                if(*nptr == *hptr) {nptr++; hptr++;}
                else hptr++;
            }
            /* printf("%d %d %d %d\n", hptr , haystack + hlen , nptr ,  needle + nlen); */
            if(nptr ==  needle + nlen)
                good = 1;
            else { 
                good = 0;
                assert(nptr < needle + nlen);
            }

        }
        else good = 0;

        if(good) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
