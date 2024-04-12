#include "stack.h"
#include <stdlib.h>



void push_stack(void* arg) {
    struct {
        struct Stack* stack;
        void* elem;
    } *args = arg;

    struct Node* new_head = malloc(sizeof(struct Node));
    if(new_head == NULL){
        perror("Ошибка при выделении памяти для Node");
        exit(1);
    }
    new_head->data = *((struct Student*)args->elem);
    new_head->next = args->stack->head;
    args->stack->head = new_head;
    args->stack->size += 1;
}

void* pop_stack(void* stack) {
    struct Stack* s = (struct Stack*)stack;
    if (s->size == 0) {
        return NULL;
    }
    struct Node* elem = s->head;
    struct Student* result = malloc(sizeof(struct Student));
    if(result == NULL){
        perror("Ошибка при выделении памяти для студента");
        exit(1);
    }
    *result = s->head->data;
    s->head = s->head->next;
    s->size -= 1;
    free(elem);
    return result;
}
struct Stack* init() {
    struct Stack* res = malloc(sizeof(struct Stack));
    if(res == NULL){
        perror("Ошибка при создании стека");
        exit(1);
    }
    res->head = NULL;
    res->size = 0;
    return res;
}


