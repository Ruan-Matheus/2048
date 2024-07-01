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
