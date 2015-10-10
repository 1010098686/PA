#include"mov-template-start.h"
#include"cpu/decode/modrm.h"

#define decode_rm_internal concat5(decode_rm_,SUFFIX1,_,SUFFIX2,_internal)
static int concat5(decode_rm_,SUFFIX1,_,SUFFIX2,_internal)(swaddr_t eip,Operand* rm,Operand* reg)
{
	rm->size=DATA_BYTE1;
	int len=read_ModR_M(eip,rm,reg);
	reg->val=REG_mov(reg->reg);
	return len;
}

make_helper(concat4(decode_rm2r_,SUFFIX1,_,SUFFIX2))
{
	return decode_rm_internal(eip,op_src,op_dest);
}

#include"mov-template-end.h"
