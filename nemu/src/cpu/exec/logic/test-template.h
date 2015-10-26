#include"cpu/exec/template-start.h"

#define instr test

static void do_execute()
{
	if(DATA_BYTE==1)
	{
		uint8_t src1=op_src->val;
		uint8_t dest1=op_dest->val;
		uint8_t result1=src1&dest1;
		if(result1&0x80) cpu.eflags.SF=1;
		else cpu.eflags.SF=0;
		if(result1==0) cpu.eflags.ZF=1;
		else cpu.eflags.ZF=0;
		result1=result1^(result1>>4);
		result1=result1^(result1>>2);
		result1=result1^(result1>>1);
		if(!(result1&1)) cpu.eflags.PF=1;
		else cpu.eflags.PF=0;
	}
	else if(DATA_BYTE==2)
	{
	    uint16_t src2=op_src->val;
		uint16_t dest2=op_dest->val;
		uint16_t result2=src2&dest2;
		if(result2&0x8000) cpu.eflags.SF=1;
		else cpu.eflags.SF=0;
		if(result2==0) cpu.eflags.ZF=1;
		else cpu.eflags.ZF=0;
		uint8_t rel=result2&0x00ff;
		rel=rel^(rel>>4);
		rel=rel^(rel>>2);
		rel=rel^(rel>>1);
		if(!(rel&1)) cpu.eflags.PF=1;
		else cpu.eflags.PF=0;
	}
	else if(DATA_BYTE==4)
	{
		uint32_t src3=op_src->val;
		uint32_t dest3=op_dest->val;
		uint32_t result3=src3&dest3;
		cpu.eflags.SF=(result3&0x80000000)?1:0;
		cpu.eflags.ZF=(result3==0)?1:0;
		uint8_t rel=result3&0x000000ff;
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

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)

#include"cpu/exec/template-end.h"
