#include"cpu/exec/template-start.h"

#define instr jae

static void do_execute()
{
	if( cpu.eflags.CF==0)
	{
		cpu.eip+=op_src->val;
		if(DATA_BYTE==2)
			cpu.eip=cpu.eip&0x0000ffff;
	}
	print_asm_template1();
}

make_instr_helper(si)

#include"cpu/exec/template-end.h"
