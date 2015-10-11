#include"cpu/exec/template-start.h"
#define instr cmp
static void do_execute()
{
		DATA_TYPE src=op_src->val;
		DATA_TYPE dest=op_dest->val;
		DATA_TYPE result=dest-src;
		switch(DATA_BYTE)
		{
			case 1:cpu.eflags.SF=(result&0x80)?1:0;break;
			case 2:cpu.eflags.SF=(result&0x8000)?1:0;break;
			case 4:cpu.eflags.SF=(result&0x80000000)?1:0;break;
		}
		cpu.eflags.ZF=(result==0)?1:0;
		int8_t rel=result;
		rel=rel^(rel>>4);
		rel=rel^(rel>>2);
		rel=rel^(rel>>1);
		cpu.eflags.PF=(!(rel&1))?1:0;
		DATA_TYPE asrc=~src;
		int cin=1;
		int acin=0;
		int i;
		for(i=1;i<=8*DATA_BYTE;++i)
		{
			int a1=asrc&0x1;
			asrc=asrc>>1;
			int a2=dest&0x1;
			dest=dest>>1;
			int r=a1+a2+cin;
			if(r==2 || r==3) cin=1;
			else cin=0;
			if(i==(8*DATA_BYTE-1)) acin=cin;
		}
		cpu.eflags.CF=(!cin)?1:0;
		cpu.eflags.OF=cin^acin;
	print_asm_template2();
}

make_instr_helper(si2rm)
make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)
#include"cpu/exec/template-end.h"
