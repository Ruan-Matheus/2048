#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "fila_dinamica.h"
#include "arquivo.h"
#include "tabuleiro.h"

#define NOME_ARQUIVO "perfis.dat"

void jogarJogo() {
    Perfil jogador;
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int pontuacao = 0;
    time_t tInicio, tFinal;
    double tempoTotal;
    bool gameNotOver = true;
    srand(time(NULL));

    if (perfilAtivo[0] == '\0') {
        printf("Nenhum perfil ativo. Por favor, selecione um perfil primeiro.\n");
        return;
    }
    strcpy(jogador.nome, perfilAtivo);

    criarTabuleiro(tabuleiro);
    exibirTabuleiro(tabuleiro, pontuacao);

    tInicio = time(NULL);
    while (gameNotOver) {    
        char movimento;
        printf("Seu movimento: ");
        scanf(" %c", &movimento);
        getchar();

        switch (movimento) {
            case 'w':
                somandoMatrizCima(tabuleiro, &pontuacao);
                break;
            case 'a':
                somandoMatrizEsquerda(tabuleiro, &pontuacao);
                break;
            case 'd':
                somandoMatrizParaDireita(tabuleiro, &pontuacao);
                break;
            case 's':
                somandoMatrizBaixo(tabuleiro, &pontuacao);
                break;
            case 'q':
                puts("Fechando o jogo...");
                gameNotOver = false;
                break;
            default:
                puts("Movimento invalido!");
                break;
        }
        exibirTabuleiro(tabuleiro, pontuacao);

        if (!HaEspacoDisponivel(tabuleiro)) {
            gameNotOver = false;
        }
    } 
    tFinal = time(NULL);
    tempoTotal = ((double)(tFinal - tInicio));
    
    // Atualiza a pontuacao
    jogador.pontuacaoMaxima = pontuacao;
    jogador.pontuacaoMaximaSegundo = pontuacao / tempoTotal;

    atualizaArquivo(jogador);

    puts("Game over!");
    printf("Tempo de jogo: %.0fs\n", tempoTotal);
    
    printf("nome: %s\npontos: %d, pontos/s: %.0f\n\n", jogador.nome, jogador.pontuacaoMaxima, jogador.pontuacaoMaximaSegundo);
}


void sair() {
    puts("Saindo...\n");
}


int main() {
    char escolha;

    //Verifica se o arquivo existe, antes de ler.
    FILE* arquivo = fopen(NOME_ARQUIVO, "ab+");
    fclose(arquivo);

    do {
        printf("\n===== MENU =====\n");
        printf("1. Jogar\n");
        printf("2. Perfis\n");
        printf("3. Sair\n");
        printf("\nEscolha: ");
        scanf(" %c", &escolha);
        getchar();

        switch (escolha) {
            case '1':
                jogarJogo();
                break;
            case '2':
                menuPerfis();
                break;
            case '3':
                sair();
                break;
            default:
                puts("Escolha invalida! Tente novamente.");
                break;
        }
    } while (escolha != '3');

    return 0;
}   