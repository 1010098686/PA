#include"cpu/exec/template-start.h"

#define instr jl

static void do_execute()
{
	if(cpu.eflags.SF!=cpu.eflags.OF)
	{
		DATA_TYPE_S src=op_src->val;
		cpu.eip+=src;
		if(DATA_BYTE==2)
			cpu.eip=cpu.eip&0x0000ffff;
	}
	print_asm_template1();
}

make_instr_helper(si)

#include"cpu/exec/template-end.h"
