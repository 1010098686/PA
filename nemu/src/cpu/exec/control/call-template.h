#include"cpu/exec/template-start.h"
#include<stdio.h>
#define instr call

void swaddr_write(swaddr_t addr , size_t len , uint32_t data);
static void do_execute()
{
	int32_t src=op_src->val;
	cpu.esp=cpu.esp-4;
	swaddr_write(cpu.esp,4,cpu.eip);
	cpu.eip=cpu.eip+src;
    sprintf(op_src->str,"0x%x",cpu.eip+5);	
	print_asm_template1();
}

make_instr_helper(i);
#include"cpu/exec/template-end.h"

