#ifndef TABULEIRO_H
#define TABULEIRO_H

#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"

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
