#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "util.h"

int main()
{
    FILE *student_file;
    student_file= fopen("student.txt","r");

    book_t *book_root = NULL;
    student_t *std_root = NULL;

    std_root = get_students(std_root);

    char selection = '0', filter[30], isbn[20], author[20], title[30], ID[20], feature[30], value[30];
    int method, filter_choice, sort_choice, publicationYear;

    book_root = get_books(book_root);


    while(selection != 'x')
    {
        printf("1-Add book.\n2-List borrowed books.\n3-List all books in library.\n4-Delete book.\n5-Update book.\n6-Filter and sort books.\n7-Search book.\n8-Reverse book list.\n9-Return or borrow book.\n");
        printf("\n\nEnter the selection:");scanf(" %c",&selection);
        switch (selection)
        {
        case '1':
            printf("Please enter the ISBN number: ");scanf("%s",isbn);
            printf("Please enter the author: ");scanf(" %[^\n]",author);
            printf("Please enter the title: ");scanf(" %[^\n]",title);
            printf("Please enter the publication year: ");scanf(" %d", &publicationYear);
            do{
                printf("Please enter the method (1-LIFO 0-FIFO): ");scanf(" %d",&method);
            }while(method != LIFO && method != FIFO);

            add_book(&book_root,isbn,title,author,publicationYear,method);
            
            break;
        case '2':
            printf("Please enter the student ID for searching: ");scanf("%s",ID);
            list_brwd_books(std_root,ID);
            break;
        case '3':
            list_books(book_root);
            break;
        
        case '4':
            printf("Please enter the isbn number to delete book: ");scanf(" %[^\n]",isbn);
            delete_book(&book_root,isbn);
            break;
        
        case '5':
            printf("Please enter the isbn number to update the book: ");scanf(" %[^\n]",isbn);
            printf("Please enter the feature that you want to change it: ");scanf(" %[^\n]",feature);
            printf("Please enter the new value for that feature: ");scanf(" %[^\n]",value);
            updateBook(&book_root,isbn,feature,value);
            break;

        case '6':
            do{
                printf("Please enter the filter choice (0-Author 1-Publication Year): ");scanf(" %d",&filter_choice);
            }while(filter_choice != 0 && filter_choice != 1);

            printf("Please enter the filter: ");scanf(" %[^\n]",filter);

            do{
                printf("Please enter the sort choice (0-title 1-Author 2-Publication year.): ");scanf(" %d", &sort_choice);
            }while(sort_choice != 0 && sort_choice != 1 && sort_choice !=2);
            
            filterAndSortBooks(book_root,filter_choice,filter,sort_choice);
            break;
        case '7':
            do{
                printf("Please enter the search choice (0-ISBN 1-Author 2-Title): ");scanf(" %d",&filter_choice);
            }while(filter_choice != 0 && filter_choice != 1 && filter_choice != 2);
            printf("Enter the search value: ");scanf(" %[^\n]",filter); 


            searchBooks(book_root,filter_choice,filter);

            break;
        case '8':
            reverseBookList(&book_root);
            list_books(book_root);
            break;
        case '9':
            printf("Please enter the operation:\n1-Borrow book.\n2-Return book.\n");
            scanf(" %c",&selection);
            printf("Please enter the ISBN number of the book: ");scanf(" %[^\n]",isbn);
            if(selection == '1')
            {
                borrowBook(&book_root,&std_root,isbn);
            }
            else if(selection == '2')
            {
                returnBook(&book_root,&std_root,isbn);
            }
            else{
                printf("Invalid operation.\n");
            }
            update_student_file(std_root);
            break;
        case 'x':
            printf("Exitting...\n\n");
            break;      
        default:
            printf("Invalid selection.Try again!\n");
            break;
        }
        /* After each operation the book file is updated.*/
        update_lb_file(book_root);
    }
    return 0;
}

/* This function adds book list another book that receiving from the user.*/
void add_book(book_t **book_root, char* isbn, char* title, char* author, int publicationYear, int method){

    book_t *new,*tmp;
    new = (book_t *)malloc(sizeof(book_t));
    
    /* New values are copying into the variables that in the book_t struct.*/
    strcpy(new->isbn,isbn);
    strcpy(new->title,title);
    strcpy(new->author,author);
    new->pub_year = publicationYear;
    new->status = 0;
    new->next = NULL;

    /* If the method is LIFO these lines will be executed.*/
    if(method == LIFO)
    {
        new->next = (*book_root);
        (*book_root) = new;
    }

    /* If the method is FIFO these lines will be executed.*/    
    else if(method == FIFO)
    {
        tmp = *book_root; // I need temporary pointer to iterate over the list and add the new item at the end of the list.
        if(*book_root == NULL)
        {
            *book_root = new;
        }
        else
        {
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = new;
        }    
    }

}   

