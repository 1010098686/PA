#include"cpu/exec/template-start.h"

#define instr cmovcc

static void do_execute()
{
  bool flag=false;
  switch(ops_decoded.opcode)
  {
    case 0x47:flag=(cpu.eflags.CF==0 && cpu.eflags.ZF==0);break;
    case 0x43:flag=(cpu.eflags.CF==0);break;
    case 0x42:flag=(cpu.eflags.CF==1);break;
    case 0x46:flag=(cpu.eflags.CF==1 || cpu.eflags.ZF==1);break;
    case 0x44:flag=(cpu.eflags.ZF==1);break;
    case 0x4f:flag=(cpu.eflags.ZF==0 && cpu.eflags.SF==cpu.eflags.OF);break;
    case 0x4d:flag=(cpu.eflags.SF==cpu.eflags.OF);break;
    case 0x4c:flag=(cpu.eflags.SF!=cpu.eflags.OF);break;
    case 0x4e:flag=(cpu.eflags.ZF==1 || cpu.eflags.SF!=cpu.eflags.OF);break;
    case 0x45:flag=(cpu.eflags.ZF==0);break;
    case 0x41:flag=(cpu.eflags.OF==0);break;
    case 0x4b:flag=(cpu.eflags.PF==0);break;
    case 0x49:flag=(cpu.eflags.SF==0);break;
    case 0x40:flag=(cpu.eflags.OF==1);break;
    case 0x4a:flag=(cpu.eflags.PF==1);break;
    case 0x48:flag=(cpu.eflags.SF==1);break;
    default:flag=false;
    }
    if(flag) OPERAND_W(op_dest,op_src->val);
    print_asm_template2();
}
make_instr_helper(rm2r)

#include"cpu/exec/template-end.h"
