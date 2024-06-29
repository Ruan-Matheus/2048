#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "fila_dinamica.h"
#include "arquivo.h"
#include "tabuleiro.h"

void toUpper(char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] >= 'a' && string[i] <= 'z') {
            string[i] -= 32;
        }
    }
} 


void jogarJogo(char* arquivoNome) {
    FILE* arquivo;
    Perfil jogador;
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int pontuacao = 0;
    time_t tInicio, tFinal;
    double tempoTotal;
    bool gameNotOver = true;
    srand(time(NULL));

    puts("Digite seu nome de perfil: ");
    fgets(jogador.nome, TAMANHO_NOME, stdin);
    toUpper(jogador.nome);
    jogador.nome[strcspn(jogador.nome, "\n")] = 0; // Remove o caracter de nova linha

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

    printf("nome: %s\npontos: %d, pontos/s: %.0f\n\n", jogador.nome, jogador.pontuacaoMaxima, jogador.pontuacaoMaximaSegundo);

    atualizaArquivo(arquivoNome, jogador);

    puts("Game over!");
    printf("Tempo de jogo: %.0fs\n", tempoTotal);
}


void sair() {
    puts("Saindo...\n");
}


int main() {
    FILE* arquivo;
    char* arquivoNome = "perfis.dat";
    char escolha;

    //Verificar se o arquivo existe, antes de ler.

    do {
        printf("\n===== MENU =====\n");
        printf("1. Jogar\n");
        printf("2. Ver Perfis\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf(" %c", &escolha);
        getchar();

        switch (escolha) {
            case '1':
                jogarJogo(arquivoNome);
                break;
            case '2':
                exibirPerfis(arquivoNome);
                break;
            case '3':
                sair();
                escolha = '3';
                break;
            default:
                puts("Escolha invalida! Tente novamente.");
                break;
        }
    } while (escolha != '3');

    return 0;
}