void list_brwd_books(student_t *std_root, char *ID){
    student_t *tmp;
    tmp = std_root;
    
    int is_find = 0;
    while(tmp != NULL)
    {
        if(strcmp(tmp->ID, ID) == 0)
        {
            int i = 0;
            is_find = 1;
            while(i<tmp->num_of_books)
            {
                printf("%s\n",tmp->brwd_books[i]);
                i++;
            }
        }
        tmp = tmp->next;
    }
    if(!is_find)
    {
        printf("The student is not found..\n");
    }

}

/* get_books function will get the books from the library file into the book_root list at the beginning of the program.*/
book_t* get_books(book_t *book_root){
    FILE *library_file;
    library_file = fopen("library.txt","r");
    book_t *new,*tmp;

    while (!feof(library_file))
    {
        tmp=book_root;
        new = (book_t*)malloc(sizeof(book_t));
        fscanf(library_file,"%[^,],%[^,],%[^,],%d,%d\n",new->isbn,new->title,new->author,&new->pub_year,&new->status);

        if(tmp == NULL)
        {
            book_root = new;
            new->next = NULL;
        }
        else {
            while(tmp->next != NULL)
            {
                tmp = tmp->next;
            }
            tmp->next = new;
            new->next = NULL;

        }   
    }
    fclose(library_file);
    return book_root;
}

/* This function gets students information in the student.txt file into the student_t list.*/
student_t* get_students(student_t* std_root)
{
    FILE* student_file;
    student_file = fopen("student.txt", "r");
    if (student_file == NULL) {
        printf("Failed to open the file.\n");
        return std_root;
    }

    student_t* last_student = NULL;

    student_t* student = (student_t*)malloc(sizeof(student_t));
    student->next = NULL;

    student->num_of_books = 0;
    int iter = 0;
    while (fscanf(student_file, " %[^,],%[^,]", student->name, student->ID) == 2)
    {
        if(iter!=0)
        {
            student_t* student = (student_t*)malloc(sizeof(student_t));
            student->next = NULL;
            student->num_of_books = 0;
        }
        iter++;
        
        char a;

        getc(student_file); // Consume the comma after the student ID
        
        do {
            fscanf(student_file, " %[^,\n]", student->brwd_books[student->num_of_books]);
            student->num_of_books++;
            a = getc(student_file);
        } while (student->num_of_books < 10 && a == ',');

        if (std_root == NULL) {
            std_root = student;
            last_student = student;
        }
        else {
            last_student->next = student;
            last_student = student;
        }
    }

    fclose(student_file);
    return std_root;
}


/* This function is created for print the books in the book list.*/
void list_books(book_t *book_root)
{
    book_t *tmp;
    tmp = book_root;
    while(tmp != NULL)
    {
        printf("%s,%s,%s,%d,%d\n",tmp->isbn,tmp->title,tmp->author,tmp->pub_year,tmp->status);
        tmp = tmp->next;
    }
}



/* This function was created to update the library file with new book list. */
void update_lb_file(book_t *book_root)
{
    FILE *library_file;

    library_file = fopen("library.txt","w");

    book_t *tmp;

    tmp = book_root;

    while (tmp != NULL)
    {
        fprintf(library_file,"%s,%s,%s,%d,%d\n",tmp->isbn,tmp->title,tmp->author,tmp->pub_year,tmp->status);
        tmp = tmp->next;
    }
    
    fclose(library_file);
}


/* The deleting operation is made here.*/
void delete_book(book_t **book_root, char* isbn) {
    
    if (*book_root == NULL) {
        return;
    }
    
    book_t *current = *book_root;
    book_t *previous = NULL;
    int is_found = 0;

    while (current != NULL) {
        if (strcmp(current->isbn, isbn) == 0) {
            is_found=1;
            
            if (previous == NULL) {
                *book_root = current->next;
            } 
            else {
                previous->next = current->next;
            }
            
            free(current); // temporary pointer current is deallocating here.
        }
        
        previous = current;
        current = current->next;
    }
    if(!is_found)
        printf("Book is not found\n");
    else
        printf("Book is successfully deleted.\n");
}



void updateBook(book_t **book_root, char *isbn, char *feature, char *value)
{
    book_t *tmp;
    tmp = *book_root;
    if(strcmp(feature,"title") == 0)
    {
        while(tmp != NULL)
        {
            if(strcmp(isbn,tmp->isbn) == 0)
            {
                strcpy(tmp->title, value);
                return;
            }
            tmp = tmp->next;
        }
        printf("Book is not found.\n");
    }
    else if(strcmp(feature, "author") == 0)
    {
        while(tmp != NULL)
        {
            if(strcmp(isbn,tmp->isbn) == 0)
            {
                strcpy(tmp->author, value);
                return;
            }
            tmp = tmp->next;
        }
        printf("Book is not found.\n");
    }
    else if(strcmp(feature,"publication year") == 0)
    {
        while(tmp != NULL)
        {
            if(strcmp(isbn,tmp->isbn) == 0)
            {
                tmp->pub_year = atoi(value);
                return;
            }
            tmp = tmp->next;

        }
        printf("Book is not found.\n");
    }
    else
    {
        printf("Given feature name is not valid feature for this system! \n");
    }
}



