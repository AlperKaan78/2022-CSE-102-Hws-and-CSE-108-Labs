#include<stdio.h>
#include<stdlib.h>
#include "util.h"


void add_ftree()
{
    Node *root = NULL;

    char selection;

    while(selection != '3')
    {
        printf("1-Add Node\n2-Save family tree.\n3-Exit.\n");
        scanf(" %c",&selection);
        switch (selection)
        {
        case '1':add_node(&root); break;
        case '2':break;
        case '3':break;
        
        default:
            break;
        }
    }
}

void add_node(Node **root)
{
    Node *tmp = *root;
    Node *new;
    new = (Node*)malloc(sizeof(Node));

    if(tmp = NULL)
    {
        new->father = NULL;
        new->mother = NULL;
        printf("Please enter the name of the person:");scanf(" %[^\n]",new->name);
        printf("Please enter the age of the person: ");scanf(" %d",&new->age);
    }
}

void save_ftree()
{
    
}

Node* remove_ftree()
{

}

void load_ftree()
{

}