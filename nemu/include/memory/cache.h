#ifndef __CACHE_H__
#define __CACHE_H__

#include "common.h"
typedef struct 
{
   unsigned int valid:1;
   unsigned int tag:11;
   int8_t block[64];
} Cache_block;

typedef struct 
{
   Cache_block cache_block[8];
} Cache_group;

typedef struct 
{
  Cache_group cache_group[128];
} Cache;

 Cache cache;

#endif
