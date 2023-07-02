#ifndef _UTIL_H
#define _UTIL_H

typedef struct Node
{
    char name[20];
    int age;
    struct Node *mother;
    struct Node *father;
}Node;

void add_ftree();

void remove_ftree(Node **root);

void load_ftree();

void add_node(Node **root);

void save_ftree();




#endif