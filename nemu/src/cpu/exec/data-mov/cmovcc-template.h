#include"cpu/exec/template-start.h"

#define instr cmovcc

static void do_execute()
{
  bool flag=false;
  switch(ops_decoded.opcode)
  {
    case 0x147:flag=(cpu.eflags.CF==0 && cpu.eflags.ZF==0);break;
    case 0x143:flag=(cpu.eflags.CF==0);break;
    case 0x142:flag=(cpu.eflags.CF==1);break;
    case 0x146:flag=(cpu.eflags.CF==1 || cpu.eflags.ZF==1);break;
    case 0x144:flag=(cpu.eflags.ZF==1);break;
    case 0x14f:flag=(cpu.eflags.ZF==0 && cpu.eflags.SF==cpu.eflags.OF);break;
    case 0x14d:flag=(cpu.eflags.SF==cpu.eflags.OF);break;
    case 0x14c:flag=(cpu.eflags.SF!=cpu.eflags.OF);break;
    case 0x14e:flag=(cpu.eflags.ZF==1 || cpu.eflags.SF!=cpu.eflags.OF);break;
    case 0x145:flag=(cpu.eflags.ZF==0);break;
    case 0x141:flag=(cpu.eflags.OF==0);break;
    case 0x14b:flag=(cpu.eflags.PF==0);break;
    case 0x149:flag=(cpu.eflags.SF==0);break;
    case 0x140:flag=(cpu.eflags.OF==1);break;
    case 0x14a:flag=(cpu.eflags.PF==1);break;
    case 0x148:flag=(cpu.eflags.SF==1);break;
    default:flag=false;
    }
    if(flag) OPERAND_W(op_dest,op_src->val);
    print_asm_template2();
}
make_instr_helper(rm2r)

#include"cpu/exec/template-end.h"
