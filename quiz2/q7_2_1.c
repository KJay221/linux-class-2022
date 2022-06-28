#include <stdio.h>
#include <stdint.h>

#define SIZE 1000000

static const char* s[] = {"", "Buzz", "Fizz", "FizzBuzz"};

int main() {
    char str[9];
    
    for(int i = 1; i <= SIZE; i++){
        uint64_t number = i;
        number = (number >> 32) + (number & 0xffffffff);
        number = (number >> 32) + ((number >> 16) & 0xffff) + (number & 0xffff);
        number = (number >> 16) + ((number >> 8) & 0xff) + (number & 0xff);
        number = (number >> 8) + ((number >> 4) & 0xf) + (number & 0xf);
        number = (number >> 4) + (number & 0xf);
        number ^= (number & 8) | ((number & 8) >> 1) | ((number & 8) >> 2) | ((number & 8) >> 3);
        if (number == 0) sprintf(str, "FizzBuzz");
        else if (number == 3 || number == 6) sprintf(str, "Fizz");
        else if (number == 5) sprintf(str, "Buzz");
        else sprintf(str, "%u", i);

        // number = (((number + (number >> 2)) + 3) & 3) &
        //             ~(((number ^ (number >> 1) ^ (number >> 2)) & 1) |
        //                 (((number ^ (number >> 1) ^ (number >> 2)) & 1) << 1));
    }
    
    return 0;
}