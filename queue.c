#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef int TYPEDATA;
typedef int bool;

typedef struct {
    TYPEDATA key;
    // Others fields
} REGISTER;


typedef struct aux {
    REGISTER reg;
    struct aux* next;
} ELEMENT;


typedef struct {
    ELEMENT* front;
    ELEMENT* rear;
} QUEUE;


void startQueue(QUEUE* q) {
    q->front = NULL;
    q->rear = NULL;
}


int sizeOfQueue(QUEUE q) {
    ELEMENT* current = q.front;
    int cont = 0;
    while (current != NULL) {
        cont++;
        current = current->next;
    }
    return cont;
}


void printQueue(QUEUE q) {
    ELEMENT* current = q.front;
    while (current != NULL) {
        printf("%d ", current->reg.key);
        current = current->next;
    }
    printf("\n");
}


void enQueue(QUEUE* q, REGISTER reg) {
    ELEMENT* new = malloc(sizeof(ELEMENT));
    if (!new) {
        puts("Error allocating memory!");
        return;
    }
    new->reg = reg;
    new->next = NULL;

    if (q->front == NULL) {
        q->front = new;
        q->rear = new;
    }
    else {
        q->rear->next = new;
        q->rear = new;
    }
}


bool deQueue(QUEUE* q, REGISTER* reg) {
    if (q->front == NULL) {
        return false;
    }
    ELEMENT* clean = q->front;
    *reg = q->front->reg;
    q->front = q->front->next;
    free(clean);
    clean = NULL;
    return true;
}


void restartQueue(QUEUE* q) {
    ELEMENT* current = q->front;
    ELEMENT* clean;
    while (current != NULL) {
        clean = current;
        current = current->next;
        free(clean);
        clean = NULL;
    }
    q->front = NULL;
    q->rear = NULL;
}


QUEUE arrayToQueue(int* array, int size) {
    QUEUE q;
    REGISTER reg;
    startQueue(&q);
    
    for (int i = 0; i < size; i++) {
        reg.key = array[i];
        enQueue(&q, reg);
    }
    return q;
}


void front(QUEUE q, int *var) {
    if (q.front == NULL) {
        *var = 0;
        return;
    }
    *var = q.front->reg.key;
}