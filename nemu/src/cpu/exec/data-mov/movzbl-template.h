#include"cpu/exec/template-start.h"

#define instr movzb

static int execute2(movzb_v)
{
	int len=0;
	int len1=decode_rm_b(cpu.eip);
	uint8_t src=op_src->val;
	if(ops_decoded.is_data_size_16)
	{
		int len2=decode_r_w(cpu.eip);
		uint16_t dest=src;
		len=len1+len2;
		OPERAND_W(op_dest,dest);
	}
	else
	{
		int len2=decode_r_l(cpu.eip);
		uint32_t dest=src;
		len=len1+len2;
		OPERAND_W(op_dest,dest);
	}
	print_asm_template2();
	return len;
}
#include"cpu/exec/template-end.h"
