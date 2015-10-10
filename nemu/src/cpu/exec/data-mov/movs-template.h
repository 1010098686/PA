#include"mov-template-start.h"

#define instr movs

static void do_mov_execute()
{
	DATA_TYPE1_S src=op_src->val;
	DATA_TYPE2_S dest=src;
	OPERAND_W_mov(op_dest,dest);
	print_asm_template2_mov();
}

make_instr_helper_mov(rm2r)


#include"mov-template-end.h"
