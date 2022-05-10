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

int main(int argc, char *argv[]){
    int size = atoi(argv[1]);
    FILE *txt;
    txt = fopen("q4_2.txt","w");
    if(!txt){
        printf("open failure");
        return 1;
    }

    for(int density = 1;density <= 64; ++density){
        fprintf(txt, "%d ", density);
        printf("%d\n",density);

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

        
        uint32_t *output = malloc(32*density*size);
        clock_t start_t,finish_t;
        double total_t = 0;

        //test naive time
        start_t = clock();
        for(int i = 0;i < size; ++i)
            naive(data, size, output);
        finish_t = clock();
        total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
        fprintf(txt, "%f ", total_t);

        //test improve time
        start_t = clock();
        for(int i = 0;i < size; ++i)
            improved(data, size, output);
        finish_t = clock();
        total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
        fprintf(txt, "%f\n", total_t);

        free(output);
        free(data);
    }
    fclose(txt);
}