/* According to the choiced filter and sort selections, operations will be made in this function.*/
void filterAndSortBooks(book_t *book_root, int filterChoice, char* filter, int sortChoice)
{
    book_t *tmp = book_root;
    book_t *filtered = NULL;
    book_t *lastFiltered = NULL;

    while (tmp != NULL)
    {
        if (filterChoice == 0 && strcmp(tmp->author, filter) == 0)
        {
            book_t *newFiltered = malloc(sizeof(book_t));
            memcpy(newFiltered, tmp, sizeof(book_t));
            newFiltered->next = NULL;

            if (filtered == NULL)
            {
                filtered = newFiltered;
                lastFiltered = newFiltered;
            }
            else
            {
                lastFiltered->next = newFiltered;
                lastFiltered = newFiltered;
            }
        }
        else if (filterChoice == 1 && tmp->pub_year == atoi(filter))
        {
            book_t *newFiltered = malloc(sizeof(book_t));
            memcpy(newFiltered, tmp, sizeof(book_t));
            newFiltered->next = NULL;

            if (filtered == NULL)
            {
                filtered = newFiltered;
                lastFiltered = newFiltered;
            }
            else
            {
                lastFiltered->next = newFiltered;
                lastFiltered = newFiltered;
            }
        }

        tmp = tmp->next;
    }
    
    tmp = filtered;
    book_t *sorted = NULL;

    /* Sorting operation is made here according to the sortChoice variable.*/
    if (sortChoice == 0) // title
    {
        while (tmp != NULL)
        {
            book_t *newNode = malloc(sizeof(book_t));
            memcpy(newNode, tmp, sizeof(book_t));
            newNode->next = NULL;

            if (sorted == NULL || strcmp(newNode->title, sorted->title) < 0)
            {
                newNode->next = sorted;
                sorted = newNode;
            }
            else
            {
                book_t *current = sorted;
                while (current->next != NULL && strcmp(newNode->title, current->next->title) >= 0)
                {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }

            tmp = tmp->next;
        }
    }
    else if (sortChoice == 1) // author
    {
        while (tmp != NULL)
        {
            book_t *newNode = malloc(sizeof(book_t));
            memcpy(newNode, tmp, sizeof(book_t));
            newNode->next = NULL;

            if (sorted == NULL || strcmp(newNode->author, sorted->author) < 0)
            {
                newNode->next = sorted;
                sorted = newNode;
            }
            else
            {
                book_t *current = sorted;
                while (current->next != NULL && strcmp(newNode->author, current->next->author) >= 0)
                {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }

            tmp = tmp->next;
        }
    }
    else if (sortChoice == 2) // publication year
    {
        while (tmp != NULL)
        {
            book_t *newNode = malloc(sizeof(book_t));
            memcpy(newNode, tmp, sizeof(book_t));
            newNode->next = NULL;

            if (sorted == NULL || newNode->pub_year < sorted->pub_year)
            {
                newNode->next = sorted;
                sorted = newNode;
            }
            else
            {
                book_t *current = sorted;
                while (current->next != NULL && newNode->pub_year >= current->next->pub_year)
                {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }

            tmp = tmp->next;
        }
    }
    /* Sorted list is written.*/
    while (sorted != NULL)
    {
        printf("%s,%s,%s,%d,%d\n", sorted->isbn, sorted->title, sorted->author, sorted->pub_year, sorted->status);
        sorted = sorted->next;
    }

    // Cleanup memory
    while (filtered != NULL)
    {
        book_t *next = filtered->next;
        free(filtered);
        filtered = next;
    }
    /* If sorted pointer is not NULL then all the temporary variables is being deallocated here. */
    while(sorted != NULL)
    {
        book_t *next = sorted->next;
        free(sorted);
        sorted = next;        
    }
}




void searchBooks(book_t *book_root, int searchChoice, char* searchValue)
{
    book_t *tmp = book_root;
    int is_find=0;
    
    // Searching and printing operations is made here according to the choice.
 
    switch (searchChoice)
    {
    case 0:
        while(tmp != NULL)
        {
            if(strcmp(tmp->isbn, searchValue) == 0)
            {
                printf("ISBN: %s, TITLE: %s, AUTHOR: %s,PUBLISHED YEAR: %d, STATUS: %d\n", tmp->isbn, tmp->title, tmp->author, tmp->pub_year, tmp->status); 
                is_find=1;
            }
            tmp = tmp->next;
        }
        break;
    case 1:
        while(tmp != NULL)
        {
            if(strcmp(tmp->author, searchValue) == 0)
            {
                printf("ISBN: %s, TITLE: %s, AUTHOR: %s,PUBLISHED YEAR: %d, STATUS: %d\n", tmp->isbn, tmp->title, tmp->author, tmp->pub_year, tmp->status); 
                is_find =1;
            }
            tmp = tmp->next;
        }
        break;  
    case 2:
        while(tmp != NULL)
        {
            if(strcmp(tmp->title, searchValue) == 0)
            {
                printf("ISBN: %s, TITLE: %s, AUTHOR: %s,PUBLISHED YEAR: %d, STATUS: %d\n", tmp->isbn, tmp->title, tmp->author, tmp->pub_year, tmp->status); 
                is_find=1;
            }
            tmp = tmp->next;
        }
        break;
    default:break;
    }    
    if(!is_find)
    {
        printf("There are no books matching your search.\n\n");
    }
}

/* This function just reverse book list. */
void reverseBookList(book_t **book_root)
{
    book_t *tmp,*current =NULL, *reversed = NULL;
    tmp = *book_root;

    while(tmp != NULL)
    {
        book_t *new = (book_t*)malloc(sizeof(book_t));
        memcpy(new,tmp,sizeof(book_t));
        new->next = NULL;

        current = reversed;
        reversed = new;
        reversed->next = current;

        tmp = tmp->next;
    }
    *book_root = reversed;

}

void borrowBook(book_t **book_root, student_t **std_root, char *isbn) {
    char ID[20], is_find = 0, is_student = 0;
    printf("Please enter the student ID: ");
    scanf(" %[^\n]", ID);

    student_t *tmp = *std_root;
    book_t *bk_tmp = *book_root;
    while(tmp != NULL)
    {
        if(strcmp(tmp->ID, ID) == 0)
        {
            is_student = 1;
            break;
        }
        tmp = tmp->next;
    }
    if(!is_student)
    {
        printf("Student was not found.\n\n");
    }
    else{
        while(bk_tmp != NULL)
        {
            if(strcmp(bk_tmp->isbn,isbn) == 0)
            {
                is_find = 1;
                if(bk_tmp->status == 1)
                {
                    printf("The book was taken by somebody.\n\n");
                    break;
                }
                else{
                    bk_tmp->status = 1;
                    
                    strcpy(tmp->brwd_books[tmp->num_of_books], bk_tmp->title);
                    tmp->num_of_books++;
                    printf("Borrowing operation was successfully made.\n\n");
                    break;
                }
            }
            bk_tmp = bk_tmp->next;
        }
        if(!is_find)
        {
            printf("There is no book with this ISBN number\n\n");
        }
    }   
}

/* This function updates the file with latest version of the student list.*/
void update_student_file(student_t *std_root)
{
    FILE *student_file;
    student_file = fopen("student.txt","w");
    student_t *tmp = std_root;
    int i;
    while(tmp != NULL)
    {
        fprintf(student_file,"%s,%s,",tmp->name,tmp->ID);
        i=0;
        while(i<tmp->num_of_books)
        {
            fprintf(student_file,"%s,",tmp->brwd_books[i]);
            i++;
        }
        fprintf(student_file,"\n");
        tmp = tmp->next;
    }
    fclose(student_file);
}
/*Returning operation is made here.*/
void returnBook(book_t **book_root,student_t **std_root, char * isbn)
{
    char ID[20], is_find = 0, is_student = 0;
    printf("Please enter the student ID: ");
    scanf(" %[^\n]", ID);

    student_t *tmp = *std_root;
    book_t *bk_tmp = *book_root;
    while(tmp != NULL)
    {
        if(strcmp(tmp->ID, ID) == 0)
        {
            is_student = 1;
            break;
        }
        tmp = tmp->next;
    }
    if(!is_student)
    {
        printf("Student was not found.\n\n");
    }
    else{
        while(bk_tmp != NULL)
        {
            printf("%s :: %s\n",bk_tmp->isbn, isbn);
            if(strcmp(bk_tmp->isbn,isbn) == 0)
            {
                is_find = 1;
                if(bk_tmp->status == 0)
                {
                    printf("The book was not taken by somebody.\n\n");
                    break;
                }
                else{
                    bk_tmp->status = 0;
                    
                    strcpy(tmp->brwd_books[tmp->num_of_books], bk_tmp->title);
                    tmp->num_of_books++;
                    printf("Returning operation was successfully made.\n\n");
                    break;
                }
            }
            bk_tmp = bk_tmp->next;
        }
        if(!is_find)
        {
            printf("There is no book with this ISBN number\n\n");
        }
    }  
}
