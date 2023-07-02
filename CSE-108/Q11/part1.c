#include<stdio.h>
#include<stdlib.h>


typedef struct Order
{
    char customerName[50],items[50],orderTime[20];
    int orderID;
    struct Order *next;
}Order;


void my_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

Order* list_enqueue(Order* queue, char* customerName, int orderID, char* items, char* orderTime) {
    Order* n;
    printf("Enqueue operation:\n");
    printf("Enqueued : Order ID: %d, Customer Name: %s, Items: %s \n",orderID,customerName,items);

    n = (Order*)malloc(sizeof(Order));

    my_strcpy(n->customerName, customerName);
    my_strcpy(n->items, items);
    my_strcpy(n->orderTime, orderTime);
    n->orderID = orderID;

    n->next = queue;  
    queue = n;  

    return queue; 
}


Order * dequeue(Order * queue)
{
    Order *l;
    l=queue;
    printf("Dequeue Operation:\n");

    while(l->next != NULL)
    {
        printf("Dequeued: Order ID: %d, Customer Name: %s, Items: %s \n",l->orderID,l->customerName,l->items);
        free(l);
        l= l->next;
    }
    return l;
}

void display(Order * queue)
{
    Order *m;
    m=queue;
    printf("Display Orders by Order Time:\n");
    while(m != NULL)
    {
        printf("Order ID: %d, Customer Name: %s, Items: %s \n",m->orderID,m->customerName,m->items);
        m=m->next;
    }
}

void updateOrder(Order * queue, int orderID, char * newItems)
{
    Order *l;
    l=queue;
    while(l->orderID != orderID)
    {
        l=l->next;
    }
    printf("Updated Order:Order ID: %d, Customer Name: %s, Items: %s \n",l->orderID,l->customerName,newItems);
    my_strcpy(l->items, newItems);
    
}

int main()
{
    Order * queue = NULL;
    queue = list_enqueue(queue,"Alper",15,"pizza","first" );
    queue = list_enqueue(queue,"Mehmet",18,"cake, coffee","second" );
    queue = list_enqueue(queue,"Ahmet",19,"hamburger","third" );
    queue = list_enqueue(queue,"Ali",20,"Kebap","aa" );

    display(queue);
    updateOrder(queue, 20,"su, ayran, durum");
    display(queue);
    
    queue = dequeue(queue);
    display(queue);

}