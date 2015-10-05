#include"cpu/exec/template-start.h"

#define instr pop
uint32_t swaddr_read(swaddr_t addr,size_t len);
static void do_execute()
{
	if(DATA_BYTE==2)
	{
		uint16_t src=swaddr_read(cpu.esp,2);
		OPERAND_W(op_src,src);
		cpu.esp+=2;
	}
	else if(DATA_BYTE==4)
	{
		uint32_t src=swaddr_read(cpu.esp,4);
		OPERAND_W(op_src,src);
		cpu.esp+=4;
	}
	print_asm_template1();
}

make_instr_helper(r)
make_instr_helper(rm)
#include"cpu/exec/template-end.h"
