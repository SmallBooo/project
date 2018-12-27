# include <iostream>
# include <string.h>
using namespace std;
char prog[1000],ch,token[8];
int p=0,sym=0,n;
char filename[30]; 
FILE *fpin;
char *keyword[8]={"if","then","else","end","repeat","until","read","write"};
void GetToken();
int main() 
{
	p=0;
	cout<<"请输入源文件名:";
	for(;;)
	{
		cin>>filename;
		if((fpin=fopen(filename,"r"))!=NULL)  //用*fpin指针只读打开文件 
		   break;
		else cout<<"文件路径错误！请输入源文件名:";
	}
	do
	{
		ch=fgetc(fpin);  //从指针所指文件读取一个字符赋给ch 
		prog[p++]=ch;
	}while(ch!=EOF);     //判断ch与为念结尾字符是否相等 
	p=0;
	do
	{
		GetToken();
		switch(sym)
		{
			case -1:
			case -2:break;
			default:cout<<"("<<sym<<","<<token<<")"<<endl;break;	
		}
	}while(ch!=EOF);
	
}
void GetToken()
{
	for(n=0;n<8;n++)
	{
		token[n]='\0';
	}
	n=0;
	ch=prog[p++];
	while(ch==' '||ch=='\n'||ch=='\t'){ch=prog[p++]	;}
	if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
	{
		sym=1;
		do{
			
			token[n++]=ch;
			ch=prog[p++];
		}while((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'));
		sym=2;
		for(n=0;n<8;n++)
		{
			if(strcmp(token,keyword[n])==0)
			{
				sym=n+3;
			}
		}
		p--;
	}
	else if(ch=='{')
	{
		do{
			ch=prog[p++];
		}while(ch!='}');
		sym=-1;
		return;
	}
	else if(ch>='0'&&ch<='9')
	{
		sym=11;
		do
		{
			token[n++]=ch;
			ch=prog[p++];
		}while(ch>='0'&&ch<='9');
		sym=12;
		p--;
		return;
	}
	else
	{
		switch(ch)
		{
			
			case '+':sym=13;token[0]=ch;break;
			case '-':sym=14;token[0]=ch;break;
			case '*':sym=15;token[0]=ch;break;
			case '/':sym=16;token[0]=ch;break;
			case '=':sym=17;token[0]=ch;break;
			case '<':sym=18;token[0]=ch;break;
			case ';':sym=19;token[0]=ch;break;
			default:sym=-2;cout<<"词法分析错误，请检查是否输入非法字符！\n";break;  
		}
	}
}
