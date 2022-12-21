	int words=0,chars=0,lines=0;

%%
[:space:]	++words;++chars;
\n		++lines;
.		++chars;
%%

int main()
{
	yyin = fopen("text.txt","r");
	yylex();
	printf("# of words = %d\n",words);
	printf("# of characters = %d\n",chars);
	printf("# of lines = %d\n",lines);
	
}
