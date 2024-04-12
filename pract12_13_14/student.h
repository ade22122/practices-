#ifndef STUDENT_H
#define STUDENT_H

#define GROUP_MACRO(x) (x * 1000)

struct Student {
    char *surname;
    char *name;
    char *sex;
    int age;
    int group;
    float mathMark;
    float physicsMark;
    float chemistryMark;
    void (*infoOutput)(void*);
};

struct Student* initstudent(char* surname, char* name, char* sex, int age, int group, float mathMark, float physickMark, float chemistryMark);
void infoOutput(void* student);
void saveStudentsToFile(struct Student* students[], int count, const char* filename);
void saveStudentsToBinaryFile(struct Student* students[], int count, const char* filename);
struct Student** loadStudentsFromBinaryFile(int* count, const char* filename);


#endif
