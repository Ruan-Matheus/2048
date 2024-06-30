#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_NOME 4 // 3 Caracter de nome + \0
#define true 1
#define false 0

typedef int bool;
typedef struct {
    char nome[TAMANHO_NOME];
    int pontuacaoMaxima;
    float pontuacaoMaximaSegundo;
} Perfil;


void atualizaArquivo(char* arquivoNome, Perfil jogador) {
    FILE* arquivo;
    Perfil atual;
    bool jogadorEncontrado = false;

    arquivo = fopen(arquivoNome, "rb+");
    if (!arquivo) {
        puts("Erro ao atualizar o arquivo de save!");
        return;
    }
    while (fread(&atual, sizeof(Perfil), 1, arquivo) == 1) {
        // O perfil existe, e foi encontrado
        if (strcmp(atual.nome, jogador.nome) == 0) { 
            if (jogador.pontuacaoMaxima > atual.pontuacaoMaxima) {
                fseek(arquivo, -sizeof(Perfil), SEEK_CUR);
                fwrite(&jogador, sizeof(Perfil), 1, arquivo);
                fseek(arquivo, 0, SEEK_CUR);
                printf("Perfil atualizado: %s\n", jogador.nome);
            }
            jogadorEncontrado = true;
            break;
        // Se o jogador foi encontrado, e sua pontuacao foi menor, a pontuacao nao e salva
        }
    }
    // Perfil não existe, adicionando ao final do arquivo
    if (!jogadorEncontrado) {
        fseek(arquivo, 0, SEEK_END);
        fwrite(&jogador, sizeof(Perfil), 1, arquivo);
    }
    fclose(arquivo);
    return;
}


void exibeArquivo(char* arquivoNome) {
    FILE* arquivo;
    Perfil temp;
    arquivo = fopen(arquivoNome, "rb");
    
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
    FILE* arquivo = fopen(arquivoNome, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s\n", arquivoNome);
        return;
    }

    Perfil jogador;
    puts("\n=========================== PERFIS ===========================\n");
    printf("NOME\t\tPONTUACAO MAXIMA \tPONTUACAO POR SEGUNDO\n");
    while (fread(&jogador, sizeof(Perfil), 1, arquivo) == 1) {
        printf("%-10s\t%-18d\t%.0f\n", jogador.nome, jogador.pontuacaoMaxima, jogador.pontuacaoMaximaSegundo);
    }

    fclose(arquivo);
}