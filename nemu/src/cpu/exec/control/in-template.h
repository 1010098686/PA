#include "cpu/exec/template-start.h"
uint32_t pio_read(ioaddr_t addr, size_t len);
#define instr in

static void do_execute()
{
  if(ops_decoded.opcode==0xe4 || ops_decoded.opcode==0xec)
  {
    cpu.gpr[0]._8[0] = pio_read(op_src->val,1);
  }
  else if(ops_decoded.is_data_size_16)
  {
    cpu.gpr[0]._16 = pio_read(op_src->val,2);
  }
  else
  {
    cpu.eax = pio_read(op_src->val,4);
  }
  print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(rm2r)

#include"cpu/exec/template-end.h"
