#include "cpu/exec/template-start.h"

#define instr jump


static void do_execute()
{

	if(op_src->type == OP_TYPE_IMM)
	{
	cpu.eip += op_src->val;
	if(DATA_BYTE == 2)
		cpu.eip &= 0x0000ffff;
	}
	else
	{
		int len = 0;
		if(DATA_BYTE == 2)
		{
			len = decode_rm_w(cpu.eip + 1);
			cpu.eip = op_src->val & 0x0000ffff;
		}
		else
		{
			len = decode_rm_l(cpu.eip + 1);
			cpu.eip = op_src->val;
		}
		cpu.eip -= (len + 1);
	}
	print_asm_template1();
}

make_instr_helper(si)
make_instr_helper(rm)

#include "cpu/exec/template-end.h"
