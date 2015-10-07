#include"cpu/exec/template-start.h"
#define instr sub
static void do_execute()
{
	if(DATA_BYTE==1)
	{
		int8_t src=op_src->val;
		int8_t dest=op_dest->val;
		int8_t result=dest-src;
		OPERAND_W(op_dest,result);
		cpu.eflags.SF=(result&0x80)?1:0;
		cpu.eflags.ZF=(result==0)?1:0;
		result=result^(result>>4);
		result=result^(result>>2);
		result=result^(result>>1);
		cpu.eflags.PF=(!(result&1))?1:0;
		int8_t asrc=~src;
		int cin=1;
		int acin=0;
		int i;
		for(i=1;i<=8;++i)
		{
			int a1=asrc&0x01;
			asrc=asrc>>1;
			int a2=dest&0x01;
			dest=dest>>1;
			int rel=a1+a2+cin;
			if(rel==2 || rel==3) cin=1;
			else cin=0;
			if(i==7) acin=cin;
		}
		cpu.eflags.CF=(!cin)?1:0;
		cpu.eflags.OF=cin^acin;
	}
	else if(DATA_BYTE==2) 
	{
		int16_t src=op_src->val;
		int16_t dest=op_dest->val;
		int16_t result=dest-src;
        OPERAND_W(op_dest,result);
		if(result&0x8000) cpu.eflags.SF=1;
		else cpu.eflags.SF=0;
		if(result==0) cpu.eflags.ZF=1;
		else cpu.eflags.ZF=0;
		//calculate the PF
		int8_t low=result&0x00ff;
		low=low^(low>>4);
		low=low^(low>>2);
		low=low^(low>>1);
		if(!(low&1)) cpu.eflags.PF=1;
		else cpu.eflags.PF=0;
		//calculate the CF and OF
		int16_t asrc=src;
		asrc=~asrc;
		int cin=1;
		int acin=0;
		int i;
		for(i=1;i<=16;++i)
		{
			int a1=asrc&0x0001;
			asrc=asrc>>1;
			int a2=dest&0x0001;
			dest=dest>>1;
			int rel=a1+a2+cin;
			if(rel==2 || rel==3) cin=1;
			else cin=0;
			if(i==15) acin=cin;
		}
		if(!cin) cpu.eflags.CF=1;
		else cpu.eflags.CF=0;
		cpu.eflags.OF=cin^acin;

	}
	else if(DATA_BYTE==4)
	{
		int32_t src=op_src->val;
		int32_t dest=op_dest->val;
		int32_t result=dest-src;
		OPERAND_W(op_dest,result);
		if(result&0x80000000) cpu.eflags.SF=1;
		else cpu.eflags.SF=0;
		cpu.eflags.ZF=(result==0)?1:0;
		//calculate the PF;
		int8_t low=result&0x000000ff;
		low=low^(low>>4);
		low=low^(low>>2);
		low=low^(low>>1);
		cpu.eflags.PF=(!(low&1))?1:0;
		//calculate the CF and OF
		int32_t asrc=src;
		asrc=~asrc;
		int cin=1;
		int acin=0;
		int i;
		for(i=1;i<=32;++i)
		{
			int a1=asrc&0x00000001;
			asrc=asrc>>1;
			int a2=dest&0x00000001;
			dest=dest>>1;
			int rel=a1+a2+cin;
			if(rel==2 || rel==3) cin=1;
			else cin=0;
			if(i==31) acin=cin;
		}
		cpu.eflags.CF=(!cin)?1:0;
		cpu.eflags.OF=cin^acin;
	}
	print_asm_template2();
}


make_instr_helper(si2rm)
make_instr_helper(i2rm)
make_instr_helper(i2a)
make_instr_helper(r2rm)
make_instr_helper(rm2r)
#include"cpu/exec/template-end.h"
