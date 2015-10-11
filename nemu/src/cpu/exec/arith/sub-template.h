#include "cpu/exec/template-start.h"

#define instr sub

static void do_execute()
{
	uint32_t f1,f2,f3,t1,t2,count = 0,flag = 0;
	t1 = op_dest->val - op_src->val;
	t2 = t1;
	if(DATA_BYTE == 1)
		flag = 8;
	else if(DATA_BYTE == 2)
		flag = 16;
	else if(DATA_BYTE == 4)
		flag = 32;
	f1 = (op_dest->val >> (flag - 1)) & 0x1;
	f2 = (op_src->val >> (flag - 1)) & 0x1;
	f3 = (t1 >> (flag - 1)) & 0x1;
	if((f1 != f2) && (f2 == f3))
		cpu.eflags.OF = 1;
	else
		cpu.eflags.OF = 0;
	if(t1 == 0)
		cpu.eflags.ZF = 1;
	else
		cpu.eflags.ZF = 0;
	if(f3 == 0)
		cpu.eflags.SF = 0;
	else
		cpu.eflags.SF = 1;
	int i;
	for(i = 1;i <= 8;++i)
	{
		int temp = t2 & 0x1;
		if(temp == 1)
			++count;
		t2 >>= 1;
	}
	if(count % 2 == 0)
		cpu.eflags.PF = 1;
	else
		cpu.eflags.PF = 0;
	count = 1;
	f1 = op_dest->val;
	f2 = ~op_src->val;
	for(i = 1;i <= flag;++i)
	{
		int p1 = f1 & 0x1;
	    int p2 = f2 & 0x1;
	    int result = p1 + p2 + count;
	    if(result > 1)
		   count = 1;
		else
		   count = 0;
	    f1 >>= 1;
	    f2 >>= 1;	
	}
	if(count == 1)
		cpu.eflags.CF = 0;
	else
		cpu.eflags.CF = 1;
	OPERAND_W(op_dest,t1);
	print_asm_template2();
}

make_instr_helper(i2rm)
make_instr_helper(si2rm)
make_instr_helper(rm2r)
make_instr_helper(r2rm)
make_instr_helper(i2a)


#include "cpu/exec/template-end.h"
