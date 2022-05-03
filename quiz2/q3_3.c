#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint64_t gcd64(uint64_t u, uint64_t v)
{
    if (!u || !v) return u | v;
    int shift = __builtin_ctz(u) ^ ((__builtin_ctz(u) ^ __builtin_ctz(v)) & -(__builtin_ctz(u) > __builtin_ctz(v)));
    u >>= __builtin_ctz(u);
    do {
        v >>= __builtin_ctz(v);
        if (u < v) {
            v -= u;
        } else {
            uint64_t t = u - v;
            u = v;
            v = t;
        }
    } while (v);
    return u << shift;
}

int main(){
    srand(time(0));
    uint64_t data[200000] = {0};
    for(int i = 0; i<200000; i++)
        data[i] = rand();

    for(int i = 0;i < 200000;i += 2)
        gcd64(data[i],data[i+1]);

    return 0;
}