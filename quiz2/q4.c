#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

size_t naive(uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    for (size_t k = 0; k < bitmapsize; ++k) {
        uint64_t bitset = bitmap[k];
        size_t p = k * 64;
        for (int i = 0; i < 64; i++) {
            if ((bitset >> i) & 0x1)
                out[pos++] = p + i;
        }
    }
    return pos;
}

size_t improved(uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        while (bitset != 0) {
            uint64_t t = -bitset & bitset;
            int r = __builtin_ctzll(bitset);
            out[pos++] = k * 64 + r;
            bitset ^= t;                           
        }
    }
    return pos;
}

int main(){
    uint64_t bitmap[3] = {0x0a21, 0xf043, 0xff0f};
    uint32_t out[30] = {0};
    printf("naive\npos:%ld\n", naive(bitmap, 3, out));
    for(int i = 0;i < 30;++i)
        printf("out %d:%d\n", i, out[i]);
    printf("\nimproved\npos:%ld\n", improved(bitmap, 3, out));
    for(int i = 0;i < 30;++i)
        printf("out %d:%d\n", i, out[i]);
}