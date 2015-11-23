#include "cpu/exec/template-start.h"

#define instr crmov

static void do_execute()
{
  if(ops_decoded.opcode==0x120) 
   OPERAND_W(op_src,cpu.CR0.val);
  else if(ops_decoded.opcode==0x122)
    cpu.CR0.val=op_src->val;
  else panic("error\n");
  print_asm_template2();
}

make_instr_helper(r)

#include "cpu/exec/template-end.h"
