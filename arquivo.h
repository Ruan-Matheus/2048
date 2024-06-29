#ifndef ARQUIVO_H
#define ARQUIVO_H

#define TAMANHO_NOME 4 // 3 Caracter de nome + \0

typedef struct {
    char nome[TAMANHO_NOME];
    int pontuacaoMaxima;
    float pontuacaoMaximaSegundo;
} Perfil;


void atualizaArquivo(char* arquivoNome, Perfil jogador);
void exibeArquivo(char* arquivoNome);
void exibirPerfis(char* arquivoNome);


#endif // ARQUIVO_H