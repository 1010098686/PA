#include"cpu/exec/helper.h"

uint32_t swaddr_read(swaddr_t addr,size_t len);
make_helper(cmps)
{
	int incdec=0;
	if(ops_decoded.opcode==0xa6)
	{
		uint8_t src=swaddr_read(cpu.esi,1);
		uint8_t dest=swaddr_read(cpu.edi,1);
		int8_t result=src-dest;
		cpu.eflags.SF=(result&0x80)?1:0;
		cpu.eflags.ZF=(result==0)?1:0;
		result=result^(result>>4);
		result=result^(result>>2);
		result=result^(result>>1);
		cpu.eflags.PF=(!(result&1))?1:0;
		uint8_t adest=~dest;
		int cin=1;
		int acin=0;
		int i;
		for(i=1;i<=8;++i)
		{
			int a1=adest&1;
			adest>>=1;
			int a2=src&1;
			src>>=1;
			int rel=a1+a2+cin;
			if(rel==2||rel==3) cin=1;
			else cin=0;
			if(i==7) acin=cin;
		}
		cpu.eflags.CF=(!cin)?1:0;
		cpu.eflags.OF=cin^acin;
		incdec=(cpu.eflags.DF==0)?1:-1;
	}
	else
	{
		if(ops_decoded.is_data_size_16)
		{
			uint16_t src=swaddr_read(cpu.esi,2);
			uint16_t dest=swaddr_read(cpu.edi,2);
			uint16_t result=src-dest;
			cpu.eflags.SF=(result&0x8000)?1:0;
			cpu.eflags.ZF=(result==0)?1:0;
			int8_t low=result&0x00ff;
			low=low^(low>>4);
			low=low^(low>>2);
			low=low^(low>>1);
			cpu.eflags.PF=(!(low&1))?1:0;
			uint16_t adest=~dest;
			int cin=1;
			int acin=0;
			int i;
			for(i=1;i<=16;++i)
			{
				int a1=adest&1;
				adest>>=1;
				int a2=src&1;
				src>>=1;
				int rel=(a1+a2+cin);
				if(rel==2 || rel==3) cin=1;
				else cin=0;
				if(i==15) acin=cin;
			}
			cpu.eflags.CF=(!(cin))?1:0;
			cpu.eflags.OF=cin^acin;
			incdec=(cpu.eflags.DF==0)?2:-2;
		}
		else 
		{
			uint32_t src=swaddr_read(cpu.esi,4);
			uint32_t dest=swaddr_read(cpu.edi,4);
			uint32_t result=src-dest;
			cpu.eflags.SF=(result&0x80000000)?1:0;
			cpu.eflags.ZF=(result==0)?1:0;
			int8_t low=result&0x000000ff;
			low=low^(low>>4);
			low=low^(low>>2);
			low=low^(low>>1);
			cpu.eflags.PF=(!(low&1))?1:0;
			uint32_t adest=~dest;
			int cin=1;
			int acin=0;
			int i;
			for(i=1;i<=32;++i)
			{
				int a1=adest&1;
				adest>>=1;
				int a2=src&1;
				src>>=1;
				int rel=a1+a2+cin;
				if(rel==2 || rel==3) cin=1;
				else cin=0;
				if(i==31) acin=cin;
			}
			cpu.eflags.CF=(!cin)?1:0;
			cpu.eflags.OF=cin^acin;
			incdec=(cpu.eflags.DF==0)?4:-4;
		}
	}
	cpu.esi=cpu.esi+incdec;
	cpu.edi=cpu.edi+incdec;
	return 1;
}
