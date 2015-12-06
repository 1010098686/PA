#include "common.h"
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "nemu.h"
#include "mmu.h"
uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
uint32_t lnaddr_read(lnaddr_t addr, size_t len);
uint32_t hwaddr_read(hwaddr_t addr, size_t len);
lnaddr_t seg_translate(swaddr_t addr,size_t len,uint8_t sreg,int* flag)
{
   uint32_t base_addr,limit;
   switch(sreg)
   {
     case 0:base_addr=cpu.CS.base_addr;limit=cpu.CS.limit;break;
     case 1:base_addr=cpu.SS.base_addr;limit=cpu.SS.limit;break;
     case 2:base_addr=cpu.DS.base_addr;limit=cpu.DS.limit;break;
     case 3:base_addr=cpu.ES.base_addr;limit=cpu.ES.limit;break;
     default:*flag=0;return 0;
   }
   if(addr+len>limit*4096)
   {
     *flag=0;
     return 0;
   }
   *flag=1;
   return base_addr+addr;
}
hwaddr_t page_translate(lnaddr_t addr,int* flag)
{
   PDE pdir;
   pdir.val=hwaddr_read((cpu.CR3.page_directory_base<<12)+((addr>>22)&0x000003ff)*4,4);
//   printf("0x%x\n",pdir.val);
//   printf("0x%x\n",pdir.present);
   if(pdir.present==0) { *flag=-1; return 0;}
   PTE ptable;
   ptable.val=hwaddr_read((pdir.page_frame<<12)+((addr>>12)&0x000003ff)*4,4);
//   printf("0x%x\n",ptable.val);
   if(ptable.present==0) {*flag=0; return 0;}
   *flag=1;
   return (((uint32_t)ptable.page_frame)<<12)+(addr&0x00000fff);
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
	if(cpu.CR0.protect_enable==1 && cpu.CR0.paging==1)
	{
	  /*int i;
	  uint32_t result=0;
	  for(i=0;i<len;++i)
	  {
	    int flag;
	    hwaddr_t ph_addr=page_translate(addr+i,&flag);
	    if(flag==-1) panic("lnaddr read error1:0x%x",addr+i);
	    else if(flag==0) panic("lnaddr read error2:0x%x",addr+i);
	    uint32_t temp=hwaddr_read(ph_addr,1);
	    result=result+(temp<<(i*8));
	  }
	  return result;*/
    if((addr&0x00000fff)+len >= 0x00001000); //panic("page error");
    int flag;
    hwaddr_t ph_addr = page_translate(addr,&flag);
    if(flag!=1) panic("lnaddr_read error");
    return hwaddr_read(ph_addr,len);
	}
        else return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	if(cpu.CR0.protect_enable==1 && cpu.CR0.paging==1)
	{
	  /*int i;
	  uint32_t data_bk=data;
	  for(i=0;i<len;++i)
	  {
	    int flag;
	    hwaddr_t ph_addr = page_translate(addr+i,&flag);
	    if(flag==-1) panic("lnaddr write error1:0x%x",addr+i);
	    else if(flag==0) panic("lnaddr write error2:0x%x",addr+i);
	    uint8_t temp=data_bk&0xff;
	    data_bk=data_bk>>8;
	    hwaddr_write(ph_addr,1,temp);*/
      if((addr&0x00000fff)+len >= 0x00001000); //panic("page error");
      int flag;
      hwaddr_t ph_addr = page_translate(addr,&flag);
      if(flag!=1) panic("lnaddr_write error");
      hwaddr_write(ph_addr,len,data);
	  //}
	 }
	 else hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, size_t len,uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	if(cpu.CR0.protect_enable==1)
	{
	  int flag;
	  lnaddr_t li_addr=seg_translate(addr,len,sreg,&flag);
	  if(!flag) panic("swaddr_read error\n");
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
	  if(!flag) panic("swaddr_write error\n");
	  else lnaddr_write(li_addr, len,data);
	}
	else lnaddr_write(addr, len, data);
}
