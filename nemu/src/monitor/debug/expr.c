#include "nemu.h"

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <sys/types.h>
#include <regex.h>
#include<stdlib.h>
#include<string.h>
#define BAD_EXP -9999
enum {
	NOTYPE = 256, EQ,SUB,ADD,MUL,DIV,NUM,HEXNUM,REG,NEQ,AND,OR,NOT,L_BRACKET,R_BRACKET,MINUS,POINTER

	/* TODO: Add more token types */

};
uint32_t swaddr_read(swaddr_t addr,size_t len);
static struct rule {
	char *regex;
	int token_type;
} rules[] = {

	/* TODO: Add more rules.
	 * Pay attention to the precedence level of different rules.
	 */

	{" +",	NOTYPE},				// spaces
	{"$e[abcd]x",REG}, // register
	{"$e[bs]p",REG},
	{"$e[sd]i",REG},
	{"0[xX][0-9a-fA-F]+",HEXNUM},		    // hex number
	{"\\+", ADD},                   // plus
	{"&&",AND},                     // and
	{"\\|\\|",OR},                  // or
	{"!=",NEQ},                      // not equal
	{"!",NOT},                     // not 
	{"==", EQ},                     // equal
	{"-",SUB},                      // sub
	{"\\*",MUL},                   // multiply
	{"/",DIV},                      // divide
	{"[0-9]+",NUM},                   // numbers
	{"\\(",L_BRACKET},             // left bracket
	{"\\)",R_BRACKET}             // right bracket

};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX];

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
	int i;
	char error_msg[128];
	int ret;

	for(i = 0; i < NR_REGEX; i ++) {
		ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
		if(ret != 0) {
			regerror(ret, &re[i], error_msg, 128);
			Assert(ret != 0, "regex compilation failed: %s\n%s", error_msg, rules[i].regex);
		}
	}
}

typedef struct token {
	int type;
	char str[32];
} Token;

Token tokens[32];
int nr_token;

static bool make_token(char *e) {
	int position = 0;
	int i;
	regmatch_t pmatch;
	
	nr_token = 0;

	while(e[position] != '\0') {
		/* Try all rules one by one. */
		for(i = 0; i < NR_REGEX; i ++) {
			if(regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
				char *substr_start = e + position;
				int substr_len = pmatch.rm_eo;

				Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s", i, rules[i].regex, position, substr_len, substr_len, substr_start);
				position += substr_len;

				/* TODO: Now a new token is recognized with rules[i]. Add codes
				 * to record the token in the array ``tokens''. For certain 
				 * types of tokens, some extra actions should be performed.
				 */
				if(rules[i].token_type==NOTYPE);
				else
				{
				 tokens[nr_token].type=rules[i].token_type;
				 if(tokens[nr_token].type == NUM || tokens[nr_token].type==HEXNUM)
				   {
					strncpy(tokens[nr_token].str,substr_start,substr_len);
				   }  
				  ++nr_token;
				}
			/*	switch(rules[i].token_type) {
					case NOTYPE:
					case EQ:
					case ADD:
					case SUB:
					case MUL:
					case DIV:
					case NUM:
					case L_BRACKET:
					case R_BRACKET:break;
					default: panic("please implement me");
				}*/

				break;
			}
		}

		if(i == NR_REGEX) {
			printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
			return false;
		}
	}

	return true; 
}

int eval(int p,int q);
bool check_parentheses(int p,int q);
int find_dominant(int p,int q);
bool isoperator(int index);
bool isinbrackets(int index,int p,int q);
int priority(int i);
static int getnum(char ch);

uint32_t expr(char *e, bool *success) {
	if(!make_token(e)) {
		*success = false;
		return 0;
	}
    
	/* TODO: Insert codes to evaluate the expression. */
	int i;
	for(i=0;i<nr_token;++i)
		if(tokens[i].type==MUL&& (i==0||isoperator(i-1)|| tokens[i-1].type==L_BRACKET))
			tokens[i].type=POINTER;
		else if(tokens[i].type==SUB&& (i==0||isoperator(i-1)||tokens[i-1].type==L_BRACKET))
			tokens[i].type=MINUS;
    return eval(0,nr_token-1);

	//panic("please implement me");
	return 0;
}

static int getnum(char ch)
{
	if(ch>='0' && ch<='9') return ch-'0';
	else if(ch>='a'&&ch<='f') return ch-'a'+10;
	else if(ch>='A'&& ch<='F') return ch-'A'+10;
	return 0;
}
bool isoperator(int index)
{
	if(tokens[index].type==ADD || tokens[index].type==SUB || tokens[index].type==MUL || tokens[index].type==DIV || tokens[index].type==MINUS || tokens[index].type==POINTER) return true;
	else return false;
}

