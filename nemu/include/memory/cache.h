#ifndef CACHE_H
#define CACHE_H
#include"nemu.h"
typedef struct 
{
  unsigned int valid;
  unsigned int tag;
  uint8_t data[64];
}Cache_block;

typedef struct 
{
  Cache_block cache_block[8];
}Cache_group;

typedef struct 
{
  Cache_group cache_group[128];
}Cache;
extern Cache cache;

#define cache_index(addr) ((addr)&0x00001fc0)>>6
#define cache_tag(addr) ((addr)&0xffffe000)>>13
#define cache_offset(addr) ((addr)&0x0000003f)
static void cache_misspro(hwaddr_t addr);
static void cachel2_write(hwaddr_t, uint8_t);
static void cachel2_read(hwaddr_t,uint8_t*);
static inline int hit(hwaddr_t addr,int* num)
{
    int i;
    for(i=0;i<8;++i) 
    {
      if(cache.cache_group[cache_index(addr)].cache_block[i].tag==cache_tag(addr) && cache.cache_group[cache_index(addr)].cache_block[i].valid==1) 
      {
        *num=i;
        return 1;
      }
    }
    return 0;
}
static inline void cache_read(hwaddr_t addr,uint8_t* result)
{
   int num=-1;
   if(hit(addr,&num))
   {
    int offset=cache_offset(addr);
    *result = cache.cache_group[cache_index(addr)].cache_block[num].data[offset];
   }
   else 
   {
     cache_misspro(addr);
     hit(addr,&num);
     int offset=cache_offset(addr);
     *result=cache.cache_group[cache_index(addr)].cache_block[num].data[offset];
    }
   
}
static inline void cache_write(hwaddr_t addr,uint8_t data)
{
  int num=-1;
  if(hit(addr,&num))
  {
   int offset=cache_offset(addr);
   cache.cache_group[cache_index(addr)].cache_block[num].data[offset]=data;
  }
  cachel2_write(addr,data);
  
}

static inline void cache_misspro(hwaddr_t addr)
{
   int num=-1;
   int i;
   hwaddr_t newaddr=addr&0xffffffc0;
   for(i=0;i<8;++i)
   {
      if(cache.cache_group[cache_index(addr)].cache_block[i].valid==0) num=i;
   }
   if(num==-1)
   {
     srand(time(NULL));
     num=rand()%8;
    }
    cache.cache_group[cache_index(addr)].cache_block[num].valid=1;
    cache.cache_group[cache_index(addr)].cache_block[num].tag=cache_tag(addr);
    for(i=0;i<64;++i)
    {
      uint8_t temp;
      cachel2_read(newaddr+i,&temp);
      cache.cache_group[cache_index(addr)].cache_block[num].data[i]=temp;
    }
} 
#endif
