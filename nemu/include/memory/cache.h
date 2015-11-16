#ifndef __CACHE_H__
#define __CACHE_H__

#include "common.h"
typedef struct 
{
   unsigned int valid:1;
   unsigned int tag:11;
   uint8_t data[64];
} Cache_block;

typedef struct 
{
   Cache_block cache_block[8];
} Cache_group;

typedef struct 
{
  Cache_group cache_group[128];
} Cache;

 extern Cache cache;
 
 #define cache_index(addr) ((addr)&0x001fc0)>>6
 #define tag(addr) ((addr)&0xffe000)>>13
 
 
 static inline bool hit(hwaddr_t addr,int*num)
 {
    int _index=cache_index(addr);
    int i;
    for(i=0;i<8;++i) 
    {
      if(cache.cache_group[_index].cache_block[i].tag==tag(addr) && cache.cache_group[_index].cache_block[i].valid==1) 
      {
        *num=i;
        return true;
      }
    }
    return false;
}

#endif
