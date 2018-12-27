#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using  namespace std;
#define MAX 20
int table[12][9]={
{5,-1,-1,4,-1,-1,1,2,3},
{-1,6,-1,-1,-1,12,-1,-1,-1},
{-1,22,7,-1,22,22,-1,-1,-1},
{-1,24,24,-1,24,24,-1,-1,-1},
{5,-1,-1,4,-1,-1,8,2,3},
{-1,26,26,-1,26,26,-1,-1,-1},
{5,-1,-1,4,-1,-1,-1,9,3},
{5,-1,-1,4,-1,-1,-1,-1,10},
{-1,6,-1,-1,11,-1,-1,-1,-1},
{-1,21,7,-1,21,21,-1,-1,-1},
{-1,23,23,-1,23,23,-1,-1,-1},
{-1,25,25,-1,25,25,-1,-1,-1}};
struct rule{
	char x;
	int y;
}r[6]={{'E',3},{'E',1},{'T',3},{'T',1},{'F',3},{'F',1}};
char index_char[9]={'i','+','*','(',')','#','E','T','F'};
int get_index_char(char i)
{
	for (int j=0;j<9;j++)
	{
		if(index_char[j]==i)
		return j;
	}
	return -1;
}
typedef struct{
	int stack[MAX];
	int top;
}status;
void init_stack(status *p)
{
	if(!p)
	cout<<"³õÊ¼»¯×´Ì¬Õ»³ö´í£¡\n";
	p->top=-1;
}
void push(status *p,int x)
{
	if(p->top<MAX-1)
	{
		p->top++;
		p->stack[p->top]=x;
	}
	else cout<<"\n×´Ì¬Õ»Òç³ö£¡\n";
}
int pop(status *p)
{
	int x;
	if(p->top!=0)
	{
		x=p->stack[p->top];
		p->top--;
		return x;
	}
	else 
	{
		cout<<"\n×´Ì¬Õ»1¿Õ!\n";
		return 0;
	}
}
int get_top(status *p)
{
	int x;
	if(p->top!=-1)
	{
		x=p->stack[p->top];
		return x;
	}
	else
	{
		cout<<"\n×´Ì¬Õ»2¿Õ!\n";
		return 0;
	}
}
void out_stack(status *p)
{
	int i;
	if(p->top<0)
	cout<<"\n×´Ì¬Õ»3¿Õ!\n";
	for(i=0;i<=p->top;i++)
	{
		cout<<p->stack[i];
	}
}
typedef struct{
	char stack[MAX];
	int top;
}symbol_instr;
void init_stack(symbol_instr *p)
{
	if(!p)
	cout<<"\n³õÊ¼»¯·ûºÅÕ»³ö´í!\n";
	p->top=-1;
}
void push(symbol_instr *p,char x)
{
	if(p->top<MAX-1)
	{
		p->top++;
		p->stack[p->top]=x;
	}
	else cout<<"\n·ûºÅÕ»Òç³ö£¡\n";
}
char pop(symbol_instr *p)
{
	char x;
	if(p->top!=-1)
	{
		x=p->stack[p->top];
		p->top--;
		return x;
	}
	else
	{
		cout<<"\n·ûºÅÕ»1¿Õ£¡\n";
		return 0;
	}
}
char get_top(symbol_instr *p)
{
	char x;
	if(p->top!=-1)
	{
		x=p->stack[p->top];
		return x;
	}
	else
	{
		cout<<"\n·ûºÅÕ»2¿Õ!\n";
		return 0;
	}
}
void out_stack1(symbol_instr *p)
{
	int i;
	if(p->top<0)
	cout<<"\n·ûºÅÕ»3¿Õ£¡\n";
	for(i=0;i<=p->top;i++)
	{
		cout<<p->stack[i];
	}
}
void out_stack2(symbol_instr *p)
{
	int i;
	if(p->top<0)
	cout<<"\n·ûºÅÕ»4¿Õ£¡\n";
	for(i=p->top;i>=0;i--)
	{
		cout<<p->stack[i];
	}
}
void print(status *status_p,symbol_instr *symbol_p,symbol_instr *instr_p)
{
	int i;
	out_stack(status_p);
	for(i=0;i<20-status_p->top;i++)
	cout<<" ";
	out_stack1(symbol_p);
	for(i=0;i<20;i++)
	cout<<" ";
	out_stack2(instr_p);
	cout<<endl;
}
int goto_char(status *status_p,symbol_instr*symbol_p,symbol_instr*instr_p)
{
	char x;
	int y,z;
	x=get_top(instr_p);
	y=get_top(status_p);
	z=get_index_char(x);
	return table[y][z];
}
void action(status*status_p,symbol_instr*symbol_p,symbol_instr*instr_p)
{
	int i,j,x;
	char a;
	i=goto_char(status_p,symbol_p,instr_p);
	
	if(i==-1)
	cout<<"¹éÔ¼³ö´í£¡\n";
	if(i==12)
	cout<<"¹éÔ¼³É¹¦£¡\n";
	if(i>=0&&i<=11)
	{
		push(status_p,i);
		a=pop(instr_p);
		push(symbol_p,a);
		print(status_p,symbol_p,instr_p);
		action(status_p,symbol_p,instr_p);
	 } 
	 if(i>=21&&1<+26)
	 {
	 	x=r[i-21].y;
	 	for(j=0;j<x;j++)
	 	{
	 		pop(status_p);
	 		pop(symbol_p);
	 		
		} 
		push(instr_p,r[i-21].x);
		action(status_p,symbol_p,instr_p);
	 }
}
int main()
{
	char x;
	status *status_p;
	symbol_instr*symbol_p,*instr_p;
	status_p=(status*)malloc(sizeof(status));
	symbol_p=(symbol_instr*)malloc(sizeof(symbol_instr));
	instr_p=(symbol_instr*)malloc(sizeof(symbol_instr));
	init_stack(status_p);
	init_stack(symbol_p);
	init_stack(instr_p);
	push(status_p,0);
	push(symbol_p,'#');
	cout<<"ÇëÊäÈëÒª·ÖÎöµÄÎÄ¼þÎ»ÖÃºÍºó×º£º\n";//´Ë´¦ÎÄ¼þµÄ½áÎ²±ØÐëÎª# 
	char filepath[50];
	gets(filepath);
	if(freopen(filepath,"r",stdin)==NULL)
	{
		puts("ÎÄ¼þÎ»ÖÃ²»´æÔÚ£¡");
		return 0;
	} 
	//cout<<"ÇëÊäÈëÒª¹éÄÉµÄÊäÈë´®£¬ÒÔ'#'×Ö·û½áÊø£¡\n";
	do{
		x=getchar();
		if(x!=' '||x!='\t'||x!='\n')
		push(symbol_p,x);
	}while(x!='#');
	while(symbol_p->top!=0)
	{
		x=pop(symbol_p);
		push(instr_p,x);
	}
	cout<<"\n\n"; 
	cout<<"\n×´Ì¬Õ»              ·ûºÅÕ»             ÊäÈë´®\n";
	print(status_p,symbol_p,instr_p);
	action(status_p,symbol_p,instr_p);
	return 0;
}
