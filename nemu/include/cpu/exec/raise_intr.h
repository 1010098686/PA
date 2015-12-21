#ifndef RAISE_INTR_H
#define RAISE_INTR_H

#include <setjmp.h>
#include "mmu.h"
#include "nemu.h"

extern jmp_buf jbuf;

void raise_intr(uint8_t NO)
{
  cpu.esp = cpu.esp -1;
  swaddr_write(cpu.esp,1,cpu.eflags.val,1);
  cpu.esp = cpu.esp - 2;
  swaddr_write(cpu.esp,2,cpu.CS.seg_selector,1);
  cpu.esp = cpu.esp -4;
  swaddr_write(cpu.esp,4,cpu.eip+2,1);
  GateDesc gatedesc;
  lnaddr_t addr = cpu.IDTR.base_addr + NO *8;
  uint32_t low = lnaddr_read(addr,4);
  uint32_t high = lnaddr_read(addr+4,4);
  gatedesc.low = low;
  gatedesc.high = high;
  cpu.CS.seg_selector = gatedesc.segment;
  SegDesc segdesc;
  int index=(cpu.CS.seg_selector&0xfff8)>>3;
  lnaddr_t seg_addr = cpu.GDTR.base_addr+index*8;
  low=lnaddr_read(seg_addr,4);
  high=lnaddr_read(seg_addr+4,4);
  segdesc.low=low;
  segdesc.high=high;
  cpu.CS.base_addr=(uint32_t)segdesc.base_15_0 + (((uint32_t)segdesc.base_23_16)<<16) + (((uint32_t)segdesc.base_31_24)<<24);
  cpu.CS.limit=(uint32_t)segdesc.limit_15_0 + (((uint32_t)segdesc.limit_19_16)<<16);
  uint32_t eip = (uint32_t)gatedesc.offset_15_0 + (((uint32_t)gatedesc.offset_31_16)<<16) + cpu.CS.base_addr;
  cpu.eip = eip;
  longjmp(jbuf ,1 );
}

#endif
