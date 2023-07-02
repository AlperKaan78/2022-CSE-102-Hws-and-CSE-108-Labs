#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000

typedef struct {
    int ID;
    int age;
    float gpa;
} Student;


float generateRandomStudents(Student* students, int size) {
    srand(time(NULL));
    students = (Student*)malloc(sizeof(Student) * ARRAY_SIZE);

    for (int i = 0; i < size; i++) {
        students[i].ID = rand() % 100;
        students[i].age = rand() % 10 + 18; 
        students[i].gpa = (float)(rand() % 5); 
    }

    float totalGPA = 0.0;

    for (int i = 0; i < size; i++) {
        totalGPA += students[i].gpa;
    }
    
    return totalGPA / size;
}

int main() {
    Student* students;

    float total_avrg_GPA = 0.0;


    for(int i=0; i<ARRAY_SIZE; i++)
    {
        total_avrg_GPA += generateRandomStudents(students, ARRAY_SIZE);
        free(students);
    }
    printf("Average GPA of 10000*10000 students: %.5f\n", total_avrg_GPA/ARRAY_SIZE);

    

    return 0;
}
