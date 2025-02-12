#ifndef BIBLIOTECA_PROJETO
#define BIBLIOTECA_PROJETO
#include <stdbool.h>

typedef struct{

    char nome[41];
    int numero_classificacao;
    char letra_classificacao;
    bool carta_super_trunfo;
    int fight;
    int iq;
    int danger;
    int mercy;

} Carta; 
void abrirJogo(const char *executavelDoJogo, char *nome_usuario, int dificuldade);

void som_beep(int tipo_beep);

Carta* inserir_carta(Carta *deck_super_trunfo, int *tamanho_adaptavel);

void exibe_todas_cartas(Carta *deck_super_trunfo, int *tamanho_adaptado);

void altera_todas_cartas(Carta deck_super_trunfo[], int *tamanho_adaptado);

void procura_carta_caracteristica(Carta deck_super_trunfo[], int *tamanho_adaptado);

void procura_carta_atributo(Carta deck_super_trunfo[], int *tamanho_adaptado);

#endif