#include"cpu/exec/template-start.h"

#define instr bt

static void do_execute()
{
	DATA_TYPE base = op_dest->val;
	DATA_TYPE offset = op_src->val;
	base = base >> offset;
	cpu.eflags.CF = base&0x1;
	print_asm_template2();
}

make_instr_helper(r2rm)
make_instr_helper(i2rm)

#include"cpu/exec/template-end.h"
