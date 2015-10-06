#include"cpu/exec/template-start.h"

#define instr jump

static void do_execute()
{
	if(DATA_BYTE==1)
	{
		uint8_t src=op_src->val;
		cpu.eip+=src;
	}
	else if(DATA_BYTE==2)
	{
		uint16_t src=op_src->val;
		cpu.eip+=src;
		cpu.eip=cpu.eip&0x0000ffff;
	}
	else if(DATA_BYTE==4)
	{
		uint32_t src=op_src->val;
		cpu.eip+=src;
	}
	print_asm_template1();
}

make_instr_helper(i)

#include"cpu/exec/template-end.h"
