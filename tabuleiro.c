#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "fila_dinamica.h"
#include "tabuleiro.h"


// Verifica se ha algum 0 na matriz
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


// Compara elementos adjacentes (linhas e colunas) e retorna verdadeiro caso sejam iguais
bool haMovimentosPossiveis(int tamanho, int tabuleiro[tamanho][tamanho]) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho - 1; j++) {
            if (tabuleiro[i][j] == tabuleiro[i][j + 1] || tabuleiro[i][j] == tabuleiro[i + 1][j]) {
                return true;
            }
        }
    }
    return false;
}


// Caso verdadeiro, o jogo ainda nao terminou.
bool jogoContinua(int tamanho, int tabuleiro[tamanho][tamanho]) {
    return (HaEspacoDisponivel(tamanho, tabuleiro) || haMovimentosPossiveis(tamanho, tabuleiro));
}


// Sorteia um numero entre 2 e 4 em uma posicao aleatoria disponivel do tabuleiro
void adicionarNovoNumero(int tamanho, int tabuleiro[tamanho][tamanho]) {
    int randomNumeroLinha;
    int randomNumeroColuna;
    
    do {
        randomNumeroLinha = (rand() % 4);
        randomNumeroColuna = (rand() % 4);
    } while (tabuleiro[randomNumeroLinha][randomNumeroColuna] != 0);

    tabuleiro[randomNumeroLinha][randomNumeroColuna] = (((rand() % 2) + 1) * 2); // 2*1 ou 2*2
}


// Cria uma matriz TAMxTAM e inicializa com 0s e uma ou duas potencias de 2.
void criarTabuleiro(int tamanho, int tabuleiro[tamanho][tamanho]) {
    int randomNumero = (rand() % 2);  // Um numero entre 1 e 2. A quantidade de não 0s no começo do jogo.
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            tabuleiro[i][j] = 0;
        }
    }
    adicionarNovoNumero(tamanho, tabuleiro);
    if (randomNumero) {
        adicionarNovoNumero(tamanho, tabuleiro);
    }
}


void somandoVetorDireita(int tamanho, int vet[tamanho], int* pontuacao) {
    FILA q;
    REGISTRO reg;
    iniciarFILA(&q);

    // Insere os elementos que não sejam 0 na fila. Elementos inseridos na ordem inversa do vetor
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


// Realiza somandoVetorDireita para cada coluna do tabuleiro. Caso alguma peca tenha sido movida, adiciona uma potencia de 2 no tabuleiro
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

    // Insere os elementos que não sejam 0 ma fila.
    for (int i = 0; i < tamanho; i++) {
        if (vet[i] != 0) {
            reg.chave = vet[i];
            inserirElementoFila(&q, reg);
        }
    }

    // Remove os elementos, combina se iguais, e devolve ao vetor
    int index = 0;
    int current, next;
    // while fila vazia
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


// Realiza somandoVetorBEsquerda para cada coluna do tabuleiro. Caso alguma peca tenha sido movida, adiciona uma potencia de 2 no tabuleiro
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


// Realiza somandoVetorBaixo para cada coluna do tabuleiro. Caso alguma peca tenha sido movida, adiciona uma potencia de 2 no tabuleiro
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


// Realiza somandoVetorCima para cada coluna do tabuleiro. Caso alguma peca tenha sido movida, adiciona uma potencia de 2 no tabuleiro
void somandoMatrizCima(int tamanho, int tabuleiro[tamanho][tamanho], int* pontuacao) {
    bool movimentoFeito = false;
    for (int i = 0; i < tamanho; i++) {
        int vet[tamanho];
        int original[tamanho];
        
        // Copia do vetor
        for (int j = 0; j < tamanho; j++) {
            vet[j] = tabuleiro[j][i];
            original[j] = tabuleiro[j][i];
        }

        somandoVetorCima(tamanho, vet, pontuacao);

        // Comparando a o vetor antes e depois do movimento
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


// Exibe o tabuleiro e pontuacao atual.
void exibirTabuleiro(int tamanho, int tabuleiro[tamanho][tamanho], int pontuacao) { 
    printf("PONTOS: %d\n\n", pontuacao);
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" %4d ", tabuleiro[i][j]);
            } else {
                printf(ROXO " %4d " FIM_COR, tabuleiro[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}