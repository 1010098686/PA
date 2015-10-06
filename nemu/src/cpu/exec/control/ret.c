#include"cpu/exec/helper.h"

/*#define DATA_BYTE 1
#include"ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"ret-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"ret-template.h"
#undef DATA_BYTE*/

uint32_t swaddr_read(swaddr_t addr,size_t len);
make_helper(ret_i_w)
{
	int len=decode_i_w(cpu.eip+1);
	uint16_t src=swaddr_read(cpu.esp,2);
	cpu.esp+=2;
	uint32_t asrc=src;
	cpu.eip=asrc;
	cpu.eip=cpu.eip&0x0000ffff;
	cpu.esp+=op_src->val;
	print_asm_template1();
	return len+1;
}
make_helper(ret_i_l)
{
	int len=decode_i_l(cpu.eip+1);
	uint32_t src=swaddr_read(cpu.esp,4);
	cpu.esp+=4;
	cpu.eip=src;
	cpu.esp+=op_src->val;
	print_asm_template1();
	return len+1;
}
