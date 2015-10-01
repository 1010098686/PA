#include"cpu/exec/template-start.h"

#define instr test

static void do_execute()
{
	if(DATA_BYTE==1)
	{
		uint8_t src=op_src->val;
		uint8_t dest=op_dest->val;
		uint8_t result=src&dest;
		if(result&0x80) cpu.eflags.SF=1;
		else cpu.eflags.SF=0;
		if(result==0) cpu.eflags.ZF=1;
		else cpu.eflags.ZF=0;
		result=result^(result>>4);
		result=result^(result>>2);
		result=result^(result>>1);
		if(!(result&1)) cpu.eflags.PF=1;
		else cpu.eflags.PF=0;
	}
	else if(DATA_BYTE==2)
	{
		uint16_t src=op_src->val;
		uint16_t dest=op_dest->val;
		uint16_t result=src&dest;
		if(result&0x8000) cpu.eflags.SF=1;
		else cpu.eflags.SF=0;
		if(result==0) cpu.eflags.ZF=1;
		else cpu.eflags.ZF=0;
		uint8_t rel=result&0x00ff;
		rel=rel^(rel>>4);
		rel=rel^(rel>>2);
		rel=rel^(rel>>1);
		if(!(rel&1)) cpu.eflags.PF=1;
		else cpu.eflags.PF=0;
	}
	else if(DATA_BYTE==4)
	{
		uint32_t src=op_src->val;
		uint32_t dest=op_dest->val;
		uint32_t result=src&dest;
		if(result&0x80000000) cpu.eflags.SF=1;
		else cpu.eflags.SF=0;
		if(result==0) cpu.eflags.ZF=1;
		else cpu.eflags.ZF=0;
		uint8_t rel=result&0x000000ff;
		rel=rel^(rel>>4);
		rel=rel^(rel>>2);
		rel=rel^(rel>>1);
		if(!(rel&1)) cpu.eflags.PF=1;
		else cpu.eflags.PF=0;
	}
	cpu.eflags.OF=0;
	cpu.eflags.CF=0;
	print_asm_template2();
}

make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(r2rm)

#include"cpu/exec/template-end.h"
