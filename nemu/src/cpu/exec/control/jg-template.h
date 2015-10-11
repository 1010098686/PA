#include"cpu/exec/template-start.h"

#define instr jg

static void do_execute()
{
	if(cpu.eflags.ZF==0 && cpu.eflags.SF==cpu.eflags.OF)
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
