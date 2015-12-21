#include "irq.h"

#include <sys/syscall.h>
#include <string.h>

void add_irq_handle(int, void (*)(void));
void mm_brk(uint32_t);
void serial_printc(char);
static void sys_brk(TrapFrame *tf) {
#ifdef IA32_PAGE
	mm_brk(tf->ebx);
#endif
	tf->eax = 0;
}

void do_syscall(TrapFrame *tf) {
	switch(tf->eax) {
		/* The ``add_irq_handle'' system call is artificial. We use it to
		 * let user program register its interrupt handlers. But this is
		 * very dangerous in a real operating system. Therefore such a
		 * system call never exists in GNU/Linux.
		 */
		case 0:
			cli();
			add_irq_handle(tf->ebx, (void*)tf->ecx);
			sti();
			break;

		case SYS_brk: sys_brk(tf); break;
    //case SYS_write:asm volatile(".byte 0xd6" : : "a"(2),"c"(tf->ecx),"d"(tf->edx)); tf->eax = strlen((char*)tf->ecx); break;
		/* TODO: Add more system calls. */
    case SYS_write:
		      {
						int i;
						for(i=0;i<tf->edx;++i) serial_printc(*((char*)tf->ecx));
						tf->eax = strlen((char*)tf->ecx);
						break;
					}
		default: panic("Unhandled system call: id = %d", tf->eax);
	}
}
