#include "cpu/exec/template-start.h"

#define instr cmp

static void do_execute()
{
    uint32_t f1,f2,f3,t,count = 0,flag = 0;
	t = op_dest->val - op_src->val;
	if(DATA_BYTE == 1)
		flag = 8;
	else if(DATA_BYTE == 2)
		flag = 16;
	else if(DATA_BYTE == 4)
		flag = 32;
	f1 = (op_dest->val >> (flag - 1)) & 0x1;
	f2 = (op_src->val >> (flag - 1)) & 0x1;
	f3 = (t >> (flag - 1)) & 0x1;
	if((f1 != f2) && (f2 == f3))
		cpu.Eflags.OF = 1;
	else
		cpu.Eflags.OF = 0;
	if(t == 0)
		cpu.Eflags.ZF = 1;
	else
		cpu.Eflags.ZF = 0;
	if(f3 == 0)
		cpu.Eflags.SF = 0;
	else
		cpu.Eflags.SF = 1;
	int i;
	for(i = 1;i <= 8;++i)
	{
		int temp = t & 0x1;
		if(temp == 1)
			++count;
		t >>= 1;
	}
	if(count % 2 == 0)
		cpu.Eflags.PF = 1;
	else
		cpu.Eflags.PF = 0;
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
		cpu.Eflags.CF = 0;
	else
		cpu.Eflags.CF = 1;
	print_asm_template2();
}

make_instr_helper(i2a)

make_instr_helper(i2rm)

make_instr_helper(si2rm)

make_instr_helper(r2rm)

make_instr_helper(rm2r)



#include "cpu/exec/template-end.h"
