#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define SIZE 10000

static inline bool is_divisible(uint32_t n, uint64_t M)
{
    return n * M <= M - 1;
}

static uint64_t M3 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 3 + 1;
static uint64_t M5 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 5 + 1;

int main() {
    clock_t start_t,finish_t;
    double total_t = 0;
    char str[10];
    
    start_t = clock();
    for (unsigned int i = 1; i < SIZE; i++) {
        if (i % 3 == 0) { sprintf(str, "Fizz"); puts(str); }
        if (i % 5 == 0) { sprintf(str, "Buzz"); puts(str); }
        if ((i % 3) && (i % 5)) { sprintf(str, "%u", i); puts(str); }
    }
    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    printf("time: %f s\n", total_t);

    return 0;
}