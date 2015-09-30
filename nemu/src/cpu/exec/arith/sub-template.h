#include"cpu/exec/template-start.h"
#define instr sub
static void do_execute()
{
	int8_t src=op_src->val;
	if(DATA_BYTE==2) 
	{
		int16_t det=op_dest->val-src;
        OPERAND_W(op_dest,det);
	}
	else if(DATA_BYTE==4)
	{
		int32_t det=op_dest->val-src;
		OPERAND_W(op_dest,det);
	}
	print_asm_template2();
}

make_instr_helper(i2rm)

#include"cpu/exec/template-end.h"
