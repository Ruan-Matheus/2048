#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "queue.c"

#define true 1
#define false 0
#define BOARD_SIZE 4

typedef int bool;


bool isSpaceAvailable(int board[BOARD_SIZE][BOARD_SIZE]) {
    int space = false;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                puts("there is space available");
                return true;
            }
        }
    }
    puts("there is no space available");
    return false;
}


void putNewTile(int board[BOARD_SIZE][BOARD_SIZE]) {
    int randomNumberLine;
    int randomNumberColum;
    
    do {
        randomNumberLine = (rand() % 4);
        randomNumberColum = (rand() % 4);
    } while (board[randomNumberLine][randomNumberColum] != 0);

    board[randomNumberLine][randomNumberColum] = pow(2,((rand() % 2) + 1));
}


void createBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    int randomNumber = (rand() % 2) + 1; // A number between 1 and 2. The quantitiy of non 0 at the start.
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }
    putNewTile(board);
    if (randomNumber == 2) {
        putNewTile(board);
    }
}


void LineSumRight(int vet[BOARD_SIZE], int* score) {
    QUEUE q;
    REGISTER reg;
    startQueue(&q);

    // Enqueue non-zero elements
    for (int i = BOARD_SIZE - 1; i >= 0; i--) {
        if (vet[i] != 0) {
            reg.key = vet[i];
            enQueue(&q, reg);
        }
    }

    // Dequeue elements, combine if equal, and store back in the vector
    int index = BOARD_SIZE - 1;
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
            *score += current + next;
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


void slideBoardRight(int board[BOARD_SIZE][BOARD_SIZE], int* score) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        LineSumRight(board[i], score);
    }
    putNewTile(board);
}


void LineSumLeft(int vet[BOARD_SIZE], int* score) {
    QUEUE q;
    REGISTER reg;
    startQueue(&q);

    // Enqueue non-zero elements
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (vet[i] != 0) {
            reg.key = vet[i];
            enQueue(&q, reg);
        }
    }

    // Dequeue elements, combine if equal, and store back in the vector
    int index = 0;
    int current, next;
    while (sizeOfQueue(q) > 0) {
        deQueue(&q, &reg);
        current = reg.key;
        if (sizeOfQueue(q) <= 0) {
             vet[index++] = current;
             break;
        }
        front(q, &next);
        if (current == next) {
            vet[index++] = current + next;
            *score += current + next;
            deQueue(&q, &reg);
        } 
        else {
            vet[index++] = current;
        }
    }
    // Fill the remaining positions with zeros
    while (index < BOARD_SIZE) {
        vet[index++] = 0;
    }

    restartQueue(&q);
}


void slideBoardLeft(int board[BOARD_SIZE][BOARD_SIZE], int* score) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        LineSumLeft(board[i], score);
    }
    putNewTile(board);
}


void printBoard(int board[BOARD_SIZE][BOARD_SIZE], int score) {
    printf("Score: %d\n", score);
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main() {
    srand(time(NULL));
    int board[BOARD_SIZE][BOARD_SIZE];
    int score = 0;
    bool gameNotOver = true;
    char move;

    createBoard(board);
    printBoard(board, score);

    while (gameNotOver) {    

        printf("Your movement: ");
        scanf("%c", &move);

        switch (move) {
            case 'w':
                //sumUp(board);
                getchar();
                break;
            case 'a':
                slideBoardLeft(board, &score);
                getchar();
                break;
            case 'd':
                slideBoardRight(board, &score);
                getchar();
                break;
            case 's':
                //sumDown(board);
                getchar();
                break;
        default:
            puts("Not a valid move!");
            break;
        }
        printBoard(board, score);
        gameNotOver = isSpaceAvailable(board);
    }
    
    puts("Game over!");

    return 0;
}