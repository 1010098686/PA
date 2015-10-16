#include "trap.h"
#include "FLOAT.h"
FLOAT src=0;
FLOAT dest=0;
FLOAT f(FLOAT x) { 
	/* f(x) = 1/(1+25x^2) */
	return F_div_F(int2F(1), int2F(1) + F_mul_int(F_mul_F(x, x), 25));
}

FLOAT computeT(int n, FLOAT a, FLOAT b, FLOAT (*fun)(FLOAT)) {
	int k;
	FLOAT s,h;
	h = F_div_int((b - a), n);
	s = F_div_int(fun(a) + fun(b), 2 );
	for(k = 1; k < n; k ++) {
		s += fun(a + F_mul_int(h, k));
	}
	s = F_mul_F(s, h);
	return s;
}

int main() { 
	 src = computeT(10, f2F(-1.0), f2F(1.0), f);
	 dest = f2F(0.551222);

	nemu_assert(Fabs(src - dest) < f2F(1e-4));
	HIT_GOOD_TRAP;
	return 0;
}
