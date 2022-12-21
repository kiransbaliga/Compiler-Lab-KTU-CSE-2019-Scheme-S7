#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

int fincheck[100],ind=0,stckn=0,clsind=0,count=0,sn=0,tn=0,eind=0;
char states[100],terms[100],stack[50],grams[20],rhs[20][50],table[50][50][10],hasEps[100],epsi[50];

int Epsilon_Closure(char c)
{
for(int i=0;i<sn;i++)
{
	if(states[i]==c)
	{
		if(strcmp(table[i][tn],"-")!=0)
		{
			strcat(epsi,table[i][tn]);
			clsind+=strlen(table[i][tn]);
			for(int j=0;j<strlen(table[i][tn]);j++)
				Epsilon_Closure(table[i][tn][j]);
		}
		break;
	}
}
return 0;
}

int main()
{
	printf("\nEnter the number of States :\n");
	scanf("%d",&sn);
	printf("\nEnter the number of Terminals :\n");
	scanf("%d",&tn);
	getchar();
	printf("\nEnter the %d States:\n",sn);
	for(int i=0;i<sn;i++)
	{
		states[i]=getchar();
		getchar();
	}
	printf("\nEnter the %d Terminals:\n",tn);
	for(int i=0;i<tn;i++)
	{
		terms[i]=getchar();
		getchar();
	}
	printf("\nEnter the Table:\n\n");
	for(int i=0;i<tn;i++)
		printf("\t%c",terms[i]);
	printf("\tepsln\tIs Final? (y/n)\n");
	for(int i=0;i<sn;i++)
	{
		printf("%c\t",states[i]);
		for(int j=0;j<tn+2;j++)
		{
			scanf("%s",table[i][j]);
			if(j==tn&&strcmp(table[i][j],"-")!=0)
			{
				hasEps[eind]=states[i];
				eind++;
			}
			if(j==tn+1)
			{
				if(strcmp(table[i][j],"y")==0)
					fincheck[i]=1;
				else
					fincheck[i]=0;
			}
		}
	}
	for(int i=0;i<eind;i++)
	{
	epsi[0]='\0';
	clsind=0;
	Epsilon_Closure(hasEps[i]);
	for(int j=0;j<sn;j++){
		for(int k=0;k<tn;k++){
			for(int l=0;l<strlen(table[j][k]);l++){
				if(table[j][k][l]==hasEps[i]){
					for(int p=0;p<clsind;p++){
						int flag=1;
						for(int o=0;o<strlen(table[j][k]);o++){
							if(table[j][k][o]==epsi[p]){
								flag=0;
								break;
							}
						}
						if(flag)
							table[j][k][strlen(table[j][k])]=epsi[p];
					}
					break;
				}
			}
		}
	}
	int thisind=0,fin=0;
	for(int k=0;k<sn;k++){
		for(int l=0;l<clsind;l++){
			for(int p=0;p<sn;p++){
				if(states[p]==epsi[l]&&fincheck[p]==1){
					fin=1;
					break;
				}
			}
			if(fin==1)
				break;
		}
		if(states[k]==hasEps[i])
			thisind=k;
	}
	for(int j=0;j<clsind;j++){
		for(int k=0;k<sn;k++){
			if(epsi[j]==states[k]){
				for(int l=0;l<tn;l++){
					for(int o=0;o<strlen(table[k][l]);o++){
						int ffll=0;
						for(int p=0;p<strlen(table[thisind][l]);p++){
							if(table[thisind][l][o]==table[k][l][p]){
								ffll=1;
								break;
							}
						}
						if(ffll==0){
							if(table[thisind][l][0]=='-')
								table[thisind][l][0]=table[k][l][o];
							else
								table[thisind][l][strlen(table[thisind][l])]=table[k][l][o];
						}
					}
				}
			}
		}
	}
	fincheck[thisind]=fin|fincheck[thisind];
	}
	printf("\nThe Epsilon free NFA is :\n\n");
	for(int i=0;i<tn;i++)
		printf("\t%c",terms[i]);
	printf("\tIs Final?\n");
	for(int i=0;i<sn;i++){
		printf("%c\t",states[i]);
		for(int j=0;j<tn+1;j++){
			if(j==tn){
				if(fincheck[i])
					printf("Yes\n");
				else
					printf("No\n");
			}
			else
				printf("%s\t",table[i][j]);
		}
	}
	printf("\n");
}

