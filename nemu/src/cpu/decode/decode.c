#include "common.h"
#include "cpu/decode/decode.h"

/* shared by all helper function */
Operands ops_decoded;

#define DATA_BYTE 1
#include "decode-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "decode-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "decode-template.h"
#undef DATA_BYTE

int decode_mov_rm2r(swaddr_t eip,int data_byte1,int data_byte2)
{
	switch(data_byte1)
	{
		case 1:op_src->size=1;break;
		case 2:op_src->size=2;break;
		case 4:op_src->size=4;break;
	}
	int len = read_ModR_M(eip,op_src,op_dest);
	switch(data_byte2)
	{
		case 1:op_dest->val=reg_b(op_dest->reg);break;
		case 2:op_dest->val=reg_w(op_dest->reg);break;
		case 4:op_dest->val=reg_l(op_dest->reg);break;
	}
	return len;
}
