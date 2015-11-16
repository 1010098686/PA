#include"trap.h"
unsigned char  ans[]={0,1,2,3,4,5,6,7,8,9};

int main()
{
  unsigned char i=0;
  nemu_assert(i==ans[0]);
  for(i=0;i<10;++i) ans[i]=9-i;
  for(i=0;i<10;++i) nemu_assert(ans[i]==9-i);
  HIT_GOOD_TRAP;
  return 0;
}
