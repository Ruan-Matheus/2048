#ifndef FILA_DINAMICA_H
#define FILA_DINAMICA_H

#define true 1
#define false 0

typedef int TIPODATA;
typedef int bool;

typedef struct {
    TIPODATA chave;
    // Other fields
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* next;
} ELEMENTO;

typedef struct {
    ELEMENTO* front;
    ELEMENTO* rear;
} FILA;

// Function prototypes
void iniciarFILA(FILA* q);
int tamanhoDaFILA(FILA q);
void exibirFILA(FILA q);
void inserirElementoFila(FILA* q, REGISTRO reg);
bool excluirElementoFila(FILA* q, REGISTRO* reg);
void reiniciarFila(FILA* q);
void primeiro(FILA q, int *var); // Copia o primeiro elemento da fila pra var

#endif // FILA_DINAMICA_H
