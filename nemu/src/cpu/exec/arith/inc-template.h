#include "cpu/exec/template-start.h"

#define instr inc

static void do_execute () {
	DATA_TYPE result = op_src->val + 1;
	OPERAND_W(op_src, result);

	/* TODO: Update EFLAGS. */
	//panic("please implement me");
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
	DATA_TYPE src=op_src->val;
	DATA_TYPE dest=1;
	int cin=0;
	int acin=0;
	int i;
	for(i=1;i<=8*DATA_BYTE;++i)
	{
		int a1=src&1;
		src>>=1;
		int a2=dest&1;
		dest>>=1;
		int rel=a1+a2+cin;
		if(rel==2 || rel==3) cin=1;
		else cin=0;
		if(i==8*DATA_BYTE-1) acin=cin;
	}
	cpu.eflags.CF=(cin)?1:0;
	cpu.eflags.OF=cin^acin;
	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"
