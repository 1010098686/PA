#include"cpu/exec/template-start.h"

#define instr movzwl

static int execute(movzwl)
{
	int len1=decode_rm_w(cpu.eip);
	int len2=decode_r_l(cpu.eip);
	uint16_t src=op_src->val;
	uint32_t dest=src;
	OPERAND_W(op_dest,dest);
	print_asm_template2();
	return len1+len2;
}
#include"cpu/exec/template-end.h"
