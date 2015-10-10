#include"cpu/exec/helper.h"

make_helper(stos)
{
	if(ops_decoded.opcode==0xaa) 
	{
		cpu.edi=cpu.gpr[0]._8[0];
		if(cpu.eflags.DF==0) ++cpu.edi;
		else --cpu.edi;
	}
	else
	{
		if(ops_decoded.is_data_size_16)
		{
			cpu.edi=cpu.gpr[0]._16;
			if(cpu.eflags.DF==0) cpu.edi+=2;
			else cpu.edi-=2;
		}
		else
		{
			cpu.edi=cpu.eax;
			if(cpu.eflags.DF==0) cpu.edi+=4;
			else cpu.edi-=4;
		}
	}
	print_asm("stos");
	return 1;
}
