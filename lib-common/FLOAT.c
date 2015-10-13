#include "FLOAT.h"
#include"trap.h"
FLOAT F_mul_F(FLOAT a, FLOAT b) {
	int temp=a*b;
	int bias=0;
	if(temp<0) bias=0x0000ffff;
	return (temp+bias)>>16;
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	nemu_assert(b!=0);
	int sign1=a&0x80000000;
	int sign2=b&0x80000000;
	if(sign1) a=-a;
	if(sign2) b=-b;
	int rel=a/b;
	int mod=a%b;
	FLOAT frel=int2F(rel);
	FLOAT fmod=int2F(mod);
	FLOAT result=F_div_int(fmod,F2int(b));
	return (sign1!=sign2)?-(frel+result):(frel+result);
}

FLOAT f2F(float a) {
	int* p=(int*)&a;
	int b=*p;
	int rel=0;
	int e=(b&0x7f800000)>>23;
	int m=(b&0x7fffff)|0x800000;
	e=e-127;
	if(e>=32) return 0x80000000;
	else if(e<0) return 0;
	else if(e>=23)
	{
		m=m<<(e-23);
	}
	else 
	{
		m=m>>(23-e);
	}
	if(b&0x80000000) rel=~m+1;
	else rel=m;
	return int2F(rel);
}

FLOAT Fabs(FLOAT a) {
	int sign=a&0x80000000;
	if(sign) a=-a;
	return a;
}

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);

	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