bool isinbrackets(int index,int p,int q)
{
	int pos1,num1=0;
	for(pos1=index;pos1>=p;--pos1)
		if(tokens[pos1].type==R_BRACKET) ++num1;
		else if(tokens[pos1].type==L_BRACKET)
		{
			if(num1!=0) --num1;
			else
			{
				int pos2,num2=0;
				for(pos2=index;pos2<=q;++pos2)
					if(tokens[pos2].type==L_BRACKET) ++num2;
					else if(tokens[pos2].type==R_BRACKET)
					{
						if( num2!=0) --num2;
						else return true;
					}
				return false;
			}
		}	
	return false;
}

int priority(int i)
{
	if(tokens[i].type==MUL || tokens[i].type==DIV) return 2;
	else if(tokens[i].type==ADD || tokens[i].type==SUB) return 1;
	else if(tokens[i].type==MINUS || tokens[i].type==POINTER) return 3;
	else return 3;
}

int find_dominant(int p,int q)
{
	int i;
	int* temp=(int*)malloc(sizeof(int)*(q-p));
	int last=0; 
	for(i=p;i<=q;++i)
	{
		if(isoperator(i) && !isinbrackets(i,p,q) )
		{
			temp[last]=i;
			++last;
		}
	}
	int min=0;
	for(i=0;i<last;++i)
		if(priority(temp[i])<priority(temp[min])) min=i;
	for(i=last-1;i>=0;--i)
		if(priority(temp[i])==priority(temp[min])) 
		{
			int result=temp[i];
			free(temp);
			return result;
		}
	int result=temp[min];
	free(temp);
	return result;
}

bool check_parentheses(int p,int q)
{
	if(tokens[p].type==L_BRACKET && tokens[q].type==R_BRACKET)
	{
		int num=0,i;
		for(i=p+1;i<q;++i)
		{
			if(tokens[i].type==L_BRACKET) ++num;
			else if(tokens[i].type==R_BRACKET) --num;
		}
		if(num!=0) return false;
		else
		{
			for(i=p+1;i<q;++i)
				if(tokens[i].type==L_BRACKET)
				{
					int j=q-1;
					for(;j>=i+1;--j)
						if(tokens[j].type==R_BRACKET)
						{
							bool judge=check_parentheses(i,j);
							if(!judge) return false;
							else return true;
						}
					if(j==i) return false;
				}
			return true;
		}

	}
	else return false;
	return false;
}

int eval(int p,int q)
{
	if(p>q)
	{
		return BAD_EXP;
	}
	else if(p==q)
	{
		if(tokens[p].type==NUM) return atoi(tokens[p].str);
		else if(tokens[p].type==HEXNUM)
		{
			int sum=0;
			int len=strlen(tokens[p].str);
			char* str=(char*)malloc(sizeof(char)*len+1);
			strcpy(str,tokens[p].str);
			int i;
			for(i=2;i<len;++i)
				sum=sum*16+getnum(str[i]);
			return sum;
		}
		else if(tokens[p].type==REG)
		{
			if(strcmp(tokens[p].str,"eax")==0) return cpu.eax;
			else if(strcmp(tokens[p].str,"$ebx")==0) return cpu.ebx;
			else if(strcmp(tokens[p].str,"$ecx")==0) return cpu.ecx;
			else if(strcmp(tokens[p].str,"$edx")==0) return cpu.edx;
			else if(strcmp(tokens[p].str,"$ebp")==0) return cpu.ebp;
			else if(strcmp(tokens[p].str,"$esp")==0) return cpu.esp;
			else if(strcmp(tokens[p].str,"$esi")==0) return cpu.esi;
			else if(strcmp(tokens[p].str,"$edi")==0) return cpu.edi;
			else;
		}
		else;
	}
	else if(check_parentheses(p,q))
	{
		return eval(p+1,q-1);
	}
	else 
	{
		int op=find_dominant(p,q);
		if(tokens[op].type==POINTER)
			return swaddr_read(eval(p+1,q),4);
		else if(tokens[op].type==MINUS)
			return -eval(p+1,q);
		else if(tokens[op].type==NOT)
			return !eval(p+1,q);
		else
		{
			int val1=eval(p,op-1);
			int val2=eval(op+1,q);
			switch(tokens[op].type)
			{
				case ADD:return val1+val2;break;
				case SUB:return val1-val2;break;
				case MUL:return val1*val2;break;
				case DIV:return val1/val2;break;
				case AND:return val1&&val2;break;
				case OR:return val1||val2;break;
				case EQ:return val1==val2;break;
				case NEQ:return val1!=val2;break;
				default:assert(0);
			}
		}
	}
	return 0;
}
