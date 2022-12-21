#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>


char buf[30];
void showError(int ln,char buffer[], char c, int code){
printf("Error at Line Number %d in the lexeme %s%c\nTerminating Program! Error Code: %d\n",ln,buffer,c,code);
exit(0);
}

char* toString(int a)
{
int l=0;
while(a>0)
{
	char c='0'+(a%10);
	a=a/10;
	buf[l]=c;
	l++;
}

for(int i=0;i<l/2;i++)
{
	char c=buf[i];
	buf[i]=buf[l-1-i];
	buf[l-1-i]=c;
}
}



int main()
{

char symbols[100][2][20]={
	
};

int symbc=0;
char keywords[40][20]={
	"void","int","char","exit","for","while","return","if","else","main","printf"
};
char dtypes[40][20]={"int","char","float"};


FILE *fp,*symtab,*fp2,*fp3;
fp = fopen( "inp.txt","r");
fp2=fopen("con.txt","w");
fp3 = fopen( "con.txt","r");
symtab = fopen( "result.txt","w");
if(fp==NULL)
{
  	printf("File could not be opened!\n");
  	exit(0);
}	
if(symtab==NULL)
{
  	printf("Result File could not be opened!\n");
  	exit(0);
}
char buffer[30],idf[30],idf2[30];
char idstack[30][20],opstack[30];
int idtop=0,optop=0;
int ln=1;
bool isd=false;
bool expecting=false;
bool isStringLiteral=false;
bool defining=false;
int sp=0,cp=0,bp=0;
char c=fgetc(fp);
while(!feof(fp))
{
	if(isStringLiteral && c!='"')
	{
		
		fprintf(symtab,"%c",c); 
		c=fgetc(fp);
		continue;
	}
	else if(!isStringLiteral && !isalnum(c)&&c!='_'&&bp!=0)
	{
 		buffer[bp]='\0';
 		bool isk=false;
 		for(int i=0;i<40;i++)
 		{
 			if(strcmp(keywords[i],buffer)==0)
 			{
 				isk=true;
 				break;
 			}
 		}
 		for(int i=0;i<40;i++)
 		{
 			if(strcmp(dtypes[i],buffer)==0)
 			{
 				defining=true;
 				break;
 			}
 		}
 		if(!isk&&isd)
 		{
 			strcpy(idstack[idtop],buffer);
 			idtop++;
 		}
 		else if(!isk)
 		{
 			strcpy(idstack[idtop],buffer);
 			idtop++;
 			strcpy(idf,buffer);
 			bool flag=false;
 			if(!expecting)
 			{
 			if(c!='=')
 			{for(int i=0;i<symbc;i++)
					{
						if(strcmp(symbols[i][0],idf)==0)
						{
							fprintf(symtab,"%s",symbols[i][1]);
							flag=true;
							break;
						}
					}}
					if(flag==false)
					fprintf(symtab,"%s",buffer); 
			}
 		}
 		else
 		{
 			
		       fprintf(symtab,"%s",buffer); 
 		}
 		bp=0;
 		buffer[bp]='\0';
 		isd=false;
	}
	if(c=='"')
	{	
		if(isStringLiteral)
			{
		buffer[bp]='\0';
		
			}
		isStringLiteral=!isStringLiteral;
		
		fprintf(symtab,"%c",c); 
		c=fgetc(fp);
		continue;
	}
	else if(c=='+'||c=='-'||c=='*'||c=='/') 
	{
 		
		if(optop>0)
		{
			if((opstack[optop-1]=='*'||opstack[optop-1]=='/')&&(c=='+'||c=='-'))
			{
			        if(idtop<2)
				{
					showError(ln,buffer,c,1);
				}
				idtop--;
				char operand[30];
				strcpy(operand,idstack[idtop]);
				
				float op1=0,op2=0;
				if(isdigit(operand[0]))
				{
					op1=atof(operand);
				}
				else
				{
					int i=0;
					for(i=0;i<symbc;i++)
					{
						if(strcmp(symbols[i][0],operand)==0)
						{
							op1=atof(symbols[i][1]);
							break;
						}
					}
					if(i==symbc)
					{
						showError(ln,buffer,c,2);
					}
				}
				
				idtop--;
				strcpy(operand,idstack[idtop]);
				
				if(isdigit(operand[0]))
				{
					op2=atof(operand);
				}
				else
				{
					int i=0;
					for(i=0;i<symbc;i++)
					{
						if(strcmp(symbols[i][0],operand)==0)
						{
							op2=atof(symbols[i][1]);
							break;
						}
					}
					if(i==symbc)
					{
						showError(ln,buffer,c,3);
					}
				}
				float ans=0;
				if(opstack[optop-1]=='*')
				{
					ans=op1*op2;
				}
				else if(opstack[optop-1]=='/')
				{
					ans=op2/op1;
				}
				
				fp2=fopen("con.txt","w");
				fprintf(fp2,"%f\n",ans);
				fclose(fp2);
				fgets(buf,30,fp3);
				
				strcpy(idstack[idtop],buf) ;
				idtop++;
				optop--;
			}
		}
		opstack[optop]=c;
 		optop++;
	}
	else if(isalpha(c))
	{
		if(isd)
		{
			showError(ln,buffer,c,4);
		}
		buffer[bp]=c;
		bp++; 
		if(bp==1)
		{
			isd=false;
		}
	}
	else if(isdigit(c))
	{
                
		buffer[bp]=c;
		bp++;
		if(bp==1)
		{
			isd=true;
		}
	}
	else if(c=='_')
	{
		if(bp!=0)
		{
			buffer[bp]=c;
			bp++;
		}
		else
		{
			showError(ln,buffer,c,5);
		}
	}
	else if(c=='<'||c=='>'||c=='='||c=='!'){
	
		fprintf(symtab,"%c",c); 
		char c2=fgetc(fp);
		if(c2!='='&&c=='!')
		{
			showError(ln,buffer,c,6);
			c=c2;
			continue;
		}
		else if(c!='=')
		{
			c=c2;
 			expecting =true;
 			continue;
		}
		else 
		{
			c=c2;
 			idtop=0;
 			
 			strcpy(idf2,idf);
 			expecting=true;
 			continue;
		}
	}
	else if(c==';'||c==',')
	{
		if(expecting)
		{
		while(idtop>1)
		{
		 	
				idtop--;
				char operand[30];
				
				strcpy(operand,idstack[idtop]);
				
				float op1=0,op2=0;
				if(isdigit(operand[0]))
				{
					op1=atoi(operand);
				}
				else
				{
					int i=0;
					for(i=0;i<symbc;i++)
					{
						if(strcmp(symbols[i][0],operand)==0)
						{
							if(strcmp(symbols[i][1],"-")==0)
								op1=0;
							else
								op1=atof(symbols[i][1]);
							break;
						}
					}
					if(i==symbc)
					{
						showError(ln,buffer,c,7);
					}
				}
				idtop--;
				strcpy(operand,idstack[idtop]);
				
				if(isdigit(operand[0]))
				{
					op2=atoi(operand);
				}
				else
				{
					int i=0;
					for(i=0;i<symbc;i++)
					{
						if(strcmp(symbols[i][0],operand)==0)
						{	if(strcmp(symbols[i][1],"-")==0)
								op1=0;
							else
							op2=atof(symbols[i][1]);
							break;
						}
					}
					if(i==symbc)
					{
						showError(ln,buffer,c,8);
					}
				}
				float ans=0;
				if(opstack[optop-1]=='*')
				{
					ans=op1*op2;
				}
				else if(opstack[optop-1]=='/')
				{
					ans=op2/op1;
				}
				else if(opstack[optop-1]=='+')
				{
					ans=op1+op2;
				}
				else if(opstack[optop-1]=='-')
				{
					ans=op2-op1;
				}
				fp2=fopen("con.txt","w");
				fprintf(fp2,"%f",ans);
				fclose(fp2);
				fp3 = fopen( "con.txt","r");
				fgets(buf,30,fp3);
				fclose(fp3);
				
				strcpy(idstack[idtop],buf) ;
				idtop++;
				optop--;
		}
		int targetInd=symbc;
		if(!defining)
		{
		int j=0;
			for(j=0;j<symbc;j++)
					{
					if(strcmp(symbols[j][0],idf2)==0)
					{
					targetInd=j;
					break;
					}
					}
		}
		strcpy(symbols[targetInd][0],idf2);
		if(isalpha(idstack[0][0]))
		{
			
		
			int i=0;
					if(strcmp(symbols[targetInd][0],idf2)==0)
					{
					for(i=0;i<symbc;i++)
					{
					
						
						if(strcmp(symbols[i][0],idstack[0])==0)
						{
							
							strcpy(symbols[targetInd][1],symbols[i][1]);
							break;
						}
						
					}
					if(i==symbc)
					{
						showError(ln,buffer,c,12);
					}
					}
					
					
		}
		else
		{
			int j=0;
			
			strcpy(symbols[targetInd][1],idstack[0]);
					
							
		}
		
		
		if(defining)
		{symbc++;
		}
		
		if(c==';')
		defining=false;
		
		fprintf(symtab,"%s",symbols[targetInd][1]);
		}
		else if(defining)
		{
		strcpy(symbols[symbc][0],idf);
		strcpy(symbols[symbc][1],"0");
		symbc++;
		if(c==';')
		defining=false;
		}
		expecting=false;
		
		fprintf(symtab,"%c",c); 
	}
	else if(c=='{'||c=='}'||c=='('||c==')'||c=='['||c==']')
	{
		fprintf(symtab,"%c",c); 
	}
	else if(c=='\n')
	{
		fprintf(symtab,"%c",c); 
	}
	
	else if(c!=' '&&c!='\t')

	{
		showError(ln,buffer,c,10);
	}
	else
	{
	
		fprintf(symtab,"%c",c); 
	}
	c=fgetc(fp);
}

fclose(symtab);
fclose(fp);
return 0;
}

/*
float pi=22/7;

void main()
{

float c;

c=2*pi;
}
*/

