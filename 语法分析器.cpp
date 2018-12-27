# include <iostream>
# include <ctype.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
using namespace std; 
char *keyword[8]= {"if", "for", "else", "while", "do", "float","int", "break"};
char keywordtable[20][20], re_keywordtable[20][20];  //存放保留字
char digittable[20][20], re_digittable[ 20][20];  //存放数字
char otherchartable[20][20], re_otherchartable[20][20];  //存放其他字符
char idtable[20][20],re_idtable[20][20];//存放标识符
char notetable[20][20];  //存放注释
char finaltable[100][20];  //存放终结符
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
int flag_error=0;                //0表示没有错误，1表示有错误 
int flagerror=0;
char lookahead;
int main ()
{
	printf("请输入要分析的语句:\n");
	initialize();
	while(1)
	{
		lookahead=getchar();    //从标准输入流中读一个字符 
		if(isalpha(lookahead))   //用来判断字符lookahead是否为英文字母
		                         //a-z或A-Z时返回非0值（不一定是1）， 否则返回0
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
				ungetc(lookahead,stdin);  //把一个字符退回到输入流中
				                          //Lookahead是写入的字符，stdin是文件流指针
				strcpy(finaltable[final_num],"/");    //将"/"放到终结符号表中 
				strcpy(otherchartable[otherchar_num++],"/")	;  //将"/"放到其他符号表中
				finaltableint[final_num++]=2;                  //"/"的序号是2 
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
			    printf("语法分析完成！\n");
		}
	 } 
	 void alpha()
	 {
	 	int i=1,flag;
	 	char ch;
	 	ch=lookahead;
	 	word[0]=ch;
	 	ch=getchar();
	 	while(isalpha(ch)||isdigit(ch))    //将标识符放到word数组中 
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
		 if(flag==1)                       //是保留字 
		 {
		 	strcpy(keywordtable[keyword_num++],word);   //将保留字复制到保留字表中 
		 	strcpy(finaltable[final_num],word);         // 保留字复制到终结符表中 
		 	if(strcmp(word,"if")==0)
		 	    finaltableint[final_num++]==100;        //if终结符的序号为100 
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
		 else                                           //不是保留字，是标识符 
		 {
		 	strcpy(idtable[id_num++],word);             //把标识符复制到标识符表中 
		 	strcpy(finaltable[final_num],"id");         //终结符号表中存放id 
		 	finaltableint[final_num++]=1;               //标识符的序号为1 
		 }
	 }
	 void initialize()                 //初始化及清空数组 
	 {
	 	int i;
	 	for(i=0;i<20;i++)
	 	{
	 		word[i]='\0';
		 }
	  } 
	 void digit()                    //将数字开头的串放到word数组中
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
		 if(flag==1)      //如果有一个字符不是数字，则将该字符串放在标识符数组中
		 {
		 	strcpy(idtable[id_num++],word);          
		 	strcpy(finaltable[final_num],"id");          
		 	finaltableint[final_num++]=1;
		  } 
		  else           //如果都是数字，则将它放到数字串数组中
		  {
		  		strcpy(digittable[digit_num++],word);          
		 	strcpy(finaltable[final_num],"num");          
		 	finaltableint[final_num++]=99;        //数字的序号是99 
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
	  				if(ch=='/')            //是/*.......*/直接跳出循环
					  break;               //是/*.......*/的情况 
				    else
				    {
				    	ungetc(ch,stdin);
				    	word[i++]=ch;
					}
				  }
				  else                      //是/*.......*/的情况 
				  {
				  	word[i++]=ch;           //word数组存放注释的内容 
				   } 
				   ch=getchar(); 
		 }
			  strcpy(notetable[note_num++],word);    //将注释的内容存放到注释表中 
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
		                   	finaltableint[final_num++]=3;      //"!="的序号是3 
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
		                   	finaltableint[final_num++]=4;      //"=="的序号是4
						  }
						  else
						  {
						    strcpy(otherchartable[otherchar_num++],"=");          
		 	                strcpy(finaltable[final_num],"=");          
		                   	finaltableint[final_num++]=5;      //"="的序号是5
		                   	ungetc(ch,stdin);
						   } 
					  }
					  break;
					  
						case '(':
		  				    strcpy(otherchartable[otherchar_num++],"(");          
		 	                strcpy(finaltable[final_num],"(");         
		                   	finaltableint[final_num++]=6;      //"("的序号是6
						    break;
						     
			        	case ')':
		  				    strcpy(otherchartable[otherchar_num++],")");          
		 	                strcpy(finaltable[final_num],")");         
		                   	finaltableint[final_num++]=7;      //")"的序号是7
						    break;
						    
						case ';':
		  				    strcpy(otherchartable[otherchar_num++],";");          
		 	                strcpy(finaltable[final_num],";");         
		                   	finaltableint[final_num++]=8;      //";"的序号是8
						    break;
						    
						case '{':
		  				    strcpy(otherchartable[otherchar_num++],"{");          
		 	                strcpy(finaltable[final_num],"{");         
		                   	finaltableint[final_num++]=9;      //"{"的序号是9
						    break;
						    
						case '}':
		  				    strcpy(otherchartable[otherchar_num++],"}");          
		 	                strcpy(finaltable[final_num],"}");         
		                   	finaltableint[final_num++]=10;      //"}"的序号是10
						    break;
						    
						case '||':
		  				    strcpy(otherchartable[otherchar_num++],"||");          
		 	                strcpy(finaltable[final_num],"||");         
		                   	finaltableint[final_num++]=11;      //"||"的序号是11
						    break;
						    
						case '&&':
		  				    strcpy(otherchartable[otherchar_num++],"&&");          
		 	                strcpy(finaltable[final_num],"&&");         
		                   	finaltableint[final_num++]=12;      //"&&"的序号是12
						    break;
						    
						case '+':
		  				    strcpy(otherchartable[otherchar_num++],"+");          
		 	                strcpy(finaltable[final_num],"+");         
		                   	finaltableint[final_num++]=13;      //"+"的序号是13
						    break;
						    
						case '-':
		  				    strcpy(otherchartable[otherchar_num++],"-");          
		 	                strcpy(finaltable[final_num],"-");         
		                   	finaltableint[final_num++]=19;      //"-"的序号是19
						    break;
						    
						case '>':
		  		     	{
		  				ch=getchar();
		  				if(ch=='=')
		  				{
		  				    strcpy(otherchartable[otherchar_num++],">=");          
		 	                strcpy(finaltable[final_num],">=");         
		                   	finaltableint[final_num++]=14;      //">="的序号是14
						  }
						  else
						  {
						      strcpy(otherchartable[otherchar_num++],">");          
		 	                strcpy(finaltable[final_num],">");          
		                   	finaltableint[final_num++]=15;      //">"的序号是15
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
		                   	finaltableint[final_num++]=16;      //"<="的序号是16
						  }
						  else
						  {
						      strcpy(otherchartable[otherchar_num++],"<");          
		 	                strcpy(finaltable[final_num],"<");          
		                   	finaltableint[final_num++]=17;      //"<"的序号是17
		                   	ungetc(ch,stdin);
						   } 
					    }
					    break;
					    
				     	case '*':     
		 	                strcpy(finaltable[final_num],"*");         
		                   	finaltableint[final_num++]=18;      //"*"的序号是18
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
		  	printf("出现错误，中止分析！\n");
		  	
		  }
		  void print()
		  {
		  	int i;
		  	finaltableint[final_num]='\0';
		  	printf("词法分析结果如下:\n");
		  	for(i=0;i<final_num;i++)
		  	    printf("%s",finaltable[i]);
		  	printf("\n语法分析过程如下：\n");
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
			if(finaltableint[finalnum]==10)     //第二个符号是"}"
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
	       
