#ifndef STACK_H
#define STACK_H

#include "student.h"

struct Node {
    struct Student data;
    struct Node* next;
};

struct Stack {
    struct Node* head;
    unsigned long int size;
};

void push_stack(void* arg);
void* pop_stack(void* stack);
struct Stack* init();

#endif