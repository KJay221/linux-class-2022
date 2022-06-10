#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


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


int main(int argc, char *argv[]){
    int size = 10000;
    int density = 32;

    //generate data
    srand(time(0));
    uint64_t *data = calloc(size, sizeof(uint64_t));
    for(int i = 0;i < size; ++i){
        for(int j = 0;j < density; ++j){
            while(1){
                int setbit = rand() % 64;
                if(!(data[i] & 1UL << setbit)){
                    data[i] |= 1UL << setbit;
                    break;
                }  
            }
        }
    }

    
    
    clock_t start_t,finish_t;
    double total_t = 0;
    for(int i = 0;i < 100; ++i){
        uint32_t *output = malloc(32*density*size);
        naive(data, size, output);
        free(output);
    }
    
    free(data);
}