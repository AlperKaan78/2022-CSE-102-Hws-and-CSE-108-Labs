#include<stdio.h>
#include<stdlib.h>

typedef struct ExamPaper
{
    char studentName[30];
    int studentNumber,score;
    struct ExamPaper *next;

}ExamPaper;

void my_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

ExamPaper* push(ExamPaper* stack, char* studentName, int studentNumber, int score)
{
    ExamPaper* n, * l;
    l = stack;

    printf("Push operation:\n");
    printf("Exam Paper Added: Student Name: %s, Student Number: %d, Score: %d \n", studentName, studentNumber, score);

    n = (ExamPaper*)malloc(sizeof(ExamPaper));

    my_strcpy(n->studentName, studentName);
    n->studentNumber = studentNumber;
    n->score = score;

    if (stack == NULL)
    {
        stack = n; 
    }
    else {
        while (l->next != NULL)
        {
            l = l->next;
        }
        l->next = n;
        n->next = NULL;
    }

    return stack;
}



ExamPaper* pop(ExamPaper* stack)
{
    ExamPaper* current = stack;
    ExamPaper* previous = NULL;


    printf("Pop operation:\n");

    if (stack == NULL)
    {
        return NULL;
    }

    if (current->next == NULL)
    {
        free(current);
        return NULL;
    }

    while (current->next != NULL)
    {
        previous = current;
        current = current->next;
    }

    free(current);

    previous->next = NULL;

    return stack;
}

int isEmpty(ExamPaper * stack)
{
    if(stack == NULL)
    {
        printf("The stack is empty.\n");
        return 1;
    }
    else{
        printf("The stack is not empty.\n");
        return 0;
    }
}

void display(ExamPaper * stack)
{
    ExamPaper *m;
    m=stack;
    printf("Exam Papers in the Stack: \n");
    while(m != NULL)
    {
        printf("Name: %s, Number: %d, Score: %d \n",m->studentName,m->studentNumber,m->score);
        m=m->next;
    }
}

int main()
{
    ExamPaper *stack =NULL;
    stack = push(stack,"Alper Kaan",25154152,50);
    stack = push(stack,"Ahmet",4518464,70);
    stack = push(stack,"Leyla",1465465,75);
    stack = push(stack,"Ayse",1415779,60);
    stack = push(stack,"Onur",1985779,20);

    display(stack);

    stack = pop(stack);
    display(stack);
    
    int empty = isEmpty(stack);
    
}