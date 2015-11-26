#include"cpu/exec/helper.h"

uint32_t swaddr_read(swaddr_t addr,size_t len,uint8_t sreg);
void swaddr_write(swaddr_t addr,size_t len,uint32_t data,uint8_t sreg);
make_helper(movsb)
{
	int incdec=0;
	if(ops_decoded.opcode==0xa4)
	{
		uint8_t src=swaddr_read(cpu.esi,1,3);
		swaddr_write(cpu.edi,1,src,3);
		incdec=(cpu.eflags.DF==0)?1:-1;
	}
	else
	{
		if(ops_decoded.is_data_size_16)
		{
			uint16_t src=swaddr_read(cpu.esi,2,3);
			swaddr_write(cpu.edi,2,src,3);
			incdec=(cpu.eflags.DF==0)?2:-2;
		}
		else
		{
			uint32_t src=swaddr_read(cpu.esi,4,3);
			swaddr_write(cpu.edi,4,src,3);
			incdec=(cpu.eflags.DF==0)?4:-4;
		}
	}
	cpu.esi+=incdec;
	cpu.edi+=incdec;
	print_asm("movs");
	return 1;
}
