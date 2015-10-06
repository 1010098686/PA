#include"cpu/exec/template-start.h"
#define instr jbe

static void do_execute()
{
	if(cpu.eflags.CF==1 || cpu.eflags.ZF==1)
	{
		if(DATA_BYTE==1)
		{
			int8_t src=op_src->val;
			cpu.eip+=src;
		}
		else if(DATA_BYTE==2)
		{
			int16_t src=op_src->val;
			cpu.eip+=src;
			cpu.eip=cpu.eip&0x0000ffff;
		}
		else if(DATA_BYTE==4)
		{
			int32_t src=op_src->val;
			cpu.eip+=src;
		}
	}
}

make_instr_helper(si)
#include"cpu/exec/template-end.h"
