#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"

make_helper(nop) {
	print_asm("nop");
	return 1;
}

make_helper(int3) {
	void do_int3();
	do_int3();
	print_asm("int3");

	return 1;
}

make_helper(lea) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int len = load_addr(eip + 1, &m, op_src);
	reg_l(m.reg) = op_src->addr;

	print_asm("leal %s,%%%s", op_src->str, regsl[m.reg]);
	return 1 + len;
}
uint32_t swaddr_read(swaddr_t addr,size_t len,uint8_t sreg);
make_helper(leave)
{
	cpu.esp=cpu.ebp;
	if(ops_decoded.is_data_size_16)
	{
		uint16_t src=swaddr_read(cpu.esp,2,1);
		cpu.esp+=2;
		cpu.gpr[5]._16=src;
	}
	else
	{
		uint32_t src=swaddr_read(cpu.esp,4,1);
		cpu.esp+=4;
		cpu.ebp=src;
	}
	print_asm("leave");
	return 1;
}

make_helper(ret)
{
	if(ops_decoded.is_data_size_16)
	{
		uint16_t src=swaddr_read(cpu.esp,2,1);
		cpu.esp+=2;
		cpu.eip=src;
		cpu.eip=cpu.eip&0x0000ffff;
	}
	else
	{
		uint32_t src=swaddr_read(cpu.esp,4,1);
		cpu.esp+=4;
		cpu.eip=src;
	}
    print_asm("ret");
	return 0;
}
make_helper(cltd)
{
	if(ops_decoded.is_data_size_16)
	{
	 if(cpu.gpr[0]._16&0x8000) cpu.gpr[2]._16=0xffff;
	 else cpu.gpr[2]._16=0;
	}
	else
	{
		if(cpu.eax&0x80000000) cpu.edx=0xffffffff;
		else cpu.edx=0x00000000;
	}

	print_asm("cltd");
	return 1;
}

make_helper(cld)
{
	cpu.eflags.DF=0;
	print_asm("cld");
	return 1;
}
make_helper(lgdt)
{
	 Operand rm , reg;
	 rm.size=4;
	 int len = read_ModR_M(cpu.eip+2,&rm,&reg);
	 lnaddr_t addr = rm.addr;
	 cpu.GDTR.limit = lnaddr_read(addr,2);
	 cpu.GDTR.base_addr = lnaddr_read(addr+2,4);
   print_asm("lgdt 0x%x",rm.addr);
   return len+1;
}
make_helper(ljmp)
{
   cpu.CS.seg_selector=swaddr_read(cpu.eip+5,2,0);
	 SegDesc segdesc;
	 int index=(cpu.SS.seg_selector&0xfff8)>>3;
	 lnaddr_t seg_addr = cpu.GDTR.base_addr+index*8;
	 uint32_t low=lnaddr_read(seg_addr,4);
	 uint32_t high=lnaddr_read(seg_addr+4,4);
	 segdesc.low=low;
	 segdesc.high=high;
	 cpu.SS.base_addr=(uint32_t)segdesc.base_15_0 + (((uint32_t)segdesc.base_23_16)<<16) + (((uint32_t)segdesc.base_31_24)<<24);
	 cpu.SS.limit=(uint32_t)segdesc.limit_15_0 + (((uint32_t)segdesc.limit_19_16)<<16);
   cpu.eip=swaddr_read(cpu.eip+1,4,0)-7;
   print_asm("ljump ");
   return 7;
}
make_helper(std)
{
  cpu.eflags.DF=1;
  print_asm("std");
  return 1;
}

make_helper(lidt)
{
	Operand rm , reg;
	rm.size=4;
	int len = read_ModR_M(cpu.eip+2,&rm,&reg);
	lnaddr_t addr = rm.addr;
	cpu.IDTR.limit = lnaddr_read(addr,2);
	cpu.IDTR.base_addr = lnaddr_read(addr+2,4);
	print_asm("lidt 0x%x",rm.addr);
	return len+1;
}
