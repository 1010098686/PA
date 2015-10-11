#include"cpu/exec/template-start.h"
#define instr add

static void do_execute()
{
		DATA_TYPE src=op_src->val;
		DATA_TYPE dest=op_src->val;
		DATA_TYPE result=src+dest;
		OPERAND_W(op_dest,result);
		switch(DATA_BYTE)
		{
			case 1:cpu.eflags.SF=(result&0x80)?1:0;break;
			case 2:cpu.eflags.SF=(result&0x8000)?1:0;break;
			case 4:cpu.eflags.SF=(result&0x80000000)?1:0;break;
		}
		cpu.eflags.ZF=(result==0)?1:0;
		int8_t low=result&0xff;
		low=low^(low>>4);
		low=low^(low>>2);
		low=low^(low>>1);
		cpu.eflags.PF=(!(low&1))?1:0;
		//calculate the CF and OF
		int cin=0;
		int acin=0;
		int i;
		for(i=1;i<=8*DATA_BYTE;++i)
		{
			int a1=src&0x1;
			src=src>>1;
			int a2=dest&0x1;
			dest=dest>>1;
			int rel=a1+a2+cin;
			if(rel==2 || rel==3) cin=1;
			else cin=0;
			if(i==(8*DATA_BYTE-1)) acin=cin;
		}
		cpu.eflags.CF=(cin)?1:0;
		cpu.eflags.OF=cin^acin;
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(si2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include"cpu/exec/template-end.h"
