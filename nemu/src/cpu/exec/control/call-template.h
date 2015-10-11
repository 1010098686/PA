#include "cpu/exec/template-start.h"

#define instr call

static void do_execute()
{
	cpu.esp -= DATA_BYTE;
	if(DATA_BYTE == 2)
	{
		MEM_W(cpu.esp,(cpu.eip + 2) & 0xffff);
		cpu.eip = (cpu.eip + op_src->val) & 0xffff;
	}
	else if(DATA_BYTE == 4)
	{
		MEM_W(cpu.esp,cpu.eip + 4);
		cpu.eip = cpu.eip + op_src->val;
	}
    print_asm_template1();
}

make_instr_helper(si)
make_instr_helper(rm)
//make_instr_helper(i)

#include "cpu/exec/template-end.h"
