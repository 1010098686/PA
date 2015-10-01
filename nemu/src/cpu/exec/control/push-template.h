#include"cpu/exec/template-start.h"

#define instr push
void swaddr_write(swaddr_t addr,size_t len,uint32_t data);
static void do_execute()
{
	uint32_t src=op_src->val;
	cpu.esp=cpu.esp-4;
	swaddr_write(cpu.esp,4,src);
	print_asm_template1();
}

make_instr_helper(r)
#include"cpu/exec/template-end.h"
