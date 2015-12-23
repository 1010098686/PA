#include "common.h"
#include "memory.h"
#include <string.h>
#include "x86.h"

#define VMEM_ADDR 0xa0000
#define SCR_SIZE (320 * 200)

/* Use the function to get the start address of user page directory. */
inline PDE* get_updir();
void create_video_mapping() {
	/* TODO: create an identical mapping from virtual memory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memory area
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */
	//panic("please implement me");
	static PTE uptable[PHY_MEM/PAGE_SIZE] align_to_page;
	PDE* pdir = get_updir();
	PTE* ptab = (PTE*)va_to_pa(uptable);
	pdir[0].val = make_pde(ptab);
	int i=0;
	/*for(i=160;i<=175;++i)
	{
		uptable[i].val = make_pte(i*4096);
	}*/
	for(;i<=VMEM_ADDR+SCR_SIZE;i+=PAGE_SIZE)
	{
		ptab->val = make_pte(i);
		ptab++;
	}
  
}

void video_mapping_write_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		buf[i] = i;
	}
}

void video_mapping_read_test() {
	int i;
	uint32_t *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		assert(buf[i] == i);
	}
}

void video_mapping_clear() {
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}
