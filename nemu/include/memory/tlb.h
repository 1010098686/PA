#ifndef TLB_H
#define TLB_H
#include "mmu.h"
#include <stdlib.h>
#include <time.h>
typedef struct
{
  unsigned int valid;
  unsigned int tag;
  PTE ptable;
}TLB_BLOCK;

typedef struct
{
  TLB_BLOCK tlb_block[64];
}TLB;

extern TLB tlb;

#define tlb_tag(addr)  ((addr)&0xfffff000)>>12

static inline int tlb_hit(lnaddr_t addr ,int* num)
{
  int i;
  for(i=0; i<64 ;++i)
  {
    if(tlb.tlb_block[i].valid==1 && tlb.tlb_block[i].tag==tlb_tag(addr))
    {
      *num=i;
      return 1;
    }
  }
  return 0;
}

static inline PTE tlb_read(lnaddr_t addr)
{
  int num=0;
  tlb_hit(addr,&num);
  return tlb.tlb_block[num].ptable;
}

static inline void tlb_write(lnaddr_t addr , PTE ptable)
{
  int i;
  int num=-1;
  for(i=0;i<64;++i)
   if(tlb.tlb_block[i].valid==0) num=i;
  if(num==-1)
  {
    srand(time(NULL));
    num=rand()%64;
  }
  tlb.tlb_block[num].valid=1;
  tlb.tlb_block[num].tag=tlb_tag(addr);
  tlb.tlb_block[num].ptable=ptable;
}

static inline void clear_tlb()
{
   int i;
   for(i=0;i<64;++i) tlb.tlb_block[i].valid=0;
}
#endif
