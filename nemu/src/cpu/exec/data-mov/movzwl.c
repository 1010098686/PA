#include"cpu/exec/helper.h"
//#include"cpu/exec/template-start.h"
/*#define DATA_BYTE 1
#include"movzwl-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"movzwl-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"movzwl-template.h"
#undef DATA_BYTE*/
void swaddr_write(swaddr_t addr,size_t len,uint32_t data);
make_helper(movzwl)
{
	
	int len1=decode_rm_w(cpu.eip);
	int len2=decode_r_l(cpu.eip);
	uint16_t src=op_src->val;
	uint32_t dest=src;
	if(op_dest->type==OP_TYPE_REG)
	{
		reg_l(op_dest->reg)=dest;
	}
	else if(op_dest->type==OP_TYPE_MEM)
	{
		swaddr_write(op_dest->addr,op_dest->size,dest);
	}
	print_asm_template2();
	return len1+len2;
}
#include"cpu/exec/template-end.h"
