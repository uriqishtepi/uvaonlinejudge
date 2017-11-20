#include <uuid/uuid.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define N 2000
short res[N][2];

void *g(void *_)
{
    uuid_t u;
    for (int i = 0; i < 1000000; ++i)
        uuid_generate(u);
}

/* combine hashes similar to hash_combine from boost library */
unsigned long long val_combine(unsigned long long lhs, unsigned long long rhs)
{
    lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
    return lhs;
}

void *f(void *arg)
{
    int i = (int)arg;
    unsigned int tmp[2];
    tmp[0] = 11111;
    tmp[1] = 11111;
    unsigned long long hash = val_combine(*(unsigned long long *)tmp, (unsigned long long)pthread_self());
    short bla[3];
    bla[0] = hash;
    bla[1] = hash >> 16;
    bla[2] = hash >> 32;
    res[i][0] = bla[0];
    res[i][1] = bla[1];
    res[i][2] = bla[2];
}

int main()
{
    pthread_t t[N];
    for (int i = 0; i < N; ++i)
        pthread_create(&t[i], NULL, f, i);
    void *r;
    for (int i = 0; i < N; ++i)
        pthread_join(t[i], &r);
    for (int i = 0; i < N; ++i)
        printf("%x %x %x\n", res[i][0], res[i][1], res[i][2]);
}
