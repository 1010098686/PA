#include"cpu/exec/template-start.h"
#define instr jbe

static void do_execute()
{
	if(cpu.eflags.CF==1 || cpu.eflags.ZF==1)
	{
		if(DATA_BYTE==1)
		{
			cpu.eip+=op_src->val;
		}
		else if(DATA_BYTE==2)
		{
			cpu.eip+=op_src->val;
			cpu.eip=cpu.eip&0x0000ffff;
		}
		else if(DATA_BYTE==4)
		{
			cpu.eip+=op_src->val;
		}
	}
	print_asm_template1();
}

make_instr_helper(si)
#include"cpu/exec/template-end.h"
