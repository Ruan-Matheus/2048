#include <stdio.h>
#include <stdlib.h>
#include "queue.c"

#define SIZE 4

void printfArr(int vet[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void LineSumRight(int vet[SIZE]) {
    QUEUE q;
    REGISTER reg;
    startQueue(&q);

    // Enqueue non-zero elements
    for (int i = SIZE - 1; i >= 0; i--) {
        if (vet[i] != 0) {
            reg.key = vet[i];
            enQueue(&q, reg);
        }
    }

    // Dequeue elements, combine if equal, and store back in the vector
    int index = SIZE - 1;
    int current, next;
    while (sizeOfQueue(q) > 0) {
        deQueue(&q, &reg);
        current = reg.key;
        if (sizeOfQueue(q) <= 0) {
             vet[index--] = current;
             break;
        }
        front(q, &next);
        if (current == next) {
            vet[index--] = current + next;
            deQueue(&q, &reg);
        } 
        else {
            vet[index--] = current;
        }
    }
    // Fill the remaining positions with zeros
    while (index >= 0) {
        vet[index--] = 0;
    }

    restartQueue(&q);
}

void slideBoardRight(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        LineSumRight(board[i]);
    }
}


void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%4d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}


int main() {
    int board[SIZE][SIZE] = {
        {2, 2, 4, 4},
        {2, 0, 2, 0},
        {4, 4, 4, 4},
        {0, 0, 0, 2}};
    
    printBoard(board);
    slideBoardRight(board);
    printBoard(board);

    return 0;
}
