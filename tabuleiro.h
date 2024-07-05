#ifndef TABULEIRO_H
#define TABULEIRO_H

#define FIM_COR "\e[m"
#define BRANCO "\e[1m"
#define VERMELHO "\e[31m "
#define VERDE "\e[32m"
#define AMARELO "\e[33m"
#define AZUL "\e[34m"
#define ROXO "\e[35m"
#define CIANO "\e[36m"
#define CINZA "\e[37"


bool HaEspacoDisponivel(int tamanho, int tabuleiro[tamanho][tamanho]);
bool haMovimentosPossiveis(int tamanho, int tabuleiro[tamanho][tamanho]);
bool jogoContinua(int tamanho, int tabuleiro[tamanho][tamanho]);
void adicionarNovoNumero(int tamanho, int tabuleiro[tamanho][tamanho]);
void criarTabuleiro(int tamanho, int tabuleiro[tamanho][tamanho]);
void somandoVetorDireita(int tamanho, int vet[tamanho], int* pontuacao);
void somandoMatrizParaDireita(int tamanho, int tabuleiro[tamanho][tamanho], int* pontuacao);
void somandoVetorEsquerda(int tamanho, int vet[tamanho], int* pontuacao);
void somandoMatrizEsquerda(int tamanho, int tabuleiro[tamanho][tamanho], int* pontuacao);
void somandoVetorBaixo(int tamanho, int vet[tamanho], int* pontuacao);
void somandoMatrizBaixo(int tamanho, int tabuleiro[tamanho][tamanho], int* pontuacao);
void somandoVetorCima(int tamanho, int vet[tamanho], int* pontuacao);
void somandoMatrizCima(int tamanho, int tabuleiro[tamanho][tamanho], int* pontuacao);
void exibirTabuleiro(int tamanho, int tabuleiro[tamanho][tamanho], int pontuacao);

#endif // TABULEIRO_H
