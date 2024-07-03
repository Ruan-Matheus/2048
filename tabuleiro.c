#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fila_dinamica.h"
#include "tabuleiro.h"

bool HaEspacoDisponivel(int tamanho, int tabuleiro[tamanho][tamanho]) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (tabuleiro[i][j] == 0) {
                return true;
            }
        }
    }
    return false;
}


bool haMovimentosPossiveis(int tamanho, int tabuleiro[tamanho][tamanho]) {
    // Verifica movimentos horizontais
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho - 1; j++) {
            if (tabuleiro[i][j] == tabuleiro[i][j + 1]) {
                return true;
            }
        }
    }
    // Verifica movimentos verticais
    for (int j = 0; j < tamanho; j++) {
        for (int i = 0; i < tamanho - 1; i++) {
            if (tabuleiro[i][j] == tabuleiro[i + 1][j]) {
                return true;
            }
        }
    }
    return false;
}


bool jogoContinua(int tamanho, int tabuleiro[tamanho][tamanho]) {
    return (HaEspacoDisponivel(tamanho, tabuleiro) || haMovimentosPossiveis(tamanho, tabuleiro));
}


void adicionarNovoNumero(int tamanho, int tabuleiro[tamanho][tamanho]) {
    int randomNumeroLinha;
    int randomNumeroColuna;
    
    do {
        randomNumeroLinha = (rand() % 4);
        randomNumeroColuna = (rand() % 4);
    } while (tabuleiro[randomNumeroLinha][randomNumeroColuna] != 0);

    tabuleiro[randomNumeroLinha][randomNumeroColuna] = (int)pow(2, ((rand() % 2) + 1)); // 2**1 ou 2**2
}


void criarTabuleiro(int tamanho, int tabuleiro[tamanho][tamanho]) {
    int randomNumero = (rand() % 2) + 1;  // Um numero entre 1 e 2. A quantidade de não 0s no começo do jogo.
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    adicionarNovoNumero(tamanho, tabuleiro);
    if (randomNumero == 2) {
        adicionarNovoNumero(tamanho, tabuleiro);
    }
}


void somandoVetorDireita(int tamanho, int vet[tamanho], int* pontuacao) {
    FILA q;
    REGISTRO reg;
    iniciarFILA(&q);

    // Insere os elementos que não sejam 0
    for (int i = tamanho - 1; i >= 0; i--) {
        if (vet[i] != 0) {
            reg.chave = vet[i];
            inserirElementoFila(&q, reg);
        }
    }

    // Remove os elementos, combina se iguais, e devolve ao vetor
    int index = tamanho - 1;
    int current, next;
    while (tamanhoDaFILA(q) > 0) {
        excluirElementoFila(&q, &reg);
        current = reg.chave;
        if (tamanhoDaFILA(q) <= 0) {
             vet[index--] = current;
             break;
        }
        primeiro(q, &next);
        if (current == next) {
            vet[index--] = current + next;
            *pontuacao += current + next;
            excluirElementoFila(&q, &reg);
        } 
        else {
            vet[index--] = current;
        }
    }
    // Preechendo o resto das posições com 0s
    while (index >= 0) {
        vet[index--] = 0;
    }

    reiniciarFila(&q);
}


void somandoMatrizParaDireita(int tamanho, int tabuleiro[tamanho][tamanho], int* pontuacao) {
    bool movimentoFeito = false;
    for (int i = 0; i < tamanho; i++) {
        int original[tamanho];
        for (int j = 0; j < tamanho; j++) {
            original[j] = tabuleiro[i][j];
        }

        somandoVetorDireita(tamanho, tabuleiro[i], pontuacao);

        for (int j = 0; j < tamanho; j++) {
            if (original[j] != tabuleiro[i][j]) {
                movimentoFeito = true;
            }
        }
    }

    if (movimentoFeito) {
        adicionarNovoNumero(tamanho, tabuleiro);
    }
}


