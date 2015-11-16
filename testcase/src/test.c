#include"trap.h"
uint8_t ans[0,1,2,3,4,5,6,7,8,9};

int main()
{
  int i;
  for(i=0;i<10;++i)
    nemu_assert(i==ans[i]);
  HIT_GOOD_TRAP;
  return 0;
}
