#ifndef UTIL_H
#define UTIL_H

#define FIFO 0
#define LIFO 1


typedef struct book_t
{
    char isbn[20], title[30],author[20];    
    int status,pub_year;
    struct book_t *next;
}book_t;

/* Each student can have 10 books at most.*/

typedef struct student_t
{
    char name[20], ID[20];
    char brwd_books[10][30];
    int num_of_books;
    struct student_t *next;
}student_t;






void list_brwd_books(student_t *std_root, char * ID);

void add_book(book_t **book_root, char* isbn, char* title, char* author, int publicationYear, int method);

void delete_book(book_t **book_root, char* isbn);

void updateBook(book_t **book_root, char* isbn, char* feature, char* value) ;

void filterAndSortBooks(book_t *book_root,int filterChoice, char* filter, int sortChoice);

void reverseBookList(book_t **book_root);

void searchBooks(book_t *book_root, int searchChoice, char* searchValue);

void borrowBook(book_t** book_root,student_t** std_root, char * isbn);

void returnBook(book_t** book_root,student_t** std_root, char * isbn);

book_t * get_books(book_t *book_root);

void list_books(book_t *book_root);

void update_lb_file(book_t *book_root);

void update_student_file(student_t *std_root);

student_t *get_students(student_t *std_root);

#endif