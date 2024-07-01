#include <stdlib.h>
#include <stdio.h>
#include "bubble_sort.h"


void troca(Perfil *p1, Perfil *p2) {
    Perfil temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}


void bolha(Perfil v[], int tam, bool tempo){
    int ult, i;

    for (ult=tam-1; ult>0; ult--) {
        for (i=0; i<ult; i++) {
            if (tempo) {
                if (v[i].pontuacaoMaximaSegundo < v[i+1].pontuacaoMaximaSegundo) {
                    troca(&v[i], &v[i+1]); 
                }
            }
            else {
                if (v[i].pontuacaoMaxima < v[i+1].pontuacaoMaxima) {
                    troca(&v[i], &v[i+1]); 
                }
            }
        }
    }
}


void exibirRanking(int max, bool segundo) {
    FILE* arquivo;
    Perfil SAVE[256];
    
    arquivo = fopen(NOME_ARQUIVO, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s", NOME_ARQUIVO);
        return;
    }

    int i = 0;
    while (fread(&SAVE[i++], sizeof(Perfil), 1, arquivo)) {}
    fclose(arquivo);

    bolha(SAVE, i, segundo);

    puts("\n=========================== RANKING ===========================\n");
    printf("%-5s %-12s %-20s %s\n", "RANK", "NOME", "PONTUACAO MAXIMA", "PONTUACAO POR SEGUNDO");
    puts("--------------------------------------------------------------");
    for (int j = 0; j < max && j < i; j++) {
        printf("%-5d %-12s %-20d %.2f\n", j + 1, SAVE[j].nome, SAVE[j].pontuacaoMaxima, SAVE[j].pontuacaoMaximaSegundo);
    }
    puts("==============================================================\n");
}
