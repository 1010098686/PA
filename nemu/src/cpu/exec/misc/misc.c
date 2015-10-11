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

make_helper(leave)
{
	cpu.esp = cpu.ebp;
	if(ops_decoded.is_data_size_16)
	{
		cpu.ebp = swaddr_read(cpu.esp,2);
		cpu.esp += 2;
	}
	else
	{
		cpu.ebp = swaddr_read(cpu.esp,4);
		cpu.esp += 4;
	}
	print_asm("leave");
	return 1;
}

make_helper(ret)
{
	if(ops_decoded.is_data_size_16)
	{
		cpu.eip = swaddr_read(cpu.esp,2);
		cpu.eip &= 0x0000ffff;
		cpu.esp += 2;
	}
	else
	{
		cpu.eip = swaddr_read(cpu.esp,4);
		cpu.esp += 4;
	}
	if(ops_decoded.opcode == 0xc2 || ops_decoded.opcode == 0xca)
	{
		cpu.esp += instr_fetch(eip + 1,2);
	}
	print_asm("ret");
	return 1;
}

make_helper(cltd)
{
	uint32_t flag = 0;
	if(ops_decoded.is_data_size_16)
	{
		flag = (cpu.eax >> 15) & 0x1;
		if(flag == 1)
			cpu.edx |= 0x0000ffff;
		else
			cpu.edx &= 0xffff0000;
		print_asm("cwtl");
	}
	else
	{
		flag = (cpu.eax >> 31) & 0x1;
		if(flag == 1)
			cpu.edx = 0xffffffff;
		else
			cpu.edx = 0;
		print_asm("cltd");
	}
	return 1;
}

make_helper(cld)
{
	cpu.eflags.DF = 0;
	print_asm("cld");
	return 1;
}
