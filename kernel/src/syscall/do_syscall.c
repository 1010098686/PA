#include "irq.h"

#include <sys/syscall.h>
#include <string.h>

void add_irq_handle(int, void (*)(void));
void mm_brk(uint32_t);
void serial_printc(char);
int fs_open(const char*,int);
int fs_read(int,void*,int);
int fs_write(int,void*,int);
int fs_lseek(int,int,int);
int fs_close(int);
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
		/* TODO: Add more system calls. */
        case SYS_write:
		            {
						tf->eax = fs_write(tf->ebx,(void*)tf->ecx,tf->edx);
						break;
					}
		 case SYS_open:
					{
						const char* pathname =(char*) tf->ebx;
						int flag = tf->ecx;
						tf->eax = fs_open(pathname,flag);
						break;
					}
		 case SYS_read:
					{
						int fd = tf->ebx;
						void* buf =(void*) tf->ecx;
						int len = tf->edx;
						tf->eax = fs_read(fd,buf,len);
						break;
					}
		 case SYS_lseek:
					{
						int fd = tf->ebx;
						int offset = tf->ecx;
						int whence = tf->edx;
						tf->eax = fs_lseek(fd,offset,whence);
						break;
					}
		 case SYS_close:
					{
						int fd = tf->ebx;
						tf->eax = fs_close(fd);
						break;
					}
		default: panic("Unhandled system call: id = %d", tf->eax);
	}
}
