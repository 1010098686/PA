#include"cpu/exec/helper.h"

make_helper(stos)
{
	if(ops_decoded.opcode==0xaa) 
	{
		swaddr_write(cpu.edi,1,cpu.gpr[0]._8[0],2);
		if(cpu.eflags.DF==0) ++cpu.edi;
		else --cpu.edi;
	}
	else
	{
		if(ops_decoded.is_data_size_16)
		{
			swaddr_write(cpu.edi,2,cpu.gpr[0]._16,2);
			if(cpu.eflags.DF==0) cpu.edi+=2;
			else cpu.edi-=2;
		}
		else
		{
			swaddr_write(cpu.edi,4,cpu.eax,2);
			if(cpu.eflags.DF==0) cpu.edi+=4;
			else cpu.edi-=4;
		}
	}
	print_asm("stos");
	return 1;
}
