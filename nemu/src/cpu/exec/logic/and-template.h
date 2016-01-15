#include "cpu/exec/template-start.h"

#define instr and

static void do_execute () {
	DATA_TYPE result = op_dest->val & op_src->val;
	OPERAND_W(op_dest, result);

	/* TODO: Update EFLAGS. */
	//panic("please implement me");
    cpu.eflags.CF=0;
	cpu.eflags.OF=0;
	cpu.eflags.SF=(MSB(result)==1)?1:0;
	cpu.eflags.ZF=(result==0)?1:0;
	int8_t rel=result&0xff;
	rel=rel^(rel>>4);
	rel=rel^(rel>>2);
	rel=rel^(rel>>1);
	cpu.eflags.PF=(!(rel&1))?1:0;
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
