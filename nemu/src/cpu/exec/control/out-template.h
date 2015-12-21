#include "cpu/exec/template-start.h"
void pio_write(ioaddr_t addr, size_t len, uint32_t data);
#define instr out

static void do_execute()
{
  if(ops_decoded.opcode==0xe6 || ops_decoded.opcode==0xee)
  {
    pio_write(op_dest->val,1,cpu.gpr[0]._8[0]);
  }
  else if(ops_decoded.is_data_size_16)
  {
    pio_write(op_dest->val,2,cpu.gpr[0]._16);
  }
  else
  {
    pio_write(op_dest->val,4,cpu.eax);
  }
  print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"
