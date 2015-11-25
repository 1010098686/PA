#include "monitor/monitor.h"
#include "monitor/expr.h"
#include "monitor/watchpoint.h"
#include "nemu.h"
#include<string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

void cpu_exec(uint32_t);
uint32_t expr(char* e,bool* success);
void init_regex();
void init_wp_list();
WP* new_wp();
void free_wp(WP* wp);
void insert_wp(char* args);
void delete_wp(int no);
void display_wp();
void printstackframe();
/* We use the ``readline'' library to provide more flexibility to read from stdin. */
char* rl_gets() {
	static char *line_read = NULL;

	if (line_read) {
		free(line_read);
		line_read = NULL;
	}

	line_read = readline("(nemu) ");

	if (line_read && *line_read) {
		add_history(line_read);
	}

	return line_read;
}

static int cmd_c(char *args) {
	cpu_exec(-1);
	return 0;
}

static int cmd_q(char *args) {
	return -1;
}

static int cmd_help(char *args);
static int cmd_si(char *args);
static int cmd_info(char* args);
static int cmd_x(char* args);
static int cmd_p(char* args);
static int cmd_w(char* args);
static int cmd_d(char* args);
static int cmd_bt(char* args);
static int cmd_cache(char* args);
static struct {
	char *name;
	char *description;
	int (*handler) (char *);
} cmd_table [] = {
	{ "help", "Display informations about all supported commands", cmd_help },
	{ "c", "Continue the execution of the program", cmd_c },
	{ "q", "Exit NEMU", cmd_q },
    { "si","Let the program execute for n steps",cmd_si},
	{ "info","Display the state of registers",cmd_info},
	{ "x","Caculate the value of expression and display the content of the address",cmd_x},
	{ "p","Calculate an expression",cmd_p},
	{ "w","set an watchpoint,when the value of expression changes the progranm stops",cmd_w},
	{ "d","delete the watchpoint",cmd_d},
	{ "bt","print the frame of stack",cmd_bt},
	{ "cache","use an address to search cache",cmd_cache}
	/* TODO: Add more commands */

};

#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))

static int cmd_help(char *args) {
	/* extract the first argument */
	char *arg = strtok(NULL, " ");
	int i;

	if(arg == NULL) {
		/* no argument given */
		for(i = 0; i < NR_CMD; i ++) {
			printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
		}
	}
	else {
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(arg, cmd_table[i].name) == 0) {
				printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
				return 0;
			}
		}
		printf("Unknown command '%s'\n", arg);
	}
	return 0;
}
static int cmd_si(char* args)
{
	int steps;
	if ( args == NULL) steps=1;
	else
	{
		steps=atoi(args);	
	}
	cpu_exec(steps);
	return 0;
}

static int cmd_info(char* args)
{
	if(args==NULL) return 0;
	if (strcmp(args,"r") == 0)
	{
		printf("eax:	0x%x	%d\n",cpu.eax,cpu.eax);
		printf("edx:	0x%x	%d\n",cpu.edx,cpu.edx);
		printf("ecx:	0x%x	%d\n",cpu.ecx,cpu.ecx);
		printf("ebx:	0x%x	%d\n",cpu.ebx,cpu.ebx);
		printf("ebp:	0x%x	%d\n",cpu.ebp,cpu.ebp);
		printf("esi:	0x%x	%d\n",cpu.esi,cpu.esi);
		printf("edi:	0x%x	%d\n",cpu.edi,cpu.edi);
		printf("esp:	0x%x	%d\n",cpu.esp,cpu.esp);
		printf("eip:    0x%x	%d\n",cpu.eip,cpu.eip);
		printf("CF:		%d\n",cpu.eflags.CF);
		printf("OF:		%d\n",cpu.eflags.OF);
		printf("SF:		%d\n",cpu.eflags.SF);
		printf("ZF:		%d\n",cpu.eflags.ZF);
	}
	else if( strcmp(args,"w") == 0)
	{
		display_wp();
	}
	else if(strcmp(args,"seg")==0)
	{
	   printf("CS:0X%x\t0x%x\n",cpu.CS.base_addr,cpu.CS.limit);
	   printf("SS:0x%x\t0x%x\n",cpu.SS.base_addr,cpu.SS.limit);
	   printf("DS:0x%x\t0x%x\n",cpu.DS.base_addr,cpu.DS.limit);
	   printf("ES:0x%x\t0x%x\n",cpu.ES.base_addr,cpu.ES.limit);
	   printf("GDTR:0x%x\t0x%x\n",cpu.GDTR.base_addr,cpu.GDTR.limit);
	   printf("CR0:0x%x\n",cpu.CR0.val);
	}
	else 
	{
		printf("the command info needs an parameter\n");
	}
	return 0;
}

static int cmd_x(char *args)
{
	char* cnum=strtok(NULL," ");
	char* exp=strtok(NULL," ");
	int num=atoi(cnum);
	init_regex();
	bool flag=true;
	int addr=expr(exp,&flag);
	if(!flag)
	{
		printf("you input an invalid expression\n");
		return 0;
	}
	int i;
	for( i=1;i<=num;++i)
	{
		int content=swaddr_read(addr,4,2);
		printf("0x%.8x\t",content);
		addr+=4;
	}
	printf("\n");
	return 0;
}
static int cmd_p(char* args)
{
	init_regex();
	bool success=true;
	int result=expr(args,&success);
	if(!success) 
	{
		printf("you input an invalid expression!\n");
		return 0;
	}
	else
	{
		printf("%d\n",result);
		return 0;
	}
}
static int cmd_w(char* args)
{
	insert_wp(args);
	return 0;
}
static int cmd_d(char* args)
{
	if(args==NULL) 
	{
		printf("no argument\n");
		return 0;
	}
	int no=atoi(args);
	delete_wp(no);
	return 0;
}
static int cmd_bt(char* args)
{
	printstackframe();
	return 0;
}
static int cmd_cache(char* args)
{
  bool flag=false;
  hwaddr_t addr=expr(args,&flag);
  int num;
  if(hit(addr,&num))
  {
    int i;
    printf("valid:%d\n",cache.cache_group[cache_index(addr)].cache_block[num].valid);
    printf("tag:0x%x\n",cache.cache_group[cache_index(addr)].cache_block[num].tag);
    for(i=0;i<64;++i) printf("%x ",cache.cache_group[cache_index(addr)].cache_block[num].data[i]);
    printf("\n");
   }
   else
   {
     printf("fail to search the cache\n");
   }
   return 0;
}
void ui_mainloop() {
	init_wp_list();
	while(1) {
		char *str = rl_gets();
		char *str_end = str + strlen(str);

		/* extract the first token as the command */
		char *cmd = strtok(str, " ");
		if(cmd == NULL) { continue; }

		/* treat the remaining string as the arguments,
		 * which may need further parsing
		 */
		char *args = cmd + strlen(cmd) + 1;
		if(args >= str_end) {
			args = NULL;
		}

#ifdef HAS_DEVICE
		extern void sdl_clear_event_queue(void);
		sdl_clear_event_queue();
#endif

		int i;
		for(i = 0; i < NR_CMD; i ++) {
			if(strcmp(cmd, cmd_table[i].name) == 0) {
				if(cmd_table[i].handler(args) < 0) { return; }
				break;
			}
		}

		if(i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
	}
}
