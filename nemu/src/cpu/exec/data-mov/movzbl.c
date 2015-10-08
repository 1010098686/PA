#include"cpu/exec/helper.h"
void swaddr_write(swaddr_t addr,size_t len,uint32_t data);
make_helper(movzb_v)
{
	
	int len;
	int len1=decode_rm_b(cpu.eip+1);
	uint8_t src=op_src->val;
	if(ops_decoded.is_data_size_16)
	{
		int len2=decode_r_w(cpu.eip+len1);
		uint16_t dest=src;
		if(op_dest->type==OP_TYPE_REG) 
		{
			reg_w(op_dest->reg)=dest;
		}
		else if(op_dest->type==OP_TYPE_MEM)
		{
			swaddr_write(op_dest->addr,op_dest->size,dest);
		}
		len=len1+len2;
	}
	else
	{
		int len2=decode_r_l(cpu.eip);
		uint32_t dest=src;
		if(op_dest->type==OP_TYPE_REG)
		{
			reg_l(op_dest->reg)=dest;
		}
		else if(op_dest->type==OP_TYPE_MEM)
		{
			swaddr_write(op_dest->addr,op_dest->size,dest);
		}
		len=len1+len2;
	}
	print_asm_template2();
	return len;
}
#include"cpu/exec/template-end.h"
