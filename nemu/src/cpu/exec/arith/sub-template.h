#include"cpu/exec/template-start.h"
#define instr sub
static void do_execute()
{
	uint8_t src=op_src->val;
	if(DATA_BYTE==2) 
	{
		uint16_t det=op_dest->val-src;
        OPERAND_W(op_dest,det);
	}
	else if(DATA_BYTE==4)
	{
		uint32_t det=op_dest->val-src;
		OPERAND_W(op_dest,det);
	}
	print_asm_template2();
}

make_instr_helper(i2rm);

#include"cpu/exec/template-end.h"
