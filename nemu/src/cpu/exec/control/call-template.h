#include"cpu/exec/template-start.h"
#include<stdio.h>
#define instr call

//void swaddr_write(swaddr_t addr , size_t len , uint32_t data);
static void do_execute()
{
	if(DATA_BYTE==4)
	{
	 MEM_W(cpu.esp,cpu.eip+4);
	 cpu.eip+=op_src->val;
	}
	else if(DATA_BYTE==2)
	{
		MEM_W(cpu.esp,(cpu.eip+2)&0xffff);
		cpu.eip=(cpu.eip+op_src->val)&0xffff;
	}
   print_asm_template1();
}

make_instr_helper(i)
make_instr_helper(rm)
#include"cpu/exec/template-end.h"

