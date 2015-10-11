#include"cpu/exec/template-start.h"

#define instr adc

static void do_execute()
{
	DATA_TYPE src=op_src->val+cpu.eflags.CF;
	DATA_TYPE dest=op_dest->val;
	DATA_TYPE result=src+dest;
	OPERAND_W(op_dest,result);
	if(DATA_BYTE==1) cpu.eflags.SF=(result&0x80)?1:0;
	else if(DATA_BYTE==2) cpu.eflags.SF=(result&0x8000)?1:0;
	else if(DATA_BYTE==4) cpu.eflags.SF=(result&0x80000000)?1:0;
	cpu.eflags.ZF=(result==0)?1:0;
	int8_t low=result&0xff;
	low=low^(low>>4);
	low=low^(low>>2);
	low=low^(low>>1);
	cpu.eflags.PF=(!(low&1))?1:0;
	int cin=1;
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
		if(i==8*DATA_BYTE-1) acin=cin;
	}
	cpu.eflags.CF=(cin)?1:0;
	cpu.eflags.OF=cin^acin;
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE==2 || DATA_BYTE==4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include"cpu/exec/template-end.h"
