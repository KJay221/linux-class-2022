#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 1000000

static inline bool is_divisible(uint32_t n, uint64_t M)
{
    return n * M <= M - 1;
}

static uint64_t M3 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 3 + 1;
static uint64_t M5 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 5 + 1;

int main() {
    char str[9];

    for (size_t i = 1; i <= SIZE; i++) {
        uint8_t div3 = is_divisible(i, M3);
        uint8_t div5 = is_divisible(i, M5);
        unsigned int length = (2 << div3) << div5;

        char fmt[9];
        strncpy(fmt, &"FizzBuzz%u"[(8 >> div5) >> (div3 << 2)], length);
        fmt[length] = '\0';

        sprintf(str, fmt, i);
    }
    
    return 0;
}