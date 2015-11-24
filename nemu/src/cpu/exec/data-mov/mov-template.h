#include "cpu/exec/template-start.h"
#include "mmu.h"
#define instr mov
uint32_t lnaddr_read(lnaddr_t addr,size_t len);
static void do_execute() {
        
	if(ops_decoded.opcode==0x8e) 
	{
	  if(op_dest->reg==0)
	  {
	    cpu.ES.seg_selector=op_src->val;
	    SegDesc segdesc;
	    int index=(cpu.ES.seg_selector&0xfff8)>>3;
	    lnaddr_t seg_addr = cpu.GDTR.base_addr+index*8;
	    uint32_t low=lnaddr_read(seg_addr,4);
	    uint32_t high=lnaddr_read(seg_addr+4,4);
	    segdesc.low=low;
	    segdesc.high=high;
	    cpu.ES.base_addr=(uint32_t)segdesc.base_15_0 + (((uint32_t)segdesc.base_23_16)<<16) + (((uint32_t)segdesc.base_31_24)<<24);
	    cpu.ES.limit=(uint32_t)segdesc.limit_15_0 + (((uint32_t)segdesc.limit_19_16)<<16);
	  }
	  else if(op_dest->reg==1)
	  {
	    cpu.CS.seg_selector=op_src->val;
	    SegDesc segdesc;
	    int index=(cpu.CS.seg_selector&0xfff8)>>3;
	    lnaddr_t seg_addr = cpu.GDTR.base_addr+index*8;
	    uint32_t low=lnaddr_read(seg_addr,4);
	    uint32_t high=lnaddr_read(seg_addr+4,4);
	    segdesc.low=low;
	    segdesc.high=high;
	    cpu.CS.base_addr=(uint32_t)segdesc.base_15_0 + (((uint32_t)segdesc.base_23_16)<<16) + (((uint32_t)segdesc.base_31_24)<<24);
	    cpu.CS.limit=(uint32_t)segdesc.limit_15_0 + (((uint32_t)segdesc.limit_19_16)<<16);
	  }
	  else if(op_dest->reg==2)
	  {
	    cpu.SS.seg_selector=op_src->val;
	    SegDesc segdesc;
	    int index=(cpu.SS.seg_selector&0xfff8)>>3;
	    lnaddr_t seg_addr = cpu.GDTR.base_addr+index*8;
	    uint32_t low=lnaddr_read(seg_addr,4);
	    uint32_t high=lnaddr_read(seg_addr+4,4);
	    segdesc.low=low;
	    segdesc.high=high;
	    cpu.SS.base_addr=(uint32_t)segdesc.base_15_0 + (((uint32_t)segdesc.base_23_16)<<16) + (((uint32_t)segdesc.base_31_24)<<24);
	    cpu.SS.limit=(uint32_t)segdesc.limit_15_0 + (((uint32_t)segdesc.limit_19_16)<<16);
	  }
	  else if(op_dest->reg==3)
	  {
	    cpu.DS.seg_selector=op_src->val;
	    SegDesc segdesc;
	    int index=(cpu.DS.seg_selector&0xfff8)>>3;
	    lnaddr_t seg_addr = cpu.GDTR.base_addr+index*8;
	    uint32_t low=lnaddr_read(seg_addr,4);
	    uint32_t high=lnaddr_read(seg_addr+4,4);
	    segdesc.low=low;
	    segdesc.high=high;
	    cpu.DS.base_addr=(uint32_t)segdesc.base_15_0 + (((uint32_t)segdesc.base_23_16)<<16) + (((uint32_t)segdesc.base_31_24)<<24);
	    cpu.DS.limit=(uint32_t)segdesc.limit_15_0 + (((uint32_t)segdesc.limit_19_16)<<16);
	  }
	}   
	else 
	{
	  OPERAND_W(op_dest, op_src->val);
	  print_asm_template2();
	}  
}

make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

make_helper(concat(mov_a2moffs_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	MEM_W(addr, REG(R_EAX),2);
	print_asm("mov" str(SUFFIX) " %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}

make_helper(concat(mov_moffs2a_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	REG(R_EAX) = MEM_R(addr,2);

	print_asm("mov" str(SUFFIX) " 0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}

#include "cpu/exec/template-end.h"
