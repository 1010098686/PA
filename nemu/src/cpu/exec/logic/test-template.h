#include"cpu/exec/template-start.h"

#define instr test

static void do_execute()
{
	DATA_TYPE src = op_src->val;
	DATA_TYPE dest = op_dest->val;
	DATA_TYPE result = src&dest;
	cpu.eflags.SF=(MSB(result)==1)?1:0;
	cpu.eflags.ZF=(result==0)?1:0;
	int8_t rel = result&0xff;
	rel = rel^(rel>>4);
	rel = rel^(rel>>2);
	rel = rel^(rel>>1);
	cpu.eflags.PF=(!(rel&1))?1:0;
	cpu.eflags.OF=0;
	cpu.eflags.CF=0;
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)

#include"cpu/exec/template-end.h"
