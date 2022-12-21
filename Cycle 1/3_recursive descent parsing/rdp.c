#include<stdio.h>
#include<string.h>
#include<ctype.h>

char input[10];
int i, err;

void E() {
	T();
	Eprime();
}

void Eprime() {
	if (input[i] == '+') {
    		i++;
    		T();
    		Eprime();
  	}
}

void T() {
  F();
  Tprime();
}

void Tprime() {
  if (input[i] == '*') {
    i++;
    F();
    Tprime();
  }
}

void F() {
  if (isalnum(input[i])) 
  	i++;
  else if (input[i] == '(') {
    i++;
    E();
    if (input[i] == ')')
      i++;
    else err = 1;
  } 
  else err = 1;
}

void main() {
	i = 0;
	err = 0;
	printf("Enter an expression : ");
	gets(input);
	E();
	if (strlen(input) == i && err == 0)
		printf("%s is accepted\n",input);
	else
		printf("%s is rejected\n",input);
}


