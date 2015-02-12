#include<map>
#include<stdio.h>
#include<assert.h>

#define mili std::map<int, long long int> 

long long int getMore(mili & m, int & max, int num)
{
    long long int i;
    long long int maxl = 0;
    if(max > 0) {
        mili::iterator it = m.find(max);
        assert(it != m.end());
        maxl = it->second;
    }
    for(i = max + 1; i <= num; i++) {
        maxl += i * i * i;
        m.insert(std::make_pair(i, maxl));
    }

    max = num;
    return maxl;
}
int main()
{
    int max = 0;
    int num;
    mili m;
    while(scanf("%d\n", &num) != EOF) {
        if(num > max) {
            printf("%lld\n", getMore(m, max, num));
            continue;
        }
        mili::iterator it = m.find(num);
        assert(it != m.end());
        printf("%lld\n", it->second);
    }
    return 0;
}
