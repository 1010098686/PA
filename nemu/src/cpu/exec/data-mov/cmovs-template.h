#include"cpu/exec/template-start.h"

#define instr cmovs

static void do_execute()
{
	if(cpu.eflags.SF==1)
	{
		OPERAND_W(op_dest,op_src->val);
	}
	print_asm_template2();
}

make_instr_helper(rm2r)

#include"cpu/exec/template-end.h"
