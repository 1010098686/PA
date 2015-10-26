#include"cpu/exec/template-start.h"

#define instr jcc

static void do_execute()
{
   bool flag=false;
   switch(ops_decoded.opcode)
   {
     case 0x77:
     case 0x87:flag=(cpu.eflags.CF==0 && cpu.eflags.ZF==0);break;
     case 0x73:
     case 0x83:flag=(cpu.eflags.CF==0);break;
     case 0xe3:flag=(cpu.ecx==0);break;
     case 0x74:
     case 0x84:flag=(cpu.eflags.ZF==1);break;
     case 0x7f:
     case 0x8f:flag=(cpu.eflags.ZF==0 && cpu.eflags.SF==cpu.eflags.OF);break;
     case 0x7d:
     case 0x8d:flag=(cpu.eflags.SF==cpu.eflags.OF);break;
     case 0x7c:
     case 0x8c:flag=(cpu.eflags.SF!=cpu.eflags.OF);break;
     case 0x7e:
     case 0x8e:flag=(cpu.eflags.ZF==1 || cpu.eflags.SF!=cpu.eflags.OF);break;
     case 0x76:
     case 0x86:flag=(cpu.eflags.CF==1 || cpu.eflags.ZF==1); break;
     case 0x72:
     case 0x82:flag=(cpu.eflags.CF==1);break;
     case 0x75:
     case 0x85:flag=(cpu.eflags.ZF==0);break;
     case 0x71:
     case 0x81:flag=(cpu.eflags.OF==0);break;
     case 0x7b:
     case 0x8b:flag=(cpu.eflags.PF==0);break;
     case 0x79:
     case 0x89:flag=(cpu.eflags.SF==0);break;
     case 0x70:
     case 0x80:flag=(cpu.eflags.OF==1);break;
     case 0x7a:
     case 0x8a:flag=(cpu.eflags.PF==1);break;
     case 0x78:
     case 0x88:flag=(cpu.eflags.SF==1);break;
     default :flag=false;
     }
     if(flag)
     {
        cpu.eip+=op_src->val;
        if(DATA_BYTE==2) cpu.eip=cpu.eip&0x0000ffff;
     }
     print_asm_template1();
}

make_instr_helper(si)

#include"cpu/exec/template-end.h"
