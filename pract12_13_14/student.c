#include "student.h"
#include <stdio.h>
#include <stdlib.h>

void infoOutput(void* student) {
    struct Student* s = (struct Student*)student;
    printf("Фамилия: %s\n", s->surname);
    printf("Имя: %s\n", s->name);
    printf("Пол %s\n", s->sex);
    printf("Возраст: %d\n", s->age);
    printf("Группа: %d\n", s->group);
    printf("Отметка по математике: %f\n", s->mathMark);
    printf("Отметка по физике: %f\n", s->physicsMark);
    printf("Отметка по химии: %f\n", s->chemistryMark);
}

struct Student* initstudent(char* surname, char* name, char* sex, int age, int group, float mathMark, float physickMark, float chemistryMark) {
    struct Student* result = malloc(sizeof(struct Student));
    result->surname = surname;
    result->name = name;
    result->sex = sex;
    result->age = age;
    result->group =  GROUP_MACRO(group);;
    result->mathMark = mathMark;
    result->physicsMark = physickMark;
    result->chemistryMark = chemistryMark;
    result->infoOutput = infoOutput;
    return result;
}
void saveStudentsToFile(struct Student* students[], int count, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка файла");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s;%s;%s;%d;%d;%f;%f;%f\n", students[i]->surname, students[i]->name, students[i]->sex,
                students[i]->age, students[i]->group, students[i]->mathMark, students[i]->physicsMark, students[i]->chemistryMark);
    }

    fclose(file);
}
void saveStudentsToBinaryFile(struct Student* students[], int count, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Cannot open file for writing");
        return;
    }

    fwrite(&count, sizeof(int), 1, file);  // Записываем количество студентов

    for (int i = 0; i < count; i++) {
        fwrite(students[i], sizeof(struct Student), 1, file);  // Записываем данные студентов
    }

    fclose(file);
}

struct Student** loadStudentsFromBinaryFile(int* count, const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Cannot open file for reading");
        return NULL;
    }

    fread(count, sizeof(int), 1, file);  // Читаем количество студентов

    struct Student** students = malloc(*count * sizeof(struct Student*));
    if(students == NULL){
        perror("Ошибка выделения памяти для студентов в struct loadStudentsFromBinaryFile");
        return NULL;
    }
    if (!students) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < *count; i++) {
        students[i] = malloc(sizeof(struct Student));
        if(students[i] == NULL){
            perror("Ошибка выделения памяти для студента в struct loadStudentsFromBinaryFile");
            return NULL;
        }
        fread(students[i], sizeof(struct Student), 1, file);  // Читаем данные студентов
    }

    fclose(file);
    return students;
}
