#ifndef CACHEL2_H
#define CACHEL2_H
#include<stdlib.h>
#include<time.h>
typedef struct 
{
  unsigned int valid;
  unsigned int dirty;
  unsigned int tag;
  uint8_t data[64];
}Cachel2_block;

typedef struct
{
  Cachel2_block cachel2_block[16];
}Cachel2_group;

typedef struct
{
  Cachel2_group cachel2_group[4096];
}Cachel2;

extern Cachel2 cachel2;

#define cachel2_index(addr) ((addr)&0x0003ffc0)>>6
#define cachel2_tag(addr) ((addr)&0xfffc0000)>>18
#define cachel2_offset(addr) ((addr)&0x0000003f)
static void cachel2_misspro(hwaddr_t addr);

static inline int cachel2_hit(hwaddr_t addr,int* num)
{
  int i=0;
  for(i=0;i<16;++i) 
    if(cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[i].tag==cachel2_tag(addr) && cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[i].valid==1) 
    {
      *num=i;
      return 1;
    }
  return 0;
}

static inline void cachel2_read(hwaddr_t addr,uint8_t* result)
{
  int num=-1;
  if(cachel2_hit(addr,&num))
  {
   int offset=cachel2_offset(addr);
   *result = cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].data[offset];
  }
  else
  {
    cachel2_misspro(addr);
    cachel2_hit(addr,&num);
    int offset=cachel2_offset(addr); 
    *result=cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].data[offset];
  }
}

static inline void cachel2_write(hwaddr_t addr,uint8_t data)
{
  int num=-1;
  if(cachel2_hit(addr,&num))
  {
   int offset=cachel2_offset(addr);
   cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].data[offset]=data;
   cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].dirty=1;
   }
   else
   {
     cachel2_misspro(addr);
     cachel2_hit(addr,&num);
     int offset=cachel2_offset(addr);
     cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].data[offset]=data;
     cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].dirty=1;
   }
}

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
static inline void cachel2_misspro(hwaddr_t addr)
{
  int num=-1;
  int i;
  hwaddr_t newaddr=addr&0xffffffc0;
  for(i=0;i<16;++i)
   if(cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[i].valid==0) num=i;
  if(num==-1) 
  {
    srand(time(NULL));
    num=rand()%16;
    if(cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].dirty==1)
    {
       int j;
	   uint32_t tag = cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].tag;
	   tag = tag <<18;
	   uint32_t index = cachel2_index(addr);
	   index = index<<6;
	   hwaddr_t waddr = tag + index;
       for(j=0;j<64;++j)
       {
         uint32_t temp=cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].data[j];
         dram_write(waddr+j,1,temp);
       }
    }
    
  }
  cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].valid=1;
  cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].dirty=0;
  cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].tag=cachel2_tag(addr);
  for(i=0;i<64;++i)
   cachel2.cachel2_group[cachel2_index(addr)].cachel2_block[num].data[i]=dram_read(newaddr+i,1);
}

#endif
