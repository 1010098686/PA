#ifndef CACHEL2_H
#define CACHEL2_H

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

