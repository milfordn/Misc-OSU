#include "mt19937.h"

char canUseRdRand = -1;

int rand(int low, int hi){
	unsigned long rdn;

	if(canUseRdRand < 0){
		unsigned int eax, ebx, ecx, edx;
		eax = 0x01;

		__asm__ __volatile__ (
		"cpuid;"
			: "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
			: "a"(eax)
		);

		if(ecx & 0x40000000){
			canUseRdRand = 1;
			puts("rdrand");
		}
		else{
			canUseRdRand = 0;
		}
	}

	if(canUseRdRand){
		__asm__ __volatile__ (
		"rdrand %0"
			: "=r"(rdn)
		);
	}
	else {
		rdn = genrand_int32();
	}

	rdn %= (hi - low);
	rdn += low;
	return (int)rdn;
}
