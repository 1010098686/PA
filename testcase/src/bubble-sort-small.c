#include"trap.h"

#define N 10

int a[N]={5,8,3,6,9,7,1,0,2,4};

void bubble_sort()
{
	int i,j,t;
	for(j=0;j<N;j++)
	{
		for(i=0;i<N-1-j;i++)
		{
			if(a[i]>a[i+1])
			{
				t=a[i];
				a[i]=a[i+1];
				a[i+1]=t;
			}
		}
	}
}

int main()
{
	bubble_sort();
	int i;
	for(i=0;i<N;++i)
	{
		nemu_assert(a[i]==i);
	}
	bubble_sort();
	for(i=0;i<N;++i)
	{
		nemu_assert(a[i]==i);
	}

	HIT_GOOD_TRAP;
	return 0;
}
