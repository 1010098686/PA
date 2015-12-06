#ifndef TLB_H
#define TLB_H
#include "mmu.h"
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

#endif
