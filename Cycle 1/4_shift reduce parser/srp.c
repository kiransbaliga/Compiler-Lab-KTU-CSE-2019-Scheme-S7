#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct prodn{
    char p1[10];
    char p2[10];
};

void main(){
    char input[20], input2[20], stack[50], temp[50], ch[2], *t1, *t2, *t;
    int i, j, s1, s2, s, count = 0;
    struct prodn p[10];
    FILE *fp;
    fp = fopen("input.txt", "r");
    stack[0] = '\0';
    printf("\nEnter the input string\n");
    scanf("%s", input);
    strcpy(input2, input);
    while (!feof(fp)){
        fscanf(fp, "%s\n", temp);
        t1 = strtok(temp, "=");
        t2 = strtok(NULL, "=");
        strcpy(p[count].p1, t1);
        strcpy(p[count].p2, t2);
        count++;
    }
    i = 0;
    printf("\n\n|STACK| \t |INPUT| \t |ACTION|\n\n");
    printf("$\t %s$ \t\n", input2);
    while (1){
        if (i < strlen(input)){
            ch[0] = input[i];
            ch[1] = '\0';
            input2[i] = ' ';
            i++;
            strcat(stack, ch);
            printf("$%s\t%s$\t Shift\n", stack, input2);
        }
        for (j = 0; j < count; j++){
            t = strstr(stack, p[j].p2);
            if (t != NULL){
                s1 = strlen(stack);
                s2 = strlen(t);
                s = s1 - s2;
                stack[s] = '\0';
                strcat(stack, p[j].p1);
                printf("$%s\t%s$\t Reduce : %s->%s\n", stack, input2, p[j].p1, p[j].p2);
                j = -1;
            }
        }
        if (strcmp(stack, "S") == 0 && i == strlen(input)){
            printf("\n%s is accepted\n",input);
            break;
        }

        if (i == strlen(input)){
            printf("\n%s is not accepted\n",input);
            break;
        }
    }
}
