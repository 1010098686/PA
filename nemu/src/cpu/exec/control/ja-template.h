#include"cpu/exec/template-start.h"

#define instr ja

static void do_execute()
{
	if(cpu.eflags.ZF==0 && cpu.eflags.CF==0)
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
