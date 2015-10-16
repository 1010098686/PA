#include"cpu/exec/template-start.h"
#define instr ret

static void do_execute()
{
	    DATA_TYPE imm=op_src->val;
		uint16_t src=swaddr_read(cpu.esp,2);
		cpu.esp+=2;
		cpu.esp+=imm;
		int len=decode_i_w(cpu.eip+1);
		cpu.eip=cpu.eip&0xffff0000;
		unsigned asrc=src;
		cpu.eip+=asrc;
		//cpu.eip=cpu.eip&0x0000ffff;
		cpu.eip-=len;

	print_asm_template1();
}

make_instr_helper(i)

#include"cpu/exec/template-end.h"
