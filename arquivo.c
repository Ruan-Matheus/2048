#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivo.h"
#include "bubble_sort.h"

char perfilAtivo[TAMANHO_NOME] = ""; // Variavel gloval para armazenar o nome do perfil ativo

void toUpper(char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] >= 'a' && string[i] <= 'z') {
            string[i] -= 32;
        }
    }
} 


bool nomeValido(char nome[]) {
    if (nome[0] == '\0') {
        return false;
    }
    for (int i = 0; nome[i] != '\0'; i++) {
        if (nome[i] < 'A' || nome[i] > 'Z') {
            return false;
        }
    }
    return true;
}


void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}


void lerNome(char* string, char nomePerfil[]) {
    printf("\n%s", string);
    fgets(nomePerfil, TAMANHO_NOME, stdin);
    // Verifica se o buffer está limpo
    int len = strlen(nomePerfil);
    if (len > 0 && nomePerfil[len - 1] == '\n') {
        nomePerfil[len - 1] = '\0'; // Remove o caractere de nova linha
    } else {
        // Esvazia o buffer se o nome for muito longo
        limparBuffer();
    }
    toUpper(nomePerfil);
}


void atualizaArquivo(Perfil jogador) {
    FILE* arquivo;
    Perfil atual;
    bool jogadorEncontrado = false;

    arquivo = fopen(NOME_ARQUIVO, "rb+");
    if (!arquivo) {
        puts("Erro ao abir o arquivo de save!");
        return;
    }
    while (fread(&atual, sizeof(Perfil), 1, arquivo) == 1) {
        // O perfil existe, e foi encontrado
        if (strcmp(atual.nome, jogador.nome) == 0) { 
            if (jogador.pontuacaoMaxima > atual.pontuacaoMaxima) {
                fseek(arquivo, (-1) * sizeof(Perfil), SEEK_CUR);
                fwrite(&jogador, sizeof(Perfil), 1, arquivo);
                fseek(arquivo, 0, SEEK_CUR);
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


void exibirPerfis() {
    Perfil jogador;

    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s\n", NOME_ARQUIVO);
        return;
    }

    puts("\n=========================== PERFIS ===========================\n");
    printf("NOME\t\tPONTUACAO MAXIMA \tPONTUACAO POR SEGUNDO\n");
    while (fread(&jogador, sizeof(Perfil), 1, arquivo) == 1) {
        printf("%-10s\t%-18d\t%.2f\n", jogador.nome, jogador.pontuacaoMaxima, jogador.pontuacaoMaximaSegundo);    
    }  
    puts("==============================================================\n");

    fclose(arquivo);
    return;
}


void criarPerfil() {
    FILE* arquivo;
    Perfil novo, temp;
    bool perfilJaExistente = false;
    bool nomeEValido;

    do {
        lerNome("Digite o nome do Perfil a ser criado: ", novo.nome);
        nomeEValido = nomeValido(novo.nome);
        if (!nomeEValido) {
            printf("Nome invalido! Apenas letras de A-Z.\n");
        }
    } while (!nomeEValido); // Validando o nome do perfil

    novo.pontuacaoMaxima = 0;
    novo.pontuacaoMaximaSegundo = 0;
  
    arquivo = fopen(NOME_ARQUIVO, "rb+");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo: %s", NOME_ARQUIVO);
        return;
    }
    while (fread(&temp, sizeof(Perfil), 1, arquivo) == 1) {
        if (strcmp(temp.nome, novo.nome) == 0) { // Perfil ja existe
            perfilJaExistente = true;
            break;
        }
    }
    if (perfilJaExistente) {
        printf("Perfil ja existe! Tente outro nome.\n");
    }
    else {
        fwrite(&novo, sizeof(Perfil), 1, arquivo);
        strcpy(perfilAtivo, novo.nome); //  O perfil ativo sera o perfil criado
        printf("Perfil criado e ativado com sucesso!\n");
    }
    fclose(arquivo);
}


// Acessa o perfil desejado, caso ele exista
void acessarPerfil() {
    FILE* arquivo;
    Perfil temp;
    bool perfilJaExistente = false;
    char nomeAcesso[TAMANHO_NOME];

    lerNome("Digite o nome do perfil a ser acessado: ", nomeAcesso);

    arquivo = fopen(NOME_ARQUIVO, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo: %s", NOME_ARQUIVO);
        return;
    }

    while (fread(&temp, sizeof(Perfil), 1, arquivo) == 1) {
        if (strcmp(temp.nome, nomeAcesso) == 0) { // Perfil encontrado
            perfilJaExistente = true;
            break;
        }
    }

    fclose(arquivo);
    
    if (perfilJaExistente) {
        strcpy(perfilAtivo, nomeAcesso);
        printf("Perfil %s acessado com sucesso\n", perfilAtivo);
    }
    else {
        printf("Perfil nao existe, tente acessar/criar outro perfil.\n");
    }
}


void excluirPerfil() {
    FILE *arquivo;
    Perfil *SAVES;
    Perfil temp;
    bool perfilEncontrado = false;
    char nomePerfil[TAMANHO_NOME];
    int i = 0, bufferSize = 20;

    lerNome("Digite o nome do Perfil a ser excluido: ", nomePerfil);

    // Verifica se o perfil a ser excluído está ativo
    if (strcmp(perfilAtivo, nomePerfil) == 0) {
        printf("Erro: Nao e possivel excluir o perfil ativo.\n");
        return;
    }
    
    arquivo = fopen(NOME_ARQUIVO, "rb+");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s\n", NOME_ARQUIVO);
        return;
    }

    SAVES = malloc(bufferSize * sizeof(Perfil));
    if (!SAVES) {
        printf("Erro ao alocar memoria para SAVES\n");
        fclose(arquivo);
        return;
    }

    while (fread(&temp, sizeof(Perfil), 1, arquivo) == 1) {
        if (strcmp(temp.nome, nomePerfil) != 0) {

            // Vetor atingiu o limite de tamanho. Dobrando seu tamanho.
            if (i >= bufferSize) {
                bufferSize *= 2;
                SAVES = realloc(SAVES, bufferSize * sizeof(Perfil));
                if (!SAVES) {
                    printf("Erro ao realocar memoria!\n");
                    fclose(arquivo);
                    return;
                }
            }

            // Copiandos os perfis diferentes daquele a seer excluido
            SAVES[i] = temp;
            i++;
        }
        else {
            perfilEncontrado = true;
        }
    }
    fclose(arquivo);

    if (perfilEncontrado) {
        // Reabre o arquivo em modo de escrita, limpando o seu conteudo
        arquivo = fopen(NOME_ARQUIVO, "wb");
        if (!arquivo) {
            printf("Erro ao abrir o arquivo %s para escrita\n", NOME_ARQUIVO);
            free(SAVES);
            return;
        }

        for (int j = 0; j < i; j++) {
            // Reescreve o arquivo com todos os perfis menos o excluido
            fwrite(&SAVES[j], sizeof(Perfil), 1, arquivo);
        }
        fclose(arquivo);
        printf("Perfil %s excluido com sucesso.\n", nomePerfil);

    } 
    else {
        printf("Perfil %s nao encontrado.\n", nomePerfil);
    }
    free(SAVES);
}


// Exibe os atributos de perfil de um jogador caso o perfil ja exista
void buscarPerfil() {
    Perfil jogador;
    char nomeBusca[TAMANHO_NOME];
    bool perfilExistente = false;

    lerNome("Digite o nome para a busca: ", nomeBusca);

    FILE* arquivo = fopen(NOME_ARQUIVO, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s\n", NOME_ARQUIVO);
        return;
    }

    while (fread(&jogador, sizeof(Perfil), 1, arquivo) == 1) {
        if (strcmp(jogador.nome, nomeBusca) == 0) {
            perfilExistente = true;
            break;
        }
    }
    if (perfilExistente) {
        puts("\n=========================== PERFIL ===========================\n");
        printf("NOME\t\tPONTUACAO MAXIMA \tPONTUACAO POR SEGUNDO\n");
        printf("%-10s\t%-18d\t%.0f\n", jogador.nome, jogador.pontuacaoMaxima, jogador.pontuacaoMaximaSegundo);
        puts("==============================================================\n");
    }
    if (!perfilExistente) {
        printf("Perfil nao existe!\n");
    }
    fclose(arquivo);
    return;
}


// Exibe o ranking dos max jogadores com base pontos maximos ou tempo
void exibirRanking(int max, bool tempo) {
    FILE* arquivo;
    Perfil *SAVES;
    int tamanhoBuffer = 20;
    
    arquivo = fopen(NOME_ARQUIVO, "rb");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo %s", NOME_ARQUIVO);
        return;
    }

    SAVES = malloc(tamanhoBuffer * sizeof(Perfil));
    if (!SAVES) {
        printf("Erro ao alocar memoria para SAVES");
        fclose(arquivo);
        return;
    }

    int i = 0;
    while (fread(&SAVES[i], sizeof(Perfil), 1, arquivo) == 1) {
        // Vetor atingiu o limite de tamanho. Dobrando seu tamanho.
            if (i >= tamanhoBuffer) {
                tamanhoBuffer *= 2;
                SAVES = realloc(SAVES, tamanhoBuffer * sizeof(Perfil));
                if (!SAVES) {
                    printf("Erro ao realocar memoria!\n");
                    fclose(arquivo);
                    return;
                }
            }
            i++;
    }

    fclose(arquivo);
    bolha(SAVES, i, tempo);

    puts("\n=========================== RANKING ===========================\n");
    printf("%-5s %-12s %-20s %s\n", "RANK", "NOME", "PONTUACAO MAXIMA", "PONTUACAO POR SEGUNDO");
    puts("--------------------------------------------------------------");
    for (int j = 0; j < max && j < i; j++) {
        printf("%-5d %-12s %-20d %.2f\n", j + 1, SAVES[j].nome, SAVES[j].pontuacaoMaxima, SAVES[j].pontuacaoMaximaSegundo);
    }
    puts("==============================================================\n");
    free(SAVES);
}


// Menu de opcoes relacionados aos perfis
void menuPerfis() {
    int opcao;
    int nMaxRanking = 10;


    do {
        puts("\n0 - Listar Perfis");
        puts("1 - Criar Perfil");
        puts("2 - Acessar Perfil");
        puts("3 - Excluir Perfil");
        puts("4 - Buscar Perfil");
        puts("5 - Ranking - PONTUACAO MAXIMA");
        puts("6 - Ranking - PONTUACAO POR SEGUNDO");
        puts("7 - Voltar");
        printf("\nEscolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 0:
                exibirPerfis();
                break;
            case 1:
                criarPerfil();
                break;
            case 2:
                acessarPerfil();
                break;
            case 3:
                excluirPerfil();
                break;
            case 4:
                buscarPerfil();
                break;
            case 5:
                exibirRanking(nMaxRanking, false);
                break;
            case 6:
                exibirRanking(nMaxRanking, true);
                break;
            case 7:
                printf("Voltando...\n");
                break;
            default:
                puts("Escolha invalida! Tente novamente.\n");
                break;
            }
    } while (opcao != 7);

    return;
}