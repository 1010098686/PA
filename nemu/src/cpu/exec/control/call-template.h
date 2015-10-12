#include"cpu/exec/template-start.h"
#include<stdio.h>
#define instr call

void swaddr_write(swaddr_t addr , size_t len , uint32_t data);
uint32_t swaddr_read(swaddr_t addr,size_t len);
static void do_execute()
{
	if(ops_decoded.opcode==0xff)
	{
		if(DATA_BYTE==2)
		{
			cpu.esp-=2;
			swaddr_write(cpu.esp,2,(cpu.eip+2)&0xffff);
			cpu.eip=op_src->val&0xffff;
		}
		else if(DATA_BYTE==4)
		{
			cpu.esp-=4;
			swaddr_write(cpu.esp,4,cpu.eip+2);
			cpu.eip=op_src->val;
		}
	}
    else if(DATA_BYTE==4)
	{
	 cpu.esp-=4;
	 MEM_W(cpu.esp,cpu.eip+4);
	 cpu.eip+=op_src->val;
	}
	else if(DATA_BYTE==2)
	{
		cpu.esp-=2;
		swaddr_write(cpu.esp,2,(cpu.eip+2)&0xffff);
		cpu.eip=(cpu.eip+op_src->val)&0xffff;
	}
   print_asm_template1();
}

make_instr_helper(si)
make_instr_helper(rm)
#include"cpu/exec/template-end.h"

