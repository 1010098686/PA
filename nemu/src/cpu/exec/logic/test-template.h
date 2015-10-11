#include "cpu/exec/template-start.h"

#define instr test

static void do_execute()
{
	uint32_t result = op_src->val & op_dest->val;
	cpu.eflags.CF = 0;
	cpu.eflags.OF = 0;
	int shift_width = 0,count = 0;
	if(DATA_BYTE == 2)
		shift_width = 16;
	else if(DATA_BYTE == 4)
		shift_width = 32;
	if(result == 0)
		cpu.eflags.ZF = 1;
	else
		cpu.eflags.ZF = 0;
	if(((result >> (shift_width - 1)) & 0x1) == 1)
		cpu.eflags.SF = 1;
	else
		cpu.eflags.SF = 0;
	int i;
	for(i = 1;i <= 8;++i)
	{
		int temp = result & 0x1;
		if(temp == 1)
			++count;
		result >>= 1;
	}
	if(count % 2 == 0)
		cpu.eflags.PF = 1;
	else
		cpu.eflags.PF = 0;
	print_asm_template2();
}

make_instr_helper(r2rm)
make_instr_helper(i2rm)
make_instr_helper(i2a)
make_instr_helper(i2r)

#include "cpu/exec/template-end.h"
