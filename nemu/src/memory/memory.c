#include "common.h"
#include<stdlib.h>
#include<time.h>
#include "nemu.h"
uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
        int i;
        uint32_t result=0;
        for(i=0;i<len;++i)
        {
             uint8_t temp=0;
             cache_read(addr+i,&temp);
             uint32_t atemp=temp;
             atemp=atemp<<(i*8);
             result+=atemp;
           
        }
        return result;
	//return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
	
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
        int i;
        uint32_t data_bk=data;
        for(i=0;i<len;++i)
        {
            uint8_t temp=data_bk&0x000000ff;
            data_bk=data_bk>>8;
            cache_write(addr+i,temp);
        }
	//dram_write(addr, len, data);
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

