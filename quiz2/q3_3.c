#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b) \
    do { \
        a ^= b; \
        b ^= a; \
        a ^= b; \
    } while (0)

unsigned long gcd1(unsigned long a, unsigned long b)
{
	unsigned long r = a | b;

	if (!a || !b)
		return r;
	r &= -r;

	while (!(b & r))
		b >>= 1;
	if (b == r)
		return r;

	for (;;) {
		while (!(a & r))
			a >>= 1;
		if (a == r)
			return r;
		if (a == b)
			return a;
		if (a < b)
            swap(a, b);		
		a -= b;
		a >>= 1;
		if (a & r)
			a += b;
		a >>= 1;
    }
}

unsigned long gcd2(unsigned long a, unsigned long b)
{
	unsigned long r = a | b;

	if (!a || !b)
		return r;
	r &= -r;

	while (!(b & r))
		b >>= 1;
	if (b == r)
		return r;

	for (;;) {
		while (!(a & r))
			a >>= 1;
		if (a == r)
			return r;
		if (a == b)
			return a;
		if (a < b)
            swap(a, b);
        a -= b;		
    }
}

int main(){
    srand(time(0));
    uint64_t data[200000] = {0};
    for(int i = 0; i<200000; i++)
        data[i] = rand();
    
    clock_t start_t,finish_t;
    double total_t = 0;

    start_t = clock();
    for(int i = 0;i < 200000;i += 2)
        gcd1(data[i],data[i+1]);
    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    printf("time: %f s\n", total_t);

    start_t = clock();
    for(int i = 0;i < 200000;i += 2)
        gcd2(data[i],data[i+1]);
    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    printf("time: %f s\n", total_t);

    return 0;
}