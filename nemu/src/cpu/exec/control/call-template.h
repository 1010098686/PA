#include"cpu/exec/template-start.h"
#include<stdio.h>
#define instr call

void swaddr_write(swaddr_t addr , size_t len , uint32_t data);
static void do_execute()
{
	if(DATA_BYTE==4)
	{
	 int32_t src=op_src->val;
	 cpu.esp=cpu.esp-4;
	 swaddr_write(cpu.esp,4,cpu.eip+4);
	 cpu.eip=cpu.eip+src;
	}
	else if(DATA_BYTE==2)
	{
		int16_t ip=cpu.eip&0x0000ffff;
		cpu.esp=cpu.esp-2;
		swaddr_write(cpu.esp,2,ip+2);
		int16_t src=op_src->val;
		cpu.eip+=src;
		//cpu.eip+=DATA_BYTE;
		cpu.eip=cpu.eip&0x0000ffff;
	}
   print_asm_template1();
}

make_instr_helper(i)
make_instr_helper(rm)
#include"cpu/exec/template-end.h"