void somandoVetorEsquerda(int tamanho, int vet[tamanho], int* pontuacao) {
    FILA q;
    REGISTRO reg;
    iniciarFILA(&q);

    for (int i = 0; i < tamanho; i++) {
        if (vet[i] != 0) {
            reg.chave = vet[i];
            inserirElementoFila(&q, reg);
        }
    }

    int index = 0;
    int current, next;
    while (tamanhoDaFILA(q) > 0) {
        excluirElementoFila(&q, &reg);
        current = reg.chave;
        if (tamanhoDaFILA(q) <= 0) {
             vet[index++] = current;
             break;
        }
        primeiro(q, &next);
        if (current == next) {
            vet[index++] = current + next;
            *pontuacao += current + next;
            excluirElementoFila(&q, &reg);
        } 
        else {
            vet[index++] = current;
        }
    }
    // Completando as posições restantes com 0s
    while (index < tamanho) {
        vet[index++] = 0;
    }

    reiniciarFila(&q);
}

void somandoMatrizEsquerda(int tamanho, int tabuleiro[tamanho][tamanho], int* pontuacao) {
    bool movimentoFeito = false;
    for (int i = 0; i < tamanho; i++) {
        int original[tamanho];
        for (int j = 0; j < tamanho; j++) {
            original[j] = tabuleiro[i][j];
        }

        somandoVetorEsquerda(tamanho, tabuleiro[i], pontuacao);

        for (int j = 0; j < tamanho; j++) {
            if (original[j] != tabuleiro[i][j]) {
                movimentoFeito = true;
            }
        }
    }

    if (movimentoFeito) {
        adicionarNovoNumero(tamanho, tabuleiro);
    }
}


void somandoVetorBaixo(int tamanho, int vet[tamanho], int* pontuacao) {
    somandoVetorDireita(tamanho, vet, pontuacao);
}


void somandoMatrizBaixo(int tamanho, int tabuleiro[tamanho][tamanho], int* pontuacao) {
    bool movimentoFeito = false;
    for (int i = 0; i < tamanho; i++) {
        int vet[tamanho];
        int original[tamanho];
        for (int j = 0; j < tamanho; j++) {
            vet[j] = tabuleiro[j][i];
            original[j] = tabuleiro[j][i];
        }

        somandoVetorBaixo(tamanho, vet, pontuacao);

        for (int j = 0; j < tamanho; j++) {
            tabuleiro[j][i] = vet[j];
            if (original[j] != tabuleiro[j][i]) {
                movimentoFeito = true;
            }
        }
    }

    if (movimentoFeito) {
        adicionarNovoNumero(tamanho, tabuleiro);
    }
}


void somandoVetorCima(int tamanho, int vet[tamanho], int* pontuacao) {
    somandoVetorEsquerda(tamanho, vet, pontuacao);
}

void somandoMatrizCima(int tamanho, int tabuleiro[tamanho][tamanho], int* pontuacao) {
    bool movimentoFeito = false;
    for (int i = 0; i < tamanho; i++) {
        int vet[tamanho];
        int original[tamanho];
        for (int j = 0; j < tamanho; j++) {
            vet[j] = tabuleiro[j][i];
            original[j] = tabuleiro[j][i];
        }

        somandoVetorCima(tamanho, vet, pontuacao);

        for (int j = 0; j < tamanho; j++) {
            tabuleiro[j][i] = vet[j];
            if (original[j] != tabuleiro[j][i]) {
                movimentoFeito = true;
            }
        }
    }

    if (movimentoFeito) {
        adicionarNovoNumero(tamanho, tabuleiro);
    }
}


void exibirTabuleiro(int tamanho, int tabuleiro[tamanho][tamanho], int pontuacao) {
    printf("PONTOS: %d\n\n", pontuacao);
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" %4d ", tabuleiro[i][j]);
            } else {
                printf(COLOR_BOLD " %4d " COLOR_OFF, tabuleiro[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}