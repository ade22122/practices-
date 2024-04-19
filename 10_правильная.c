#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Student{
    char *surname;
    char *name;
    char *sex;
    int age;
    int group;
    float mathMark;
    float physicsMark;
    float chemistryMark;
    void (*infoOutput)(struct Student *student);
};

struct Tree{
    struct Student data;
    struct Tree* left;
    struct Tree* right;
    int count;
    void (*add_node)(struct Tree* node, struct Student data);
    void (*clear)(struct Tree* node);
};

void tree_add_node(struct Tree* node, struct Student data);
void tree_clear(struct Tree* node);

struct Tree* tree_init(struct Student data){
    struct Tree* result = malloc(sizeof(struct Tree));
    result->data = data;
    result->count = 1;
    result->add_node = tree_add_node;
    result->right = NULL;
    result->left = NULL;
    result->clear = tree_clear;

    return result;
}

void tree_add_node(struct Tree* node, struct Student data){
    if (node->data.age < data.age) {
        if (node->left == NULL) {
            node->left = tree_init(data);
            return;
        }
        tree_add_node(node->left, data);
        return;
    }
    if (node->data.age > data.age) {
        if (node->right == NULL) {
            node->right = tree_init(data);
            return;
        }
        tree_add_node(node->right, data);
        return;
    }

}

void tree_clear(struct Tree* node){
    if(node->left != NULL)
        tree_clear(node->left);
    if(node->right != NULL)
        tree_clear(node->right);
    free(node);
}
void  infoOutput ( struct Student *student){
    printf("Фамилия: %s\n", student->surname);
    printf("Имя: %s\n", student->name);
    printf("Пол %s\n",student->sex);
    printf("Возраст: %d\n",student->age);
    printf("Группа: %d\n",student->group);
    printf("Отметка по математике: %f\n",student->mathMark);
    printf("Отметка по физеке: %f\n", student->physicsMark);
    printf("Отметка по химии: %f\n",student->chemistryMark);
}

struct Student* initstudent(char *surname, char *name, char *sex, int age,int group,float mathMark,float physickMark,float chemistryMark){
    struct Student* result = malloc(sizeof(struct Student));
    result->surname = surname;
    result->name = name;
    result->sex =  sex;
    result->age = age;
    result->group = group;
    result->mathMark = mathMark;
    result->physicsMark = physickMark;
    result->chemistryMark = chemistryMark;
    result->infoOutput = infoOutput;
    return  result;
}
void filter_students(struct Tree* node, int min_age, int max_age) {
    if (node == NULL) {
        return;
    }

    filter_students(node->left, min_age, max_age);

    if (node->data.age >= min_age && node->data.age <= max_age) {
        node->data.infoOutput(&node->data);
    }

    filter_students(node->right, min_age, max_age);
}


int main(){
    system("chcp 65001");
    struct Student* one = initstudent("test2", "test2", "m", 14, 207, 5.0, 5.0, 5.0);
    struct Student* two = initstudent("test2", "test2", "m", 16, 207, 5.0, 5.0, 2.2);
    struct Student* three = initstudent("test3", "test3", "m", 18, 207, 5.0, 5.0, 5.0);

    struct Tree* students = tree_init(*one);
    students->add_node(students, *two);
    students->add_node(students, *three);



    filter_students(students, 16, 18);

    students->clear(students);

    return 0;
}