#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>

char s[100], post[100], stack[100], queue[100];
int top = -1, j = 0, front = -1;

int precedence(char c){
	if(c == '+' || c == '-'){
		return 1;
	}
	else if(c == '*' || c == '/'){
		return 2;
	}
	else if(c == '^'){
		return 3;
	}
	else{
		return 0;
	}
}

void postfix(){
	int n = strlen(s), i = 0;
	while(s[i] != '\0'){
		if(s[i] == '('){
			top++;
			stack[top] = s[i];
		}
		else if(isalpha(s[i])){
			post[j++] = s[i];
		}
		else if(precedence(s[i])){
			while(precedence(stack[top]) > precedence(s[i])){
				post[j++] = stack[top--];
			}
			top++;
			stack[top] = s[i];
		}
		else if(s[i] == ')'){
			while(stack[top] != '('){
				post[j++] = stack[top--];
			}
			top--;
		}
		i++;
	}
	while(top!=-1){
		post[j++] = stack[top--];
	}
	post[j] = '\0';
}

void main(){
	int i = 0;
	char ind = '1';
	
	FILE *fp,*fp1,*fp2;
	fp = fopen( "3addr.txt","w");
	fp1 = fopen( "quadraple.txt","w");
	fp2 = fopen( "triple.txt","w");
	fprintf(fp,"Three Address\n");
	fprintf(fp1,"Quadruple\nOP\tO1\tO2\tRES\n");
	fprintf(fp2,"Triple\nIN\tOP\tO1\tO2\n");
	
	printf("Input the string: ");
	scanf("%s", s);
	
	postfix();
	
	printf("Infix : %s \nPostfix : %s\n", s, post);

	while(post[i] != '\0'){
		if(precedence(post[i])){
			char a = queue[front--];
			char b = queue[front--];
			if(isdigit(a) && isdigit(b)){
				fprintf(fp,"t%c = t%c %c t%c\n", ind, b, post[i], a);
				fprintf(fp1,"%c\tt%c\tt%c\tt%c\n", post[i], b, a, ind);
			}
			else if(isdigit(b)){
				fprintf(fp,"t%c = t%c %c %c\n", ind, b, post[i], a);
				fprintf(fp1,"%c\tt%c\t%c\tt%c\n", post[i], b, a, ind);
			}
			else if(isdigit(a)){
				fprintf(fp,"t%c = %c %c t%c\n", ind, b, post[i], a);
				fprintf(fp1,"%c\t%c\tt%c\tt%c\n", post[i], b, a, ind);
			}
			else{
				fprintf(fp,"t%c = %c %c %c\n", ind, b, post[i], a);
				fprintf(fp1,"%c\t%c\t%c\tt%c\n", post[i], b, a, ind);
			}
			fprintf(fp2,"%c\t%c\t%c\t%c\n", ind, post[i], b, a);
			front++;
			queue[front] = ind;
			ind++;
		}
		else{
			front++;
			queue[front] = post[i];
		}
		i++;
	}
}
