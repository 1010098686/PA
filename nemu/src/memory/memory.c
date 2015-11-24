#include "common.h"
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "nemu.h"
#include "mmu.h"
uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
uint32_t lnaddr_read(lnaddr_t addr, size_t len);
lnaddr_t seg_translate(swaddr_t addr,size_t len,uint8_t sreg,int* flag)
{
  uint16_t selector=0; 
  switch(sreg)
   {
   case 0: selector=cpu.CS.seg_selector;break;
   case 1: selector=cpu.SS.seg_selector;break;
   case 2: selector=cpu.DS.seg_selector;break;
   case 3: selector=cpu.ES.seg_selector;break;
   default:*flag=0;return 0;break;
   }
   uint16_t index=(selector&0xfff8)>>3;
   SegDesc segdesc;
   uint32_t desc_addr=cpu.GDTR.base_addr+index*8;
   uint32_t low=lnaddr_read(desc_addr,4);
   uint32_t high=lnaddr_read(desc_addr+4,4);
   segdesc.low=low;
   segdesc.high=high;
   uint32_t base_addr=(uint32_t)segdesc.base_15_0 + (((uint32_t)segdesc.base_23_16)<<16) + (((uint32_t)segdesc.base_31_24)<<24);
   uint32_t dpl=segdesc.privilege_level;
   uint32_t cpl=selector&0x0003;
   if(cpl<dpl) {*flag=0;return 0;}
   lnaddr_t linear_addr=base_addr+addr;
   lnaddr_t limit_addr=(uint32_t)segdesc.limit_15_0 + (((uint32_t)segdesc.limit_19_16)<<16);
   if(linear_addr+len>limit_addr){ *flag=0;return 0;}
   *flag=1;
   return linear_addr;
}
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
	if(cpu.CR0.protect_enable==1)
	{
	  int flag;
	  lnaddr_t li_addr=seg_translate(addr,len,sreg,&flag);
	  if(!flag) panic("error\n");
	  else return lnaddr_read(li_addr, len);
	}
	else return lnaddr_read(addr,len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data,uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	if(cpu.CR0.protect_enable==1)
	{
	  int flag;
	  lnaddr_t li_addr = seg_translate(addr,len,sreg,&flag);
	  if(!flag) panic("error\n");
	  else lnaddr_write(li_addr, len,data);
	}
	else lnaddr_write(addr, len, data);
}

