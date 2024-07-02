#ifndef ARQUIVO_H
#define ARQUIVO_H

#define TAMANHO_NOME 4 // 3 Caracter de nome + \0
#define NOME_ARQUIVO "perfis.dat"
#define BUFFER_SIZE 256
#define true 1
#define false 0

typedef int bool;

typedef struct {
    char nome[TAMANHO_NOME];
    int pontuacaoMaxima;
    float pontuacaoMaximaSegundo;
} Perfil;

extern char perfilAtivo[TAMANHO_NOME];

void toUpper(char* string);
void atualizaArquivo(Perfil jogador);
void exibirPerfis();
void criarPerfil();
void acessarPerfil();
void excluirPerfil(); 
void excluirPerfil();
void buscarPerfil();
void exibirRanking(int max, bool segundo);
void menuPerfis();


#endif // ARQUIVO_H