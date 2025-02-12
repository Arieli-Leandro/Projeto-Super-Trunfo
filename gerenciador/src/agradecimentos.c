#include <stdio.h>
#include <stdlib.h>
#include "agradecimentos.h"
#include "estilizacao.h"

void agradecimentos_finais(){

    printf("\n");
    printf(AZUL_VIVO_NEGRITO "Este e um Projeto Final da disciplina: de Fundamentos de Programacao 2 \n");
    printf(RESET);
    printf("Ministrado pelo professor: ");
    printf(AZUL_VIVO_NEGRITO "Muriel de Souza Godoi \n");
    printf(RESET);
    printf("Desenvolvido com muito carinho, cafe e ");
    printf(AZUL_VIVO_NEGRITO "bugs \n");
    printf(RESET);

    printf("\n");
    printf("Feito por: \n");
    printf(AZUL_VIVO_NEGRITO);
    printf("\n");
    printf("-> Arieli Leandro Gutierres \n");
    printf("-> Gustavo Henrique \n");
    printf("-> Gustavo Gaspar \n");
    printf(RESET);
    printf("\n");

    printf(AZUL_VIVO_NEGRITO "Muito obrigada por utilizar nosso projeto!! \n");
    printf(RESET);
    
    return;

}