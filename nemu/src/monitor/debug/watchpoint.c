#include "monitor/watchpoint.h"
#include "monitor/expr.h"
#include<string.h>
#define NR_WP 32
uint32_t expr(char* e,bool* success);
void init_regex();
static WP wp_list[NR_WP];
static WP *head, *free_;

void init_wp_list() {
	int i;
	for(i = 0; i < NR_WP; i ++) {
		wp_list[i].NO = i;
		wp_list[i].next = &wp_list[i + 1];
		wp_list[i].exp[0]='\0';
		wp_list[i].value=0;
	}
	wp_list[NR_WP - 1].next = NULL;

	head = NULL;
	free_ = wp_list;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp()
{
	if(free_==NULL) 
	{
		assert(0);
	}
	else
	{
		WP* new=free_;
		free_=free_->next;
		new->next=NULL;
		return new;
	}
}
void free_wp(WP* wp)
{
	wp->next=free_;
	free_=wp;
}

void insert_wp(char* args)
{
	init_regex();
	bool flag=true;
	int value=expr(args,&flag);
	if(!flag)
	{
		printf("you input an invalid expression,fail to creat a new watchpoint\n");
		return ;
	}
	WP* new=new_wp();
	strcpy(new->exp,args);
	new->value=value;
	if(head==NULL)
	{
		head=new;
		head->NO=1;
	}
	else
	{
		WP* temp=head;
		while(temp->next!=NULL)
			temp=temp->next;
		new->NO=temp->NO+1;
		temp->next=new;
	}
	return ;
}

void delete_wp(int no)
{
	WP* p;
	if(head->NO==no)
	{
		p=head;
		head=head->next;
		free_wp(p);
		return ;
	}
	p=head;
	while( p->next!=NULL && p->next->NO!=no ) p=p->next;
	if(p->next==NULL)
	{
		printf("fail to find NO.%d watchpoint\n",no);
		return ;
	}
	else
	{
		WP* del=p->next;
		p->next=del->next;
		free_wp(del);
		return ;
	}
}

void display_wp()
{
	printf("NO\texp\t\tvalue\n");
	WP* p=head;
	while(p!=NULL)
	{
		printf("%d\t%s\t%d\n",p->NO,p->exp,p->value);
		p=p->next;
	}
}

bool haschanged(int* no)
{
	init_regex();
	WP* p=head;
	while(p!=NULL)
	{
		bool flag=true;
		int value=expr(p->exp,&flag);
		if(value!=p->value)
		{
			p->value=value;
			*no=p->NO;
			return true;
		}
	}
	return false;
}
