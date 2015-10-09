#include"cpu/exec/helper.h"
#define instr movzb
void swaddr_write(swaddr_t addr,size_t len,uint32_t data);
make_helper(movzb_v)
{
	int len=0;
	if(ops_decoded.is_data_size_16)
	{
        #define DATA_BYTE 2
		len=decode_mov_rm2r(cpu.eip+1,1,2);
		uint8_t src=op_src->val;
		uint16_t dest=src;
		if(op_dest->type==OP_TYPE_REG) 
		{
			reg_w(op_dest->reg)=dest;
		}
		else if(op_dest->type==OP_TYPE_MEM)
		{
			swaddr_write(op_dest->addr,op_dest->size,dest);
		}
        #undef DATA_BYTE
	}
	else
	{
        #define DATA_BYTE 4
		len=decode_mov_rm2r(cpu.eip+1,1,4);
		uint8_t src=op_src->val;
		uint32_t dest=src;
		if(op_dest->type==OP_TYPE_REG)
		{
			reg_l(op_dest->reg)=dest;
		}
		else if(op_dest->type==OP_TYPE_MEM)
		{
			swaddr_write(op_dest->addr,op_dest->size,dest);
		}
        #undef DATA_BYTE
	}
	print_asm_template2();
	return len;
}
#include"cpu/exec/template-end.h"
