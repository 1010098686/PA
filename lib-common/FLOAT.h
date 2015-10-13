#ifndef __FLOAT_H__
#define __FLOAT_H__

#include "trap.h"
typedef int FLOAT;

static inline int F2int(FLOAT a) {
	int sign=a&0x80000000;
	if(sign) a=-a;
	a=a>>16;
	if(sign) a=-a;
	return a;
}

static inline FLOAT int2F(int a) {
    int sign=a&0x80000000;
	if(sign) a=-a;
	a=a<<16;
	if(sign) a=-a;
	return a;
}

static inline FLOAT F_mul_int(FLOAT a, int b) {
	return a*b;
}

static inline FLOAT F_div_int(FLOAT a, int b) {
    nemu_assert(b!=0);
	return a/b;
}

FLOAT f2F(float);
FLOAT F_mul_F(FLOAT, FLOAT);
FLOAT F_div_F(FLOAT, FLOAT);
FLOAT Fabs(FLOAT);
FLOAT sqrt(FLOAT);
FLOAT pow(FLOAT, FLOAT);

#endif
