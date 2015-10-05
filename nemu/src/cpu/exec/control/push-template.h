#include"cpu/exec/template-start.h"

#define instr push
void swaddr_write(swaddr_t addr,size_t len,uint32_t data);
static void do_execute()
{
	if(DATA_BYTE==4)
	{

	  uint32_t src=op_src->val;
	  cpu.esp=cpu.esp-4;
	  swaddr_write(cpu.esp,4,src);
	}
	else if(DATA_BYTE==2)
	{
		uint16_t src=op_src->val;
		cpu.esp-=2;
		swaddr_write(cpu.esp,2,src);
	}
	print_asm_template1();
}

make_instr_helper(r)
make_instr_helper(rm)
make_instr_helper(i)
#include"cpu/exec/template-end.h"
