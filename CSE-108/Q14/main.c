#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Order {
    char customerName[50];
    char items[50];
    time_t orderTime;
    int orderID;
    struct Order* next;
} Order;

typedef struct LIFO {
    Order* list;
} LIFO;

typedef struct FIFO {
    Order* list;
} FIFO;

void my_strcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

Order* list_enqueue(Order* list, char* customerName, int orderID, char* items, time_t orderTime) {
    Order* n;

    time_t timestamp = orderTime;
    char* timeString = ctime(&timestamp);
    printf("Enqueue operation:\n");
    printf("Enqueued: Order ID: %d, Customer Name: %s, Items: %s, Time: %s\n", orderID, customerName, items,timeString);

    n = (Order*)malloc(sizeof(Order));
    if (n == NULL) {
        printf("Failed to allocate memory.\n");
        return list;
    }

    my_strcpy(n->customerName, customerName);
    my_strcpy(n->items, items);
    n->orderTime = orderTime;
    n->orderID = orderID;

    n->next = list;
    list = n;

    return list;
}

Order* dequeue(Order* list, time_t thresholdTime) {
    Order* current = list;
    Order* previous = NULL;
    int success = 0;

    while (current != NULL) {
        time_t timestamp = current->orderTime;
        if (timestamp > thresholdTime) {
            Order* temp = current;

            if (previous == NULL) 
                list = current->next; 
            else 
                previous->next = current->next;

            current = current->next;
            printf("The oldest order successfully deleted according to the threshold.\n");
            success = 1;
            free(temp);

            break;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    if (!success) 
    {
        printf("\nInvalid threshold.\n\n");
    }

    return list;
}

void display(Order* list) {
    Order* m;
    m = list;
    printf("Display Orders according to the operation:\n");
    while (m != NULL) {
        time_t timestamp = m->orderTime;
        char* timeString = ctime(&timestamp);
        printf("Order ID: %d, Customer Name: %s, Items: %s, Order Time:%s", m->orderID, m->customerName, m->items, timeString);
        m = m->next;
    }
}

void serializeLIFO(LIFO* stack, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    Order* current = stack->list;
    while (current != NULL) {
        fwrite(current, sizeof(Order), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("LIFO data structure serialized to a binary file.\n\n");
}

LIFO* deserializeLIFO(const char* filename) {
    FILE* binFile;
    binFile = fopen(filename, "rb");


    if (binFile == NULL) 
    {
        printf("Failed to open binary file for reading.\n");
        return NULL;
    }

    LIFO* stack = (LIFO*)malloc(sizeof(LIFO));
    if (stack == NULL) {
        printf("Failed to allocate memory for stack.\n");
        fclose(binFile);
        return NULL;
    }

    stack->list = NULL;

    Order* current = NULL;

    while (1) {
        current = (Order*)malloc(sizeof(Order));
        if (fread(current, sizeof(Order), 1, binFile) != 1) {
            free(current);
            break;
        }

        current->next = stack->list;
        stack->list = current;
    }

    fclose(binFile);


    printf("LIFO data structure successfully deserialized to a stack.\n\n");

    return stack;
}


void serializeFIFO(FIFO* queue, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    Order* current = queue->list;
    while (current != NULL) {
        fwrite(current, sizeof(Order), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("FIFO data structure serialized to a binary file.\n\n");
}

FIFO* deserializeFIFO(const char* filename) {
    FILE* binFile;
    binFile = fopen(filename, "rb");
    if (binFile == NULL) {
        printf("Failed to open file for reading.\n");
        return NULL;
    }

    FIFO* queue = (FIFO*)malloc(sizeof(FIFO));
    if (queue == NULL) {
        printf("Failed to allocate memory.\n");
        fclose(binFile);
        return NULL;
    }

    queue->list = NULL;

    Order* current = NULL;
    Order* previous = NULL;

    while (1) {
        current = (Order*)malloc(sizeof(Order));
        if (fread(current, sizeof(Order), 1, binFile) != 1) {
            free(current);
            break;
        }

        current->next = NULL;

        if (previous == NULL) {
            queue->list = current;
        } else {
            previous->next = current;
        }

        previous = current;
    }

    fclose(binFile);
    printf("FIFO data structure successfully deserialized to queue.\n\n");

    return queue;
}

int main() {
    Order* queue = NULL;
    queue = list_enqueue(queue, "Alper", 15, "pizza", time(NULL));
    queue = list_enqueue(queue, "Mehmet", 18, "cake, coffee", time(NULL));
    queue = list_enqueue(queue, "Ahmet", 19, "hamburger", time(NULL));


    display(queue);
    queue = dequeue(queue, 145);

    display(queue);
    LIFO* stack;
    stack = (LIFO*)malloc(sizeof(LIFO));
    stack->list = queue;
    serializeLIFO(stack, "exFile.bin");

    stack = deserializeLIFO("exFile.bin");
    display(stack->list);

    queue = list_enqueue(queue, "Ali", 20, "Kebap", time(NULL));
    queue = list_enqueue(queue, "kemal",29,"cay,borek,pogaca",time(NULL));

    FIFO*q;
    q = (FIFO*)malloc(sizeof(FIFO));
    q->list = queue;
    serializeFIFO(q,"exFile.bin");

    q = deserializeFIFO("exFile.bin");
    display(q->list);
    return 0;
}
