#include "cpu/exec/template-start.h"
#include "cpu/decode/modrm.h"
#include "nemu.h"
#define instr crmov

static void do_execute()
{
  ModR_M m;
  m.val=swaddr_read(cpu.eip+2,1,0);
  if(ops_decoded.opcode==0x120)
  {
   switch (m.reg)
   {
      case 0:cpu.gpr[m.R_M]._32=cpu.CR0.val;break;
      case 3:cpu.gpr[m.R_M]._32=cpu.CR3.val;break;
      default:panic("error");
   }
  }
  else if(ops_decoded.opcode==0x122)
   {
     switch(m.reg)
     {
       case 0:cpu.CR0.val=cpu.gpr[m.R_M]._32;break;
       case 3:cpu.CR3.val=cpu.gpr[m.R_M]._32;clear_tlb();break;
       default:panic("error");
      }
   }
  else panic("error\n");
  print_asm_template2();
}

make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
