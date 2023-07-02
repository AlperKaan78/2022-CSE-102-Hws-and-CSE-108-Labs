#include<stdio.h>
#include<stdlib.h>
#include "util.h"
#include<time.h>
#include<string.h>

int main()
{
    srand(time(NULL)); /* seed operation for random function.*/

    Node *head = NULL;
    fillLinkedList(&head);
    printll(head);
    serializeLinkedList(head);

    Node *new_head = NULL;
    deserializeLinkedList(&new_head);
    printll(new_head);

    free_ll(&head);
    free_ll(&new_head);
    return 0;
}

/* According to type of the data variable in the Nodes, datas will be printed.*/
void printll(Node* head) {
    Node* tmp = head;
    while (tmp != NULL) {
        if (strcmp(((Asset1*)tmp->data)->type, "asset1") == 0) {
            Asset1* asset = (Asset1*)tmp->data;
            printf("Asset1: ivals[0] = %d, svals[0] = %lf\n", asset->ivals[0], asset->svals[0]);
        }
        else if (strcmp(((Asset2*)tmp->data)->type, "asset2") == 0) {
            Asset2* asset = (Asset2*)tmp->data;
            printf("Asset2: ivals[0] = %d, ivals[1] = %d, svals[0] = %lf, svals[1] = %lf\n",
                    asset->ivals[0], asset->ivals[1], asset->svals[0], asset->svals[1]);
        }
        else if (strcmp(((Asset3*)tmp->data)->type, "asset3") == 0) {
            Asset3* asset = (Asset3*)tmp->data;
            printf("Asset3: string1 = %s, string2 = %s\n", asset->string1, asset->string2);
        }
        else if (strcmp(((Asset4*)tmp->data)->type, "asset4") == 0) {
            Asset4* asset = (Asset4*)tmp->data;
            printf("Asset4: value1 = %lf, value2 = %f, value3 = %lf\n",
                    asset->value1, asset->value2, asset->value3);
        }
        
        tmp = tmp->next;
    }
}
/* After all the operations memory for the head nodes must be deallocated.*/
void free_ll(Node** head)
{
    Node* current = *head;
    Node* next;

    while (current != NULL)
    {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    *head = NULL; 
}


/* New Nodes will be generated in this function and number of Nodes is determined randomly in this function.
    Each loop new Node memory is allocated for the it. Since the data is void type, each type of asset can be assigned
    it new pointer's data variable. All the variables in the Asset(1,2,3,4) are generated randomly. */
void fillLinkedList(Node **head)
{
    int number_of_assets = rand()%10 +11;
    int counter = 1;


    while(counter++<=number_of_assets)
    {
        Node *new;
        new = (Node*)malloc(sizeof(Node));
        new->next = NULL;
        int asset_type = rand()%4 + 1;

        if(asset_type == 1)
        {
            Asset1 *new_asset1;
            new_asset1 = (Asset1*)malloc(sizeof(Asset1));
            strcpy(new_asset1->type, "asset1");
            new_asset1->ivals[0] = rand()%20;
            new_asset1->svals[0] = (double)rand() / RAND_MAX;
            new->data = new_asset1;     
        }
        else if(asset_type == 2)
        {
            Asset2 *new_asset2;
            new_asset2 = (Asset2*)malloc(sizeof(Asset2));
            strcpy(new_asset2->type, "asset2");
            new_asset2->ivals[0] = rand()%20;
            new_asset2->ivals[1] = rand()%20;
            new_asset2->svals[0] = (double)rand() / RAND_MAX;
            new_asset2->svals[1] = (double)rand() / RAND_MAX;
            new->data = new_asset2;
        }
        else if(asset_type == 3)
        {
            Asset3 *new_asset3;
            new_asset3 = (Asset3*)malloc(sizeof(Asset3));
            strcpy(new_asset3->type, "asset3");
            fill_string(new_asset3->string1, 50);
            fill_string(new_asset3->string2, 50);
            new->data = new_asset3;            
        }
        else if(asset_type == 4)
        {
            Asset4 *new_asset4;
            new_asset4 = (Asset4*)malloc(sizeof(Asset4));
            strcpy(new_asset4->type, "asset4");
            new_asset4->value1 = (double)rand() / RAND_MAX;
            new_asset4->value2 = (double)rand() / RAND_MAX;
            new_asset4->value3 = (double)rand() / RAND_MAX;
            new->data = new_asset4;
        }
        new->next = (*head); // Linked list constructed as LIFO.
        (*head) = new;
    }
}

/* This function fills the given string randomly. Big case letters are used in this filling proccess.*/
void fill_string(char * string, int size)
{
    for(int a=0; a<size; a++)
    {
        string[a] = random_character();
    }
}

/* This function generates characters randomly. It returns character to the fill_string function.*/
char random_character() {
    return 'A' + rand() % 26;  
}

/* The serialize operations are made in this function. According to the type of data in the Nodes, data in all the assets
    will be writed to the binary file.*/
void serializeLinkedList(Node* head)
{
    FILE* bin_file;
    bin_file = fopen("linkedlist.bin", "wb");
    Node* tmp = head;
    
    if (bin_file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (tmp != NULL) {
        if (strcmp(((Asset1*)tmp->data)->type, "asset1") == 0) {
            Asset1* asset = (Asset1*)tmp->data;
            fwrite(asset, sizeof(Asset1), 1, bin_file);
        }
        else if (strcmp(((Asset2*)tmp->data)->type, "asset2") == 0) {
            Asset2* asset = (Asset2*)tmp->data;
            fwrite(asset, sizeof(Asset2), 1, bin_file);
        }
        else if (strcmp(((Asset3*)tmp->data)->type, "asset3") == 0) {
            Asset3* asset = (Asset3*)tmp->data;
            fwrite(asset, sizeof(Asset3), 1, bin_file);
        }
        else if (strcmp(((Asset4*)tmp->data)->type, "asset4") == 0) {
            Asset4* asset = (Asset4*)tmp->data;
            fwrite(asset, sizeof(Asset4), 1, bin_file);
        }
        else {
            printf("Unknown asset type.\n");
        }
        tmp = tmp->next;
    }

    printf("-----Serializing is successfully made-----\n");
    fclose(bin_file);
}

/* While file does not end, the deserialize operations continue. Firstly, the asset type will be read and program 
    checks which asset type is equal to the read asset type. After determining proccess, the cursor in the binary file
    move to at the beginning of the Asset.(Total variable provide us to move at the beginning of the asset.After each
    reading total is increased by size of the asset type and cursor move from beginning to end of the last read asset)  */
void deserializeLinkedList(Node** head)
{
    FILE* bin_file;
    bin_file = fopen("linkedlist.bin", "rb");

    if (bin_file == NULL) {
        printf("Error while opening the file.\n");
        return;
    }

    int total = 0;
    Node* newNode = NULL;

    while (!feof(bin_file)) {
        newNode = (Node*)malloc(sizeof(Node));

        char asset_type[20]; // it is used to specify the asset type.
        fread(asset_type, sizeof(char), 6, bin_file);

        if (strcmp(asset_type, "asset1") == 0) {
            fseek(bin_file, total, SEEK_SET);
            total += sizeof(Asset1);
            Asset1* asset1 = (Asset1*)malloc(sizeof(Asset1));
            fread(asset1, sizeof(Asset1), 1, bin_file);
            newNode->data = asset1;
        }
        else if (strcmp(asset_type, "asset2") == 0) {
            fseek(bin_file, total, SEEK_SET);
            total += sizeof(Asset2);
            Asset2* asset2 = (Asset2*)malloc(sizeof(Asset2));
            fread(asset2, sizeof(Asset2), 1, bin_file);
            newNode->data = asset2;
        }
        else if (strcmp(asset_type, "asset3") == 0) {
            fseek(bin_file, total, SEEK_SET);
            total += sizeof(Asset3);
            Asset3* asset3 = (Asset3*)malloc(sizeof(Asset3));
            fread(asset3, sizeof(Asset3), 1, bin_file);
            newNode->data = asset3;
        }
        else if (strcmp(asset_type, "asset4") == 0) {
            fseek(bin_file, total, SEEK_SET);
            total += sizeof(Asset4);
            Asset4* asset4 = (Asset4*)malloc(sizeof(Asset4));
            fread(asset4, sizeof(Asset4), 1, bin_file);
            newNode->data = asset4;
        }
        else {
            free(newNode);
            continue;
        }
        /* This proccess is made as LIFO.*/
        newNode->next = *head;
        *head = newNode;
    }

    printf("-----Deserializing is successfully made-----\n");

    fclose(bin_file);
}

