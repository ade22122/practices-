#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include "student.h"
#include "stack.h"


int main() {
    system("chcp 65001");
    struct Student* one = initstudent("Иванов", "Иван", "м", 17, 207, 5.0, 5.0, 5.0);
    struct Student* two = initstudent("Петров", "Петр", "м", 16, 207, 5.0, 5.0, 2.2);
    struct Student* three = initstudent("Сидоров", "Сидор", "м", 18, 207, 5.0, 5.0, 5.0);

    struct Student* studentArray[] = {one, two, three};
    int count = sizeof(studentArray) / sizeof(struct Student*);

    saveStudentsToFile(studentArray, count, "students.txt");
    saveStudentsToBinaryFile(studentArray, count, "students.bin");
    printf("Студенты сохранены в:'students.txt' и 'students.bin'\n");

    int loadedCount;
    struct Student** loadedStudents = loadStudentsFromBinaryFile(&loadedCount, "students.bin");
    if (loadedStudents) {

        for (int i = 0; i < loadedCount; i++) {
            loadedStudents[i]->infoOutput(loadedStudents[i]);
            free(loadedStudents[i]);
        }
        free(loadedStudents);
    } if (loadedStudents == NULL) {
        perror("Ошибка при загрузке студентов из файла");
    }

    struct Stack* students = init();
    struct {
        struct Stack* stack;
        void* elem;
    } args;


    args.stack = students;
    args.elem = one;
    push_stack(&args);

    args.elem = two;
    push_stack(&args);

    args.elem = three;
    push_stack(&args);

//    while (students->size > 0) {
//        struct Student* q = (struct Student*)pop_stack(students);
//        if (q->age >= 16 && q->age <= 18) {
//            q->infoOutput(q);
//            free(q);
//
//        }
//    }

    return 0; 

    
}
