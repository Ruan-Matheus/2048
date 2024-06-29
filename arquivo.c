#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_NOME 4 // 3 Caracter de nome + \0

typedef struct {
    char nome[TAMANHO_NOME];
    int pontuacaoMaxima;
    float pontuacaoMaximaSegundo;
} Perfil;


void atualizaArquivo(char* arquivoNome, Perfil jogador) {
    FILE* arquivo;
    Perfil atual;

    arquivo = fopen(arquivoNome, "r+");
    if (!arquivo) {
        puts("Erro ao atualizar o arquivo de save!");
        return;
    }
    while (fread(&atual, sizeof(Perfil), 1, arquivo) == 1) {
        if (strcmp(atual.nome, jogador.nome) == 0) { // O perfil existe, e foi encontrado
            if (jogador.pontuacaoMaxima > atual.pontuacaoMaxima) {
                fseek(arquivo, -sizeof(Perfil), SEEK_CUR);
                fwrite(&jogador, sizeof(Perfil), 1, arquivo);
                fclose(arquivo);
            }
        return; // Se o jogador foi encontrado, e sua pontuacao foi menor, a pontuacao nao e salva
        }
    }
    fwrite(&jogador, sizeof(Perfil), 1, arquivo);
    fclose(arquivo);
    return;
}


void exibeArquivo(char* arquivoNome) {
    FILE* arquivo;
    Perfil temp;
    arquivo = fopen(arquivoNome, "r");
    
    if (!arquivo) {
        puts("Falha ao abrir o arquivo de save!");
        return;
    }
    while (fread(&temp, sizeof(Perfil), 1, arquivo) == 1) {
        printf("Nome: %s\nPontuacao Maxima: %d \nPontos por Segundo: %.0f\n\n", temp.nome, temp.pontuacaoMaxima, temp.pontuacaoMaximaSegundo);
    }
    fclose(arquivo);
    return;
}


void exibirPerfis(char* arquivoNome) {
    FILE* arquivo = fopen(arquivoNome, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s\n", arquivoNome);
        return;
    }

    Perfil jogador;
    puts("\n=========================== RANKING ===========================\n");
    printf("NOME\t\tPONTUACAO MAXIMA \tPONTUACAO POR SEGUNDO\n");
    while (fread(&jogador, sizeof(Perfil), 1, arquivo) == 1) {
        printf("%-10s\t%-18d\t%.0f\n", jogador.nome, jogador.pontuacaoMaxima, jogador.pontuacaoMaximaSegundo);
    }

    fclose(arquivo);
}