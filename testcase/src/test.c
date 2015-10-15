#include"trap.h"
#include"FLOAT.h"
int main()
{
	FLOAT f=f2F(0.5);
	nemu_assert(f==0x00008000);
	HIT_GOOD_TRAP;
	return 0;
}
