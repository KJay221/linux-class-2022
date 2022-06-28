#include <stdio.h>

#define SIZE 1000000

int main() {
    char str[9];
    
    for (unsigned int i = 1; i <= SIZE; i++) {
        if (i % 15 == 0) sprintf(str, "FizzBuzz");
        else if (i % 3 == 0) sprintf(str, "Fizz");
        else if (i % 5 == 0) sprintf(str, "Buzz");
        else if ((i % 3) && (i % 5)) sprintf(str, "%u", i);
    }
    
    return 0;
}