#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        int len = strlen(students[i]->surname);
        int gen = strlen(students[i]->name);
        int cen = strlen(students[i]->sex);
        fwrite(&len, sizeof(int), 1, file);
        fwrite(students[i]->surname, sizeof(char), len, file);
        fwrite(&gen, sizeof(int), 1, file);
        fwrite(students[i]->name, sizeof(char), gen, file);
        fwrite(&cen, sizeof(int), 1, file);
        fwrite(students[i]->sex, sizeof(char), cen, file);
        fwrite (&students[i]->age , sizeof(int), 1, file);
        fwrite (&students[i]->group , sizeof(int), 1, file);
        fwrite (&students[i]->mathMark , sizeof(float), 1, file);
        fwrite (&students[i]->physicsMark , sizeof(float), 1, file);
        fwrite (&students[i]->chemistryMark , sizeof(float), 1, file);
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
        int tmpsize;
        
        fread(&tmpsize, sizeof(int), 1, file);
        students[i]->surname = malloc(tmpsize * sizeof(char) + 1);
        students[i]->surname[tmpsize] = '\0';
        fread(students[i]->surname,sizeof(char),tmpsize,file);
         fread(&tmpsize, sizeof(int), 1, file);
        students[i]->name = malloc(tmpsize * sizeof(char) + 1);
        students[i]->name[tmpsize] = '\0';
        fread(students[i]->name,sizeof(char),tmpsize,file);
         fread(&tmpsize, sizeof(int), 1, file);
        students[i]->sex = malloc(tmpsize * sizeof(char) + 1);
        students[i]->sex[tmpsize] = '\0';
        fread(students[i]->sex,sizeof(char),tmpsize,file);
        fread (&students[i]->age , sizeof(int), 1, file);
        fread (&students[i]->group , sizeof(int), 1, file);
        fread (&students[i]->mathMark , sizeof(float), 1, file);
        fread (&students[i]->physicsMark , sizeof(float), 1, file);
        fread (&students[i]->chemistryMark , sizeof(float), 1, file);
        students[i]->infoOutput=infoOutput;
    }

    fclose(file);
    return students;
}

