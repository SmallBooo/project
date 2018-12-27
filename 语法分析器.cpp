# include <iostream>
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
using namespace std; 
char *keyword[8]= {"if", "for", "else", "while", "do", "float","int", "break"};
char keywordtable[20][20], re_keywordtable[20][20];  //��ű�����
char digittable[20][20], re_digittable[ 20][20];  //�������
char otherchartable[20][20], re_otherchartable[20][20];  //��������ַ�
char idtable[20][20],re_idtable[20][20];//��ű�ʶ��
char notetable[20][20];  //���ע��
char finaltable[100][20];  //����ս��
int finaltableint[100];
char  word[20];
void initialize();
void alpha();
void digit();
void error();
void otherchar();
void note();
void print();
void program();
void block();
void stmts();
void stmt();
void Bool();
void expr();
void expr1();
void term();
void term1();
void factor();
void match(char *t);
int digit_num=0,keyword_num=0,otherchar_num=0,id_num=0,note_num=0;
int redigit_num=1,rekeyword_num=1,reotherchar_num=1,reid_num=1;
int final_num=0,finalnum=0;
int flag_error=0;                //0��ʾû�д���1��ʾ�д��� 
int flagerror=0;
char lookahead;
int main ()
{
	printf("������Ҫ���������:\n");
	initialize();
	while(1)
	{
		lookahead=getchar();    //�ӱ�׼�������ж�һ���ַ� 
		if(isalpha(lookahead))   //�����ж��ַ�lookahead�Ƿ�ΪӢ����ĸ
		                         //a-z��A-Zʱ���ط�0ֵ����һ����1���� ���򷵻�0
		{
			alpha();
			initialize();					 	
		} 
		else if(isdigit(lookahead))
		{
			digit();
			initialize();
		}
		else if(lookahead=='\t'||lookahead==' ')
		{
			continue;
		}
		else if(lookahead=='\n')
		break;
		else if(lookahead=='/')
		{
			lookahead=getchar();
			if(lookahead=='*')
			{
				note();
				initialize();
			}
			else
			{
				ungetc(lookahead,stdin);  //��һ���ַ��˻ص���������
				                          //Lookahead��д����ַ���stdin���ļ���ָ��
				strcpy(finaltable[final_num],"/");    //��"/"�ŵ��ս���ű��� 
				strcpy(otherchartable[otherchar_num++],"/")	;  //��"/"�ŵ��������ű���
				finaltableint[final_num++]=2;                  //"/"�������2 
				initialize(); 
			}
			}
			else
			{
				otherchar();
				initialize();
			 } 
		}
		if(flag_error==0)
		{
			print();
			program();
			if(finalnum==final_num)
			    printf("�﷨������ɣ�\n");
		}
	 } 
	 void alpha()
	 {
	 	int i=1,flag;
	 	char ch;
	 	ch=lookahead;
	 	word[0]=ch;
	 	ch=getchar();
	 	while(isalpha(ch)||isdigit(ch))    //����ʶ���ŵ�word������ 
	 	{
	 		word[i++]=ch;
	 		ch=getchar();
		 }
		 ungetc(ch,stdin);
		 flag=0;
		 for(i=0;i<8;i++)
		 {
		 	if(strcmp(word,keyword[i])==0)
		 	  flag=1;
		 }
		 if(flag==1)                       //�Ǳ����� 
		 {
		 	strcpy(keywordtable[keyword_num++],word);   //�������ָ��Ƶ������ֱ��� 
		 	strcpy(finaltable[final_num],word);         // �����ָ��Ƶ��ս������ 
		 	if(strcmp(word,"if")==0)
		 	    finaltableint[final_num++]==100;        //if�ս�������Ϊ100 
		 	if(strcmp(word,"for")==0)
		 	    finaltableint[final_num++]==200;
		 	if(strcmp(word,"else")==0)
		 	    finaltableint[final_num++]==300;
		 	if(strcmp(word,"while")==0)
		 	    finaltableint[final_num++]==400;
			if(strcmp(word,"do")==0)
		 	    finaltableint[final_num++]==500;
		 	if(strcmp(word,"float")==0)
		 	    finaltableint[final_num++]==600;
		 	if(strcmp(word,"int")==0)
		 	    finaltableint[final_num++]==700;
		    if(strcmp(word,"break")==0)
		 	    finaltableint[final_num++]==800; 
		 }
		 else                                           //���Ǳ����֣��Ǳ�ʶ�� 
		 {
		 	strcpy(idtable[id_num++],word);             //�ѱ�ʶ�����Ƶ���ʶ������ 
		 	strcpy(finaltable[final_num],"id");         //�ս���ű��д��id 
		 	finaltableint[final_num++]=1;               //��ʶ�������Ϊ1 
		 }
	 }
	 void initialize()                 //��ʼ����������� 
	 {
	 	int i;
	 	for(i=0;i<20;i++)
	 	{
	 		word[i]='\0';
		 }
	  } 
	 void digit()                    //�����ֿ�ͷ�Ĵ��ŵ�word������
	 {
	 	int i=1,flag;
	 	char ch;
	 	ch=lookahead;
	 	word[0]=ch;
	 	ch=getchar();
	 	while(isalpha(ch)||isdigit(ch))
	 	{
	 		word[i++]=ch;
	 		ch=getchar();
		 }
		 ungetc(ch,stdin);
		 flag=0;
		 for(i=0;word[i]!='\0';i++)
		 {
		 	if(word[i]<'0'||word[i]>'9')
		 	flag=1;
		 }
		 if(flag==1)      //�����һ���ַ��������֣��򽫸��ַ������ڱ�ʶ��������
		 {
		 	strcpy(idtable[id_num++],word);          
		 	strcpy(finaltable[final_num],"id");          
		 	finaltableint[final_num++]=1;
		  } 
		  else           //����������֣������ŵ����ִ�������
		  {
		  		strcpy(digittable[digit_num++],word);          
		 	strcpy(finaltable[final_num],"num");          
		 	finaltableint[final_num++]=99;        //���ֵ������99 
		   } 
	  } 
	  void note()
	  {
	  	char ch;
	  	int i=0;
	  	ch=getchar();
	  	while(1)
	  	{
	  			if(ch=='*')
	  			{
	  				ch=getchar();
	  				if(ch=='/')            //��/*.......*/ֱ������ѭ��
					  break;               //��/*.......*/����� 
				    else
				    {
				    	ungetc(ch,stdin);
				    	word[i++]=ch;
					}
				  }
				  else                      //��/*.......*/����� 
				  {
				  	word[i++]=ch;           //word������ע�͵����� 
				   } 
				   ch=getchar(); 
		 }
			  strcpy(notetable[note_num++],word);    //��ע�͵����ݴ�ŵ�ע�ͱ��� 
		  }
		  void otherchar()		  
		  {
		  	char ch;
		  	ch=lookahead;
		  	switch(ch){
		  		case '!':
		  			{
		  				ch=getchar();
		  				if(ch=='=')
		  				{
		  				    strcpy(otherchartable[otherchar_num++],"!=");          
		 	                strcpy(finaltable[final_num],"!=");          
		                   	finaltableint[final_num++]=3;      //"!="�������3 
						  }
						  else
						  {
						  	ungetc(ch,stdin);
						  	error();
						   } 
					  }
					  break;
					  
					  
				case '=':
		  			{
		  				ch=getchar();
		  				if(ch=='=')
		  				{
		  				    strcpy(otherchartable[otherchar_num++],"==");          
		 	                strcpy(finaltable[final_num],"==");         
		                   	finaltableint[final_num++]=4;      //"=="�������4
						  }
						  else
						  {
						    strcpy(otherchartable[otherchar_num++],"=");          
		 	                strcpy(finaltable[final_num],"=");          
		                   	finaltableint[final_num++]=5;      //"="�������5
		                   	ungetc(ch,stdin);
						   } 
					  }
					  break;
					  
						case '(':
		  				    strcpy(otherchartable[otherchar_num++],"(");          
		 	                strcpy(finaltable[final_num],"(");         
		                   	finaltableint[final_num++]=6;      //"("�������6
						    break;
						     
			        	case ')':
		  				    strcpy(otherchartable[otherchar_num++],")");          
		 	                strcpy(finaltable[final_num],")");         
		                   	finaltableint[final_num++]=7;      //")"�������7
						    break;
						    
						case ';':
		  				    strcpy(otherchartable[otherchar_num++],";");          
		 	                strcpy(finaltable[final_num],";");         
		                   	finaltableint[final_num++]=8;      //";"�������8
						    break;
						    
						case '{':
		  				    strcpy(otherchartable[otherchar_num++],"{");          
		 	                strcpy(finaltable[final_num],"{");         
		                   	finaltableint[final_num++]=9;      //"{"�������9
						    break;
						    
						case '}':
		  				    strcpy(otherchartable[otherchar_num++],"}");          
		 	                strcpy(finaltable[final_num],"}");         
		                   	finaltableint[final_num++]=10;      //"}"�������10
						    break;
						    
						case '||':
		  				    strcpy(otherchartable[otherchar_num++],"||");          
		 	                strcpy(finaltable[final_num],"||");         
		                   	finaltableint[final_num++]=11;      //"||"�������11
						    break;
						    
						case '&&':
		  				    strcpy(otherchartable[otherchar_num++],"&&");          
		 	                strcpy(finaltable[final_num],"&&");         
		                   	finaltableint[final_num++]=12;      //"&&"�������12
						    break;
						    
						case '+':
		  				    strcpy(otherchartable[otherchar_num++],"+");          
		 	                strcpy(finaltable[final_num],"+");         
		                   	finaltableint[final_num++]=13;      //"+"�������13
						    break;
						    
						case '-':
		  				    strcpy(otherchartable[otherchar_num++],"-");          
		 	                strcpy(finaltable[final_num],"-");         
		                   	finaltableint[final_num++]=19;      //"-"�������19
						    break;
						    
						case '>':
		  		     	{
		  				ch=getchar();
		  				if(ch=='=')
		  				{
		  				    strcpy(otherchartable[otherchar_num++],">=");          
		 	                strcpy(finaltable[final_num],">=");         
		                   	finaltableint[final_num++]=14;      //">="�������14
						  }
						  else
						  {
						      strcpy(otherchartable[otherchar_num++],">");          
		 	                strcpy(finaltable[final_num],">");          
		                   	finaltableint[final_num++]=15;      //">"�������15
		                   	ungetc(ch,stdin);
						   } 
					    }
					    break;
					    
					    case '<':
		  		     	{
		  				ch=getchar();
		  				if(ch=='=')
		  				{
		  				    strcpy(otherchartable[otherchar_num++],"<=");          
		 	                strcpy(finaltable[final_num],"<=");         
		                   	finaltableint[final_num++]=16;      //"<="�������16
						  }
						  else
						  {
						      strcpy(otherchartable[otherchar_num++],"<");          
		 	                strcpy(finaltable[final_num],"<");          
		                   	finaltableint[final_num++]=17;      //"<"�������17
		                   	ungetc(ch,stdin);
						   } 
					    }
					    break;
					    
				     	case '*':     
		 	                strcpy(finaltable[final_num],"*");         
		                   	finaltableint[final_num++]=18;      //"*"�������18
						    break;
						default:
					    	error();
					     	break; 					
			  }
		  }
		  void error()
		  {
		  	flag_error=1;
		  	if(finalnum!=final_num)
		  	printf("���ִ�����ֹ������\n");
		  	
		  }
		  void print()
		  {
		  	int i;
		  	finaltableint[final_num]='\0';
		  	printf("�ʷ������������:\n");
		  	for(i=0;i<final_num;i++)
		  	    printf("%s",finaltable[i]);
		  	printf("\n�﷨�����������£�\n");
		  }
		  void program()
		  {
		  	printf("program-->block\n");
		  	block();
		  	if(flagerror==1)
		  	{
		  		error();
		  		return;
			  }
		  }
		  void block()
		  {
		  	if(flagerror==1)
		  	{
		  		return;
			  }
			  printf("block-->{stmts}\n");
			  match("{");
			  stmts();
			  match("}");
		  }
		  void stmts()
		  {
		  	if(flagerror==1)
		  	{
		  		return;
			  }
			if(finaltableint[finalnum]==10)     //�ڶ���������"}"
			{
				printf("stmts-->null\n");
				return;
			 } 
			 printf("stmts-->stmt stmts\n");
			 stmt();
			 stmts();
		  }
		  void stmt()
		  {
		  	if(flagerror==1)
		  	{
		  		return;
			  }
			  switch(finaltableint[finalnum])
			  {
			  	case 1:
			  		printf("stmt-->id=expr;\n");
			  		match("id");
			  		match("=");
			  		expr();
			  		match(";");
			  		break;
			  	case 100:
			  		match("if");
			  		match("(");
			  		Bool();
			  		match(")");
			  		stmt();
			  		if(strcmp(finaltable[finalnum],"else")==0)
					  {
					  	printf("stmt-->if(Bool)  stmt else stmt\n");
					  	match("else");
					  	stmt();
					  	break;
					   } 
				    else
					   {
					   	  	printf("stmt-->if(Bool)  stmt\n");
					   	  	break;
					   }
				case 400:
						printf("stmt-->while(Bool)  stmt\n");
						match("while");
						match("(");
						Bool();
						match(")");
						stmt();
					   	break;
				case 500:
						printf("stmt-->do stmt while(Bool)\n");
						match("do");
						stmt();
						match("while");
						match("(");
						Bool();
						match(")");
					   	break;
				case 800:
					printf("stmt-->break\n");
					match("break");
					break;
				default :
					printf("stmt-->block\n");
					block();
					break;
			  }
		  }
		  void Bool()
		  {
		  	if(flagerror==1)
		  	{
		  		return;
			  }
			  expr();
			  switch(finaltableint[finalnum])
			  {
			  	case 17:
			  		printf("bool-->expr<expr\n");
					match("<");
					expr();
					break;
				case 16:
			  		printf("bool-->expr<=expr\n");
					match("<=");
					expr();
					break;
				case 15:
			  		printf("bool-->expr>expr\n");
					match(">");
					expr();
					break;
				case 14:
			  		printf("bool-->expr>=expr\n");
					match(">=");
					expr();
					break;
				default :
			  		printf("bool-->expr\n");
					expr();
					break;
			  }
		  }
		  void expr()
		  {
		  		if(flagerror==1)
		  	{
		  		return;
			}
			  printf("expr-->term expr1\n");
			  term();
			  expr1();
		  }
		  void expr1()
		  {
		  		if(flagerror==1)
		  	{
		  		return;
			}
			  switch(finaltableint[finalnum])
			  {
			 	case 13:
			 		printf("expr1-->+term expr1\n");
					match("+");
					term();	 
					expr1();
					break;
				case 19:
				    printf("expr1-->-erm expr1\n");
					match("-");
					term();	 
					expr1();
					break;
				default :
					printf("expr1-->null\n");
					return;
			  }
		  }
		  void term()
		  {
		  		if(flagerror==1)
		  	{
		  		return;
			}
			printf("term-->factor term1\n");
			factor();
			term1();
		  }
		  void term1()
		  {
		  	if(flagerror==1)
		  	{
		  		return;
			}
			  switch(finaltableint[finalnum])
			  {
			  	case 18:
			  		printf("term1-->*factor term1\n");
			  		match("*");
		            factor();
			        term1();
			        break;
			    case 2:
			  		printf("term1-->/factor term1\n");
			  		match("/");
		            factor();
			        term1();
			        break;
			    default :
			    	printf("term1-->null\n");
			    	return;
			  }
	        }
          void factor()
          {
		  	if(flagerror==1)
		  	{
		  		return;
			}
			  switch(finaltableint[finalnum])
			  {
			  	case 6:
			  		printf("factor-->(expr)\n");
			  		match("(");
		            expr();
			        match(")");
			        break;
			    case 1:
			  		printf("factor-->id\n");
			  		match("id");
			        break;
			    case 99:
			  		printf("factor-->num\n");
			  		match("num");
			        break;
			    default :
			    	flagerror=1;
			    	return;
			  }
	        }
	        void match(char *t)
	        {
	        	if(strcmp(finaltable[finalnum],t)==0)
	        	
	        	;
	        	else
	        	{
	        		flagerror=1;
	        		return;
	        	}
	        	finalnum++;
	        }
	       
