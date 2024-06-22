#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fila_dinamica.c"

#define TAMANHO_TABULEIRO 4


bool HaEspacoDisponivel(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) {
                puts("Ha espaco disponivel");
                return true;
            }
        }
    }
    puts("Nao ha espaco disponivel");
    return false;
}


void adicionarNovoNumero(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int randomNumeroLinha;
    int randomNumeroColuna;
    
    do {
        randomNumeroLinha = (rand() % 4);
        randomNumeroColuna = (rand() % 4);
    } while (tabuleiro[randomNumeroLinha][randomNumeroColuna] != 0);

    tabuleiro[randomNumeroLinha][randomNumeroColuna] = pow(2,((rand() % 2) + 1)); // 2**1 ou 2**2
}


void criarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    int randomNumero = (rand() % 2) + 1;  // Um numero entre 1 e 2. A quantidade de não 0s no começo do jogo.
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    adicionarNovoNumero(tabuleiro);
    if (randomNumero == 2) {
        adicionarNovoNumero(tabuleiro);
    }
}


void somandoVetorDireita(int vet[TAMANHO_TABULEIRO], int* pontuacao) {
    FILA q;
    REGISTRO reg;
    iniciarFILA(&q);

    // Insere os elementos que não sejam 0
    for (int i = TAMANHO_TABULEIRO - 1; i >= 0; i--) {
        if (vet[i] != 0) {
            reg.chave = vet[i];
            inserirElementoFila(&q, reg);
        }
    }

    // Remove os elementos, combina se iguais, e devolve ao vetor
    int index = TAMANHO_TABULEIRO - 1;
    int current, next;
    while (tamanhoDaFILA(q) > 0) {
        excluirElementoFila(&q, &reg);
        current = reg.chave;
        if (tamanhoDaFILA(q) <= 0) {
             vet[index--] = current;
             break;
        }
        front(q, &next);
        if (current == next) {
            vet[index--] = current + next;
            *pontuacao += current + next;
            excluirElementoFila(&q, &reg);
        } 
        else {
            vet[index--] = current;
        }
    }
    // Fill the remaining positions with zeros
    while (index >= 0) {
        vet[index--] = 0;
    }

    reiniciarFila(&q);
}


void somandoMatrizParaDireita(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int* pontuacao) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        somandoVetorDireita(tabuleiro[i], pontuacao);
    }
    adicionarNovoNumero(tabuleiro);
}


void somandoVetorEsquerda(int vet[TAMANHO_TABULEIRO], int* pontuacao) {
    FILA q;
    REGISTRO reg;
    iniciarFILA(&q);

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        if (vet[i] != 0) {
            reg.chave = vet[i];
            inserirElementoFila(&q, reg);
        }
    }

    // excluirElementoFila elements, combine if equal, and store back in the vector
    int index = 0;
    int current, next;
    while (tamanhoDaFILA(q) > 0) {
        excluirElementoFila(&q, &reg);
        current = reg.chave;
        if (tamanhoDaFILA(q) <= 0) {
             vet[index++] = current;
             break;
        }
        front(q, &next);
        if (current == next) {
            vet[index++] = current + next;
            *pontuacao += current + next;
            excluirElementoFila(&q, &reg);
        } 
        else {
            vet[index++] = current;
        }
    }
    // Fill the remaining positions with zeros
    while (index < TAMANHO_TABULEIRO) {
        vet[index++] = 0;
    }

    reiniciarFila(&q);
}


void somandoMatrizEsquerda(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int* pontuacao) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        somandoVetorEsquerda(tabuleiro[i], pontuacao);
    }
    adicionarNovoNumero(tabuleiro);
}


void somandoVetorBaixo(int tabuleiro[TAMANHO_TABULEIRO], int* pontuacao) {
    somandoVetorDireita(tabuleiro, pontuacao);
}


void somandoMatrizBaixo(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int* pontuacao) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        int vet[TAMANHO_TABULEIRO];
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            vet[j] = tabuleiro[j][i];
        }
        somandoVetorBaixo(vet, pontuacao);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[j][i] = vet[j];
        }
    }
    adicionarNovoNumero(tabuleiro);
}



void somandoVetorCima(int tabuleiro[TAMANHO_TABULEIRO], int* pontuacao) {
    somandoVetorEsquerda(tabuleiro, pontuacao);
}


void somandoMatrizCima(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int* pontuacao) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        int vet[TAMANHO_TABULEIRO];
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            vet[j] = tabuleiro[j][i];
        }
        somandoVetorCima(vet, pontuacao);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[j][i] = vet[j];
        }
    }
    adicionarNovoNumero(tabuleiro);
}

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int pontuacao) {
    printf("Pontos: %d\n\n", pontuacao);
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %4d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main() {
    srand(time(NULL));
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int pontuacao = 0;
    bool gameNotOver = true;
    char movimento;

    criarTabuleiro(tabuleiro);
    exibirTabuleiro(tabuleiro, pontuacao);

    while (gameNotOver) {    

        printf("Seu movimento: ");
        scanf("%c", &movimento);

        switch (movimento) {
            case 'w':
                somandoMatrizCima(tabuleiro, &pontuacao);
                getchar();
                break;
            case 'a':
                somandoMatrizEsquerda(tabuleiro, &pontuacao);
                getchar();
                break;
            case 'd':
                somandoMatrizParaDireita(tabuleiro, &pontuacao);
                getchar();
                break;
            case 's':
                somandoMatrizBaixo(tabuleiro, &pontuacao);
                getchar();
                break;
        default:
            puts("Movimento invalido!");
            break;
        }
        exibirTabuleiro(tabuleiro, pontuacao);
        gameNotOver = HaEspacoDisponivel(tabuleiro);
    }
    
    puts("Game over!");

    return 0;
}