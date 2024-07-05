#include <stdio.h>
#include <stdlib.h>
#include "fila_dinamica.h"


void iniciarFILA(FILA* q) {
    q->front = NULL;
    q->rear = NULL;
}


int tamanhoDaFILA(FILA q) {
    ELEMENTO* current = q.front;
    int cont = 0;
    while (current != NULL) {
        cont++;
        current = current->next;
    }
    return cont;
}


void exibirFILA(FILA q) {
    ELEMENTO* current = q.front;
    while (current != NULL) {
        printf("%d ", current->reg.chave);
        current = current->next;
    }
    printf("\n");
}


void inserirElementoFila(FILA* q, REGISTRO reg) {
    ELEMENTO* new = malloc(sizeof(ELEMENTO));
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


bool excluirElementoFila(FILA* q, REGISTRO* reg) {
    if (q->front == NULL) {
        return false;
    }
    ELEMENTO* clean = q->front;
    *reg = q->front->reg;
    q->front = q->front->next;
    free(clean);
    clean = NULL;
    return true;
}


void reiniciarFila(FILA* q) {
    ELEMENTO* current = q->front;
    ELEMENTO* clean;
    while (current != NULL) {
        clean = current;
        current = current->next;
        free(clean);
        clean = NULL;
    }
    q->front = NULL;
    q->rear = NULL;
}


// Copia o valor do primeiro elemento na fila para var
void primeiro(FILA q, int *var) {
    if (q.front == NULL) {
        *var = 0;
        return;
    }
    *var = q.front->reg.chave;
}