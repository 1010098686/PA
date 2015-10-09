#include"cpu/exec/helper.h"
void swaddr_write(swaddr_t addr,size_t len,uint32_t data);
make_helper(movzwl)
{
	
	int len=decode_mov_rm2r(cpu.eip,2,4);
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
	return len;
}
#include"cpu/exec/template-end.h"
