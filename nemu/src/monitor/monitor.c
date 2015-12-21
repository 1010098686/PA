#include "nemu.h"

#define ENTRY_START 0x100000

extern uint8_t entry [];
extern uint32_t entry_len;
extern char *exec_file;


void load_elf_tables(int, char *[]);
void init_regex();
void init_wp_list();
void init_ddr3();
void init_device();
void init_sdl();

FILE *log_fp = NULL;

static void init_log() {
	log_fp = fopen("log.txt", "w");
	Assert(log_fp, "Can not open 'log.txt'");
}

static void welcome() {
	printf("Welcome to NEMU!\nThe executable is %s.\nFor help, type \"help\"\n",
			exec_file);
}

void init_monitor(int argc, char *argv[]) {
	/* Perform some global initialization */

	/* Open the log file. */
	init_log();

	/* Load the string table and symbol table from the ELF file for future use. */
	load_elf_tables(argc, argv);

	/* Compile the regular expressions. */
	init_regex();

	/* Initialize the watchpoint link list. */
	init_wp_list();
	init_device();
	init_sdl();
	/* Display welcome message. */
	welcome();
}

#ifdef USE_RAMDISK
static void init_ramdisk() {
	int ret;
	const int ramdisk_max_size = 0xa0000;
	FILE *fp = fopen(exec_file, "rb");
	Assert(fp, "Can not open '%s'", exec_file);

	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);
	Assert(file_size < ramdisk_max_size, "file size(%zd) too large", file_size);

	fseek(fp, 0, SEEK_SET);
	ret = fread(hwa_to_va(0), file_size, 1, fp);
	assert(ret == 1);
	fclose(fp);
}
#endif

static void load_entry() {
	int ret;
	FILE *fp = fopen("entry", "rb");
	Assert(fp, "Can not open 'entry'");

	fseek(fp, 0, SEEK_END);
	size_t file_size = ftell(fp);

	fseek(fp, 0, SEEK_SET);
	ret = fread(hwa_to_va(ENTRY_START), file_size, 1, fp);
	assert(ret == 1);
	fclose(fp);
}

void restart() {
	/* Perform some initialization to restart a program */
#ifdef USE_RAMDISK
	/* Read the file with name `argv[1]' into ramdisk. */
	init_ramdisk();
#endif

	/* Read the entry code into memory. */
	load_entry();

	/* Set the initial instruction pointer. */
	cpu.eip = ENTRY_START;
	cpu.eflags.CF=0;
	cpu.eflags.PF=0;
	cpu.eflags.ZF=0;
	cpu.eflags.SF=0;
	cpu.eflags.IF=0;
	cpu.eflags.DF=0;
	cpu.eflags.OF=0;
	cpu.CR0.paging=0;
	cpu.CR0.task_switched=0;
	cpu.CR0.protect_enable=0;
	cpu.CR0.monitor_coprocessor=0;
	cpu.CR0.emulation=0;
	cpu.CR0.paging=0;
	cpu.CS.base_addr=0;
	cpu.CS.limit=0xffffffff;
	cpu.IDTR.base_addr = 0;
	cpu.IDTR.limit = 0x03ff;
	cpu.INTR = 0;
	/* Initialize DRAM. */
	init_ddr3();
	int i;
	for(i=0;i<128;++i)
	{
	   int j;
	   for(j=0;j<8;++j)
	     cache.cache_group[i].cache_block[j].valid=0;
  }
  for(i=0;i<4096;++i)
  {
    int j;
    for(j=0;j<16;++j)
      {
        cachel2.cachel2_group[i].cachel2_block[j].valid=0;
        cachel2.cachel2_group[i].cachel2_block[j].dirty=0;
      }
  }
	for(i=0;i<64;++i) tlb.tlb_block[i].valid=0;
}
