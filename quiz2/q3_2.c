#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

uint64_t good_gcd64(uint64_t u, uint64_t v)
{
    if (!u || !v) return u | v;
    int shift = __builtin_ctz(u) ^ ((__builtin_ctz(u) ^ __builtin_ctz(v)) & -(__builtin_ctz(u) > __builtin_ctz(v)));
    u >>= __builtin_ctz(u);
    v >>= __builtin_ctz(v);
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

uint64_t gcd64(uint64_t u, uint64_t v)
{
    if (!u || !v) return u | v;
    while (v) {                               
        uint64_t t = v;
        v = u % v;
        u = t;
    }
    return u;
}

int main(){
    srand(time(0));
    uint64_t data[200000] = {0};
    for(int i = 0; i<200000; i++)
        data[i] = rand();
    
    clock_t start_t,finish_t;
    double total_t = 0;

    //use __builtin_ctz()
    start_t = clock();
    for(int i =0;i<200000;i+=2){
        good_gcd64(data[i],data[i+1]);
    }
    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    printf("time: %f s\n", total_t);

    //origin
    start_t = clock();
    for(int i =0;i<200000;i+=2){
        gcd64(data[i],data[i+1]);
    }
    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    printf("time: %f s\n", total_t);

    return 0;
}