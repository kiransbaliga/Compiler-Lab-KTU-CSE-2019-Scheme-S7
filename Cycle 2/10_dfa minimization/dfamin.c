#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

char states[100],terms[100],stack[50];
int ind=0,stacklen=0;
char grams[20];
int count=0,rescount=0,resind=0;
int sn=0,tn=0;

int eqtab[30][30];
bool isfinal[40],resfinal[40];

char restab[30][30];

char table[50][50];
char hasEps[100];
int eind=0;

char eclsr[50];
int clsind=0;

char sstr[30];
int sortString()
{
	int l=strlen(sstr);
	for(int i=0;i<l;i++)
	{
		for(int j=0;j<l-1-i;j++)
		{
			if(sstr[j]>sstr[j+1])
			{
				char tem=sstr[j];
				sstr[j]=sstr[j+1];
				sstr[j+1]=tem;
			}
		}
	}
}

int main()
{
	printf("Input the number of states:-\n");
	scanf("%d",&sn);
	printf("Input the number of terminals:-\n");
	scanf("%d",&tn);
	getchar();

	printf("Input the %d states:-\n",sn);
	for(int i=0;i<sn;i++)
	{
		states[i]=getchar();
		getchar();
		
	}
	printf("Input the %d terminals:-\n",tn);
	for(int i=0;i<tn;i++)
	{
		terms[i]=getchar();
		getchar();
	}
	printf("Input the transition table:-\n");

	for(int i=0;i<tn;i++)
	{
		printf("\t%c",terms[i]);
	}
	printf("\tIs Final? (y/n)\n");
	for(int i=0;i<sn;i++)
	{
		printf("%c\t",states[i]);
		for(int j=0;j<tn+1;j++)
		{
			table[i][j]=getchar();
			getchar();
			if(j==tn)
			{
				if(table[i][j]=='y')
				{
				isfinal[i]=1;
				}
				else
				isfinal[i]=0;
			}
		}
	}
	for(int i=0;i<sn;i++)
	{
		for(int j=0;j<sn;j++)
		{
			if(isfinal[i]!=isfinal[j])
			eqtab[i][j]=0;
			else if(i==j)
			eqtab[i][j]=1;
			else
			eqtab[i][j]=2; /// BLANK VALUE
		}
	}
	bool haschanged=false;
	bool complete=false;
	while(!complete)
	{
		haschanged=false;
		complete=true;
		for(int i=0;i<sn;i++)
		{
			for(int j=0;j<sn;j++)
			{
				if(eqtab[i][j]!=2)
				{
					continue;
				}
				complete=false;
				int issame=1;
				for(int k=0;k<tn;k++)
				{
					int ind1,ind2;
					for(int l=0;l<sn;l++)
					{
						if(table[i][k]==states[l])
						{
							ind1=l;
						}
						if(table[j][k]==states[l])
						{
							ind2=l;
						}
					}
					if(eqtab[ind1][ind2]==0)
					{
						issame=0;
						break;
					}
					else if(eqtab[ind1][ind2]==2)
					{
						issame=2;//blank
					}
				}
				if(issame==1)
				{
					eqtab[i][j]=1;
					eqtab[j][i]=1;
					haschanged=true;
				}
				else if(issame==0)
				{
					eqtab[i][j]=0;
					eqtab[j][i]=0;
					haschanged=true;
				}
			}
		}
		if(!haschanged)
		{
			for(int i=0;i<sn;i++)
			{
				for(int j=0;j<sn;j++)
				{
					if(eqtab[i][j]==2)
					{	
						eqtab[i][j]=1;
					}
				}
			}
		}
	}
	int teams[40];
	int curteam=0;
	for(int i=0;i<sn;i++)
	teams[i]=-1;
	for(int i=0;i<sn;i++)
	{
		if(teams[i]!=-1)
			continue;
		teams[i]=curteam;
		curteam++;
		for(int j=0;j<sn;j++)
		{
			if(eqtab[i][j]==1)
			{
				teams[j]=teams[i];
			}
		}
	}
	for(int i=0;i<sn;i++)
	{
		resfinal[teams[i]]=isfinal[i];
		for(int j=0;j<tn;j++)
		{
			for(int k=0;k<sn;k++)
			{
				if(states[k]==table[i][j])
				{
					restab[teams[i]][j]=teams[k];
				}
			}
		}		
	}
	printf("Minimized DFA\n");
	for(int i=0;i<tn;i++)
	{
		printf("\t%c",terms[i]);
	}
	printf("\tIs Final? (y/n)\n");
	for(int i=0;i<curteam;i++)
	{
		printf("%c\t",('A'+i));
		for(int j=0;j<tn+1;j++)
		{
			if(j==tn)
			{
				if(resfinal[i])
				{
					printf("Y\n");
				}
				else
					printf("N\n");
			}
			else
			{
				printf("%c\t",('A'+restab[i][j]));
			}
		}
	}
	printf("\n");
}
