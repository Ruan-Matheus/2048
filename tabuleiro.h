#ifndef TABULEIRO_H
#define TABULEIRO_H

#define TAMANHO_TABULEIRO 4

bool HaEspacoDisponivel(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void adicionarNovoNumero(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void criarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void somandoVetorDireita(int vet[TAMANHO_TABULEIRO], int* pontuacao);
void somandoMatrizParaDireita(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int* pontuacao);
void somandoVetorEsquerda(int vet[TAMANHO_TABULEIRO], int* pontuacao);
void somandoMatrizEsquerda(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int* pontuacao);
void somandoVetorBaixo(int tabuleiro[TAMANHO_TABULEIRO], int* pontuacao);
void somandoMatrizBaixo(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int* pontuacao);
void somandoVetorCima(int tabuleiro[TAMANHO_TABULEIRO], int* pontuacao);
void somandoMatrizCima(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int* pontuacao);
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int pontuacao);

#endif // TABULEIRO_H