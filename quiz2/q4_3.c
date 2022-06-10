#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

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

size_t my_improve_1(uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        size_t p = k << 6;
        for (int i = 0; i < 64; i+=2) {
            switch ((bitset >> i) & 0x3){
                case 1:
                    out[pos++] = p | i;
                    break;
                case 2:
                    out[pos++] = p | (i + 1);
                    break;
                case 3:
                    out[pos++] = p | i;
                    out[pos++] = p | (i + 1);
                    break;
            }              
        }
    }
    return pos;
}

size_t my_improve_2(uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        size_t p = k << 6;
        for (int i = 0; i < 64; i+=4) {
            switch ((bitset >> i) & 0xf){
                case 1:
                    out[pos++] = p | i;
                    break;
                case 2:
                    out[pos++] = p | (i + 1);
                    break;
                case 3:
                    out[pos++] = p | i;
                    out[pos++] = p | (i + 1);
                    break;
                case 4:
                    out[pos++] = p | (i + 2);
                    break;
                case 5:
                    out[pos++] = p | i;
                    out[pos++] = p | (i + 2);
                    break;
                case 6:
                    out[pos++] = p | (i + 1);
                    out[pos++] = p | (i + 2);
                    break;
                case 7:
                    out[pos++] = p | i;
                    out[pos++] = p | (i + 1);
                    out[pos++] = p | (i + 2);
                    break;
                case 8:
                    out[pos++] = p | (i + 3);
                    break;
                case 9:
                    out[pos++] = p | i;
                    out[pos++] = p | (i + 3);
                    break;
                case 10:
                    out[pos++] = p | (i + 1);
                    out[pos++] = p | (i + 3);
                    break;
                case 11:
                    out[pos++] = p | i;
                    out[pos++] = p | (i + 1);
                    out[pos++] = p | (i + 3);
                    break;
                case 12:
                    out[pos++] = p | (i + 2);
                    out[pos++] = p | (i + 3);
                    break;
                case 13:
                    out[pos++] = p | i;
                    out[pos++] = p | (i + 2);
                    out[pos++] = p | (i + 3);
                    break;
                case 14:
                    out[pos++] = p | (i + 1);
                    out[pos++] = p | (i + 2);
                    out[pos++] = p | (i + 3);
                    break;
                case 15:
                    out[pos++] = p | i;
                    out[pos++] = p | (i + 1);
                    out[pos++] = p | (i + 2);
                    out[pos++] = p | (i + 3);
                    break;
            }                
        }
    }
    return pos;
}

int main(int argc, char *argv[]){
    int size = atoi(argv[1]);
    FILE *txt;
    txt = fopen("q4_3.txt","w");
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

           
        clock_t start_t,finish_t;
        double total_t = 0;

        //test improve time
        uint32_t *output1 = malloc(32*density*size);
        start_t = clock();
        improved(data, size, output1);
        finish_t = clock();
        total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
        fprintf(txt, "%f ", total_t);
        free(output1);

        //test my_improve_1 time
        uint32_t *output2 = malloc(32*density*size);
        start_t = clock();
        my_improve_1(data, size, output2);
        finish_t = clock();
        total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
        fprintf(txt, "%f ", total_t);
        free(output2);

        //test my_improve_2 time
        uint32_t *output3 = malloc(32*density*size);
        start_t = clock();
        my_improve_2(data, size, output3);
        finish_t = clock();
        total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
        fprintf(txt, "%f\n", total_t);
        free(output3);
        
        // for(int i = 0;i < size; ++i){
        //     if(output1[i] != output2[i])
        //         printf("error");
        //     if(output1[i] != output3[i])
        //         printf("error");
        // }

        free(data);
    }
    fclose(txt);
}