#include"trap.h"

int main()
{
	int i,j;
	unsigned ui,uj;
	i=2;
	j=-1;
	if(i>j)
	{
		if(i>=j)
		{
			ui=3;
			uj=2;
			if(ui>uj) HIT_GOOD_TRAP;
		}
		else nemu_assert(0);
	}
	else nemu_assert(0);
	HIT_GOOD_TRAP;
	return 0;
}
