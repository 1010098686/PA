#include"cpu/exec/template-start.h"

#define instr setcc

static void do_execute()
{
   bool flag=false;
   switch(ops_decoded.opcode)
   {
     case 0x97:flag=(cpu.eflags.CF==0 && cpu.eflags.ZF==0);break;
     case 0x93:flag=(cpu.eflags.CF==0);break;
     case 0x92:flag=(cpu.eflags.CF==1);break;
     case 0x96:flag=(cpu.eflags.CF==1 || cpu.eflags.ZF==1);break;
     case 0x94:flag=(cpu.eflags.ZF==1);break;
     case 0x9f:flag=(cpu.eflags.ZF==0 && cpu.eflags.SF==cpu.eflags.OF);break;
     case 0x9d:flag=(cpu.eflags.SF==cpu.eflags.OF);break;
     case 0x9c:flag=(cpu.eflags.SF!=cpu.eflags.OF);break;
     case 0x9e:flag=(cpu.eflags.ZF==1 || cpu.eflags.SF!=cpu.eflags.OF);break;
     case 0x95:flag=(cpu.eflags.ZF==0);break;
     case 0x91:flag=(cpu.eflags.OF==0);break;
     case 0x9b:flag=(cpu.eflags.PF==0);break;
     case 0x99:flag=(cpu.eflags.SF==0);break;
     case 0x90:flag=(cpu.eflags.OF==1);break;
     case 0x9a:flag=(cpu.eflags.PF==1);break;
     case 0x98:flag=(cpu.eflags.SF==1);break;
     default:flag=false;
     }
     if(flag) OPERAND_W(op_src,1);
     else OPERAND_W(op_src,0);
     print_asm_template1();
}
make_instr_helper(rm)

#include"cpu/exec/template-end.h"
