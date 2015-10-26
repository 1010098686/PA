#include"cpu/exec/template-start.h"

#define instr setcc

static void do_execute()
{
   bool flag=false;
   switch(ops_decoded.opcode)
   {
     case 0x197:flag=(cpu.eflags.CF==0 && cpu.eflags.ZF==0);break;
     case 0x193:flag=(cpu.eflags.CF==0);break;
     case 0x192:flag=(cpu.eflags.CF==1);break;
     case 0x196:flag=(cpu.eflags.CF==1 || cpu.eflags.ZF==1);break;
     case 0x194:flag=(cpu.eflags.ZF==1);break;
     case 0x19f:flag=(cpu.eflags.ZF==0 && cpu.eflags.SF==cpu.eflags.OF);break;
     case 0x19d:flag=(cpu.eflags.SF==cpu.eflags.OF);break;
     case 0x19c:flag=(cpu.eflags.SF!=cpu.eflags.OF);break;
     case 0x19e:flag=(cpu.eflags.ZF==1 || cpu.eflags.SF!=cpu.eflags.OF);break;
     case 0x195:flag=(cpu.eflags.ZF==0);break;
     case 0x191:flag=(cpu.eflags.OF==0);break;
     case 0x19b:flag=(cpu.eflags.PF==0);break;
     case 0x199:flag=(cpu.eflags.SF==0);break;
     case 0x190:flag=(cpu.eflags.OF==1);break;
     case 0x19a:flag=(cpu.eflags.PF==1);break;
     case 0x198:flag=(cpu.eflags.SF==1);break;
     default:flag=false;
     }
     if(flag) OPERAND_W(op_src,1);
     else OPERAND_W(op_src,0);
     print_asm_template1();
}
make_instr_helper(rm)

#include"cpu/exec/template-end.h"
