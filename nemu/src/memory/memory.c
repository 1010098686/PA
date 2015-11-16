#include "common.h"
#include<stdlib.h>
#include<time.h>
uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);

/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
        /*int num;
        if(hit(addr,&num)
        {
          int offset=addr&0xffff3f+len;
          int i;
          uint32_t result=0;
          for(i=offset-1;i>=addr&0xffff3f;--i)
          {
            result=result<<8+cache.cache_group[index(addr)].cache_block[num].data[i];
          }
          return result;
        }
        else
        {*/
          
	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
	//}
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
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

