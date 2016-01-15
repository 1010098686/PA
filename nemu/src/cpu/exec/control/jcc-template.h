#include"cpu/exec/template-start.h"

#define instr jcc

static void do_execute()
{
   int flag=0;
   switch(ops_decoded.opcode)
   {
     case 0x77:flag=(cpu.eflags.CF==0 && cpu.eflags.ZF==0);break;  //ja
     case 0x187:flag=(cpu.eflags.CF==0 && cpu.eflags.ZF==0);break; //ja
     case 0x73:flag=(cpu.eflags.CF==0);break;  //jae
     case 0x183:flag=(cpu.eflags.CF==0);break; //jae
     case 0xe3:flag=((cpu.ecx&0x0000ffff)==0);break;   //jcxz
     case 0x74:flag=(cpu.eflags.ZF==1);break;  //jz
     case 0x184:flag=(cpu.eflags.ZF==1);break; //jz
     case 0x7f:flag=(cpu.eflags.ZF==0 && cpu.eflags.SF==cpu.eflags.OF);break; //jg
     case 0x18f:flag=(cpu.eflags.ZF==0 && cpu.eflags.SF==cpu.eflags.OF);break; //jg
     case 0x7d:flag=(cpu.eflags.SF==cpu.eflags.OF);break; //jge
     case 0x18d:flag=(cpu.eflags.SF==cpu.eflags.OF);break;//jge
     case 0x7c:flag=(cpu.eflags.SF!=cpu.eflags.OF);break;//jl
     case 0x18c:flag=(cpu.eflags.SF!=cpu.eflags.OF);break;//jl
     case 0x7e:flag=(cpu.eflags.ZF==1 || cpu.eflags.SF!=cpu.eflags.OF);break;//jle
     case 0x18e:flag=(cpu.eflags.ZF==1 || cpu.eflags.SF!=cpu.eflags.OF);break;//jle
     case 0x76:flag=(cpu.eflags.CF==1 || cpu.eflags.ZF==1); break;//jna
     case 0x186:flag=(cpu.eflags.CF==1 || cpu.eflags.ZF==1); break;//jna
     case 0x72:flag=(cpu.eflags.CF==1);break;//jb
     case 0x182:flag=(cpu.eflags.CF==1);break;//jb
     case 0x75:flag=(cpu.eflags.ZF==0);break;//jne
     case 0x185:flag=(cpu.eflags.ZF==0);break;//jne
     case 0x71:flag=(cpu.eflags.OF==0);break;//jno
     case 0x181:flag=(cpu.eflags.OF==0);break;//jno
     case 0x7b:flag=(cpu.eflags.PF==0);break;//jnp
     case 0x18b:flag=(cpu.eflags.PF==0);break;//jnp
     case 0x79:flag=(cpu.eflags.SF==0);break;//jns
     case 0x189:flag=(cpu.eflags.SF==0);break;//jns
     case 0x70:flag=(cpu.eflags.OF==1);break;//jo
     case 0x180:flag=(cpu.eflags.OF==1);break;//jo
     case 0x7a:flag=(cpu.eflags.PF==1);break;//jp
     case 0x18a:flag=(cpu.eflags.PF==1);break;//jp
     case 0x78:flag=(cpu.eflags.SF==1);break;//js
     case 0x188:flag=(cpu.eflags.SF==1);break;//js
     default :assert(0);
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
