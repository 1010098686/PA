#include "common.h"
#include<stdlib.h>
#include<time.h>
#include "nemu.h"
uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
        int num;
        if(hit(addr,&num))
        {
          int offset=cache_offset(addr);
          int i;
          uint32_t result=0;
          for(i=offset+len-1;i>=offset;--i)
          {
            result=(result<<8)+cpu.cache.cache_group[cache_index(addr)].cache_block[num].data[i];
          }
          return result;
        }
        else
        {
          hwaddr_t newaddr=addr&0xffffffc0;
          int _index=-1;
          int i;
          for(i=0;i<8;++i) if(cpu.cache.cache_group[cache_index(newaddr)].cache_block[i].valid==0) _index=i;
          if(_index==-1) 
          {
            srand(time(NULL));
            _index=rand()%8;
          }
          cpu.cache.cache_group[cache_index(newaddr)].cache_block[_index].tag=cache_tag(newaddr);
          cpu.cache.cache_group[cache_index(newaddr)].cache_block[_index].valid=1;
          for(i=0;i<64;++i)
          {
            uint8_t temp=dram_read(newaddr+i,1)&0xff;
            cpu.cache.cache_group[cache_index(newaddr)].cache_block[_index].data[i]=temp;
          }
	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
	}
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
        int num;
        if(hit(addr,&num))
        {
          int offset=cache_offset(addr);
          uint32_t data_bk = data;
          int i;
          for(i=offset;i<offset+len;++i)
          {
             uint8_t temp=data_bk&0xff;
             data_bk=data_bk>>8;
             cpu.cache.cache_group[cache_index(addr)].cache_block[num].data[i]=temp;
          }
        }
	dram_write(addr, len, data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	return lnaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_write(addr, len, data);
}

