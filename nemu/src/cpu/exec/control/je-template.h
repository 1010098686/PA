#include"cpu/exec/template-start.h"
#include<stdio.h>
#define instr je
static void do_execute()
{
	int asrc=0;
	if(cpu.eflags.ZF==1)
	{
		
	  if(DATA_BYTE==1)
	   {
		int8_t src=op_src->val;
		asrc=src;
		cpu.eip+=src;
	   }  
	  else if(DATA_BYTE==2)
	   {
		int16_t src=op_src->val;
		asrc=src;
		cpu.eip+=src;
	   }
	  else if(DATA_BYTE==4)
	   {
		int32_t src=op_src->val;
		asrc=src;
		cpu.eip+=src;
	   }
	}
	sprintf(op_src->str,"0x%x",cpu.eip+asrc+2);
	print_asm_template1();
}

make_instr_helper(si)
#include"cpu/exec/template-end.h"
