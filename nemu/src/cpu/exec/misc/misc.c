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
uint32_t swaddr_read(swaddr_t addr,size_t len);
make_helper(leave)
{
	cpu.esp=cpu.ebp;
	if(ops_decoded.is_data_size_16)
	{
		uint16_t src=swaddr_read(cpu.esp,2);
		cpu.esp+=2;
		cpu.gpr[5]._16=src;
	}
	else
	{
		uint32_t src=swaddr_read(cpu.esp,4);
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
		uint16_t src=swaddr_read(cpu.esp,2);
		cpu.esp+=2;
		cpu.eip=src;
		cpu.eip=cpu.eip&0x0000ffff;
	}
	else
	{
		uint32_t src=swaddr_read(cpu.esp,4);
		cpu.esp+=4;
		cpu.eip=src;
	}
    print_asm("ret");
	return 1;
}
make_helper(cltd)
{
	if(ops_decoded.is_data_size_16)
	{
	 if(cpu.gpr[0]._16&0x8000) cpu.gpr[2]._16=0xffff;
	 else cpu.gpr[2]._16=0x0000;
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
