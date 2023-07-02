#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Customer
{
    int age, priorityLevel;
    char name[20], groupName[20];
    struct Customer *next, *prev;
}Customer;

Customer *insertCustomer(Customer *pqueue);

Customer *removeCustomer(Customer *pqueue);

void displayCustomers(Customer *pqueue);

void writeFile(Customer *pqueue);

void searchCustomer(Customer *pqueue);

Customer* changePriority(Customer* pqueue);

int main()
{
    Customer *pqueue = NULL;

    char selection;


    while(selection != '6')
    {
        printf("Welcome to the ABC bank.\n\n1-Insert new costumer.\n2-Remove costumer.\n3-Display costumers in order.\n4-Search a customer.\n5-Change priority settings.\n6-Exit\n\n");
        scanf(" %c",&selection);
        
        switch (selection)
        {
        case '1':pqueue = insertCustomer(pqueue);writeFile(pqueue); break;
        case '2':pqueue = removeCustomer(pqueue);writeFile(pqueue); break;
        case '3':displayCustomers(pqueue); break;
        case '4':searchCustomer(pqueue); break;    
        case '5':changePriority(pqueue); break;
        case '6':printf("GOODBYE:)\n\n");break;
        default:printf("Invalid selection"); break;
        }

    }
}

Customer* insertCustomer(Customer* pqueue) {
    Customer* n, * l;
    n = (Customer*)malloc(sizeof(Customer));
    n->next = NULL;
    n->prev = NULL;

    printf("Please enter customer's name: ");
    scanf(" %19s", n->name);

    printf("Please enter customer's age: ");
    scanf("%d", &n->age);

    printf("Please enter priority group: ");
    scanf(" %19s", n->groupName);

    if (strcmp(n->groupName, "NORMAL") == 0) {
        n->priorityLevel = 1;
    }
    else if (strcmp(n->groupName, "VETERAN") == 0) {
        n->priorityLevel = 2;
    }
    else if (strcmp(n->groupName, "OD") == 0) {
        n->priorityLevel = 3;
    }
    else if (strcmp(n->groupName, "VIP") == 0) {
        n->priorityLevel = 4;
    }

    if (pqueue == NULL) {
        pqueue = n;
    }
    else {
        l = pqueue;
        while (l != NULL) {
            if (l->priorityLevel < n->priorityLevel) {
                if (l->prev == NULL) {
                    n->next = l;
                    l->prev = n;
                    pqueue = n;
                }
                else {
                    l->prev->next = n;
                    n->prev = l->prev;
                    l->prev = n;
                    n->next = l;
                }
                break;
            }
            else if (l->next == NULL) {
                l->next = n;
                n->prev = l;
                break;
            }
            l = l->next;
        }
    }

    printf("Customer added successfully.\n\n");
    return pqueue;
}


Customer* removeCustomer(Customer* pqueue) {
    char name[20];
    int isRemoved = 0;

    printf("Please enter the customer's name: ");
    scanf(" %19s", name);

    if (pqueue == NULL) {
        printf("The list is empty.\n");
    }
    else {
        Customer* l = pqueue;
        while (l != NULL) {
            if (strcmp(l->name, name) == 0) {
                if (l->prev == NULL) {
                    pqueue = l->next;
                    if (pqueue != NULL) {
                        pqueue->prev = NULL;
                    }
                }
                else {
                    l->prev->next = l->next;
                    if (l->next != NULL) {
                        l->next->prev = l->prev;
                    }
                }
                free(l);
                isRemoved = 1;
                printf("Customer removed successfully.\n");
                break;
            }
            l = l->next;
        }
    }

    if (!isRemoved) {
        printf("Customer not found.\n");
    }

    return pqueue;
}


void displayCustomers(Customer *pqueue){

    while(pqueue != NULL)
    {
        printf("%s - AGE: %d - LEVEL: %d - GROUP: %s\n",pqueue->name,pqueue->age,pqueue->priorityLevel,pqueue->groupName);
        pqueue =pqueue->next;
    }
    
}

void writeFile(Customer *pqueue)
{
    FILE *cf;
    cf=fopen("customer.txt","w");

    while(pqueue != NULL)
    {
        fprintf(cf, "%s - AGE: %d - LEVEL: %d - GROUP: %s\n",pqueue->name,pqueue->age,pqueue->priorityLevel,pqueue->groupName);
        pqueue =pqueue->next;
    }
    fclose(cf);
}

void searchCustomer(Customer *pqueue){

    char name[20];

    int isFound=0;
    printf("Please enter customer's name: ");
    scanf(" %19s",name);

    while (pqueue != NULL)
    {
        if(strcmp(pqueue->name,name)==0)
        {
            printf("Found: %s - AGE: %d - LEVEL: %d - GROUP: %s\n",pqueue->name,pqueue->age,pqueue->priorityLevel,pqueue->groupName);
            isFound = 1;
            break;
        }
        pqueue=pqueue->next;
        
    }

    if(!isFound)
    {
        printf("Entered customer not found.\n\n");
    }  
}

Customer* changePriority(Customer* pqueue) {
    char name[20];
    int newPriority;
    Customer *l;
    printf("Please enter the customer's name: ");
    scanf(" %19s", name);

    printf("Please enter the new priority level: ");
    scanf("%d", &newPriority);

    Customer* current = pqueue;
    int customerFound = 0;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->priorityLevel = newPriority;
            customerFound = 1;
            printf("Priority level for customer has been updated.\n");
            break;
        }
        current = current->next;
    }

    if (!customerFound) {
        printf("Customer %s not found.\n", name);
    }
}
