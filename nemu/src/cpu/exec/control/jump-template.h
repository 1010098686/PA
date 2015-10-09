#include"cpu/exec/template-start.h"

#define instr jump

static void do_execute()
{
  if(ops_decoded.opcode==0xeb || ops_decoded.opcode==0xe9)
  {
	  DATA_TYPE_S src=op_src->val;
	  cpu.eip+=src;
	  if(DATA_BYTE==2) cpu.eip=cpu.eip&0x0000ffff;
  }
  else if(ops_decoded.opcode==0xff)
  {
	  if(DATA_BYTE==2) cpu.eip=op_src->val&0x0000ffff;
	  else if(DATA_BYTE==4) cpu.eip=op_src->val;
  }

}

make_instr_helper(si)
make_instr_helper(rm)

#include"cpu/exec/template-end.h"
