#include "common.h"
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "nemu.h"
#include "mmu.h"
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

uint32_t swaddr_read(swaddr_t addr, size_t len,uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	uint16_t selector=0;
	switch(sreg)
	{
	  case 0: selector=cpu.CS.seg_selector;break;
	  case 1: selector=cpu.SS.seg_selector;break;
	  case 2: selector=cpu.DS.seg_selector;break;
	  case 3: selector=cpu.ES.seg_selector;break;
	}
	uint16_t index=(selector&0xfff8)>>3;
	SegDesc segdesc;
	memcpy((void*)&segdesc,(void*)0+cpu.GDTR.base_addr+index*8,8);
	uint32_t base_addr=segdesc.base_15_0 + segdesc.base_23_16 + segdesc.base_31_24;
	uint32_t dpl=segdesc.privilege_level;
	uint32_t cpl=selector&0xfffc;
	if(cpl<dpl) panic("error\n");
	lnaddr_t linear_addr=base_addr+addr;
	lnaddr_t limit_addr=segdesc.limit_15_0 + segdesc.limit_19_16;
	if(linear_addr+len>limit_addr) panic("error\n");
	return lnaddr_read(linear_addr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data,uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	uint16_t selector=0;
	switch(sreg)
	{
	  case 0: selector=cpu.CS.seg_selector;break;
	  case 1: selector=cpu.SS.seg_selector;break;
	  case 2: selector=cpu.DS.seg_selector;break;
	  case 3: selector=cpu.ES.seg_selector;break;
	}
	uint16_t index=(selector&0xfff8)>>3;
	SegDesc segdesc;
	memcpy((void*)&segdesc,(void*)0+cpu.GDTR.base_addr+index*8,8);
	uint32_t base_addr=segdesc.base_15_0 + segdesc.base_23_16 + segdesc.base_31_24;
	uint32_t dpl=segdesc.privilege_level;
	uint32_t cpl=selector&0xfffc;
	if(cpl<dpl) panic("error\n");
	lnaddr_t linear_addr=base_addr+addr;
	lnaddr_t limit_addr=segdesc.limit_15_0 + segdesc.limit_19_16;
	if(linear_addr+len>limit_addr) panic("error\n");
	lnaddr_write(addr, len, data);
}

