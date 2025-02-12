#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "STlogica.h"

#define MJOGADORES 2

CartaId *carregarCartas(const char *nomeArquivo, int *totalCartas)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo de cartas");
        return NULL;
    }

    // conta quantidade de cartas no arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    rewind(arquivo);

    *totalCartas = tamanhoArquivo / sizeof(Carta);

    if (*totalCartas <= 0)
    {
        perror("Nenhuma carta encontrada no arquivo.\n");
        fclose(arquivo);
        return NULL;
    }

    // Alocar memória para as cartas e carregar os dados
    Carta *cartas = (Carta *)malloc(tamanhoArquivo);
    if (!cartas)
    {
        perror("Erro ao alocar memória para as cartas");
        exit(1);
    }

    fread(cartas, sizeof(Carta), *totalCartas, arquivo);
    fclose(arquivo);
    // passa cartas para cartasID
    CartaId *cartasid = (CartaId *)malloc(sizeof(CartaId) * (*totalCartas));
    for (int i = 0; i < *totalCartas; i++)
    {
        snprintf(cartasid[i].nome, sizeof(cartasid[i].nome), "%s", cartas[i].nome);
        cartasid[i].numeroClassificacao = cartas[i].numeroClassificacao;
        cartasid[i].letraClassificacao = cartas[i].letraClassificacao;
        cartasid[i].superTrunfo = cartas[i].superTrunfo;
        cartasid[i].fight = cartas[i].fight;
        cartasid[i].iq = cartas[i].iq;
        cartasid[i].danger = cartas[i].danger;
        cartasid[i].mercy = cartas[i].mercy;
        cartasid[i].imgid = -1;
    }
    free(cartas);

    return cartasid;
}

bool embaralharCartas(CartaId *cartas, int totalCartas)
{
    bool finalizado = false;
    srand(time(NULL));

    for (int i = 0; i < totalCartas; i++)
    {
        int j = rand() % totalCartas;
        CartaId swap = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = swap;
    }

    finalizado = !finalizado;
    return finalizado;
}

bool distribuirCartas(CartaId *cartas, int totalCartas, Jogador *jogadores, int numJogadores)
{
    bool finalizado = false;
    int cartasPorJogador = totalCartas / numJogadores;

    for (int i = 0; i < numJogadores; i++)
    {
        jogadores[i].cartasRestantes = cartasPorJogador;
        jogadores[i].mao = (CartaId *)malloc(totalCartas * sizeof(CartaId));
        for (int j = 0; j < cartasPorJogador; j++)
        {
            jogadores[i].mao[j] = cartas[i * cartasPorJogador + j];
        }
    }

    finalizado = !finalizado;
    return finalizado;
}

int resolverRodada(Jogador *jogadores, int numJogadores, int atributo, int indiceEmpate)
{

    int superTrunfo = -1;
    int cartaA = -1;
    int vencedor = 2;

    int *valorCarta = malloc(sizeof(int) * numJogadores);

    if (valorCarta == NULL)
    {
        perror("\n\n\nnao foi possivel alocar o ponteiro STlogica>resolverRodada \n\n\n");
    }

    for (int i = 0; i < numJogadores; i++)
    {
        if (jogadores[i].cartasRestantes > 0)
        {
            switch (atributo)
            {
            case 0:
                valorCarta[i] = jogadores[i].mao[indiceEmpate].fight;
                break;
            case 1:
                valorCarta[i] = jogadores[i].mao[indiceEmpate].iq;
                break;
            case 2:
                valorCarta[i] = jogadores[i].mao[indiceEmpate].danger;
                break;
            case 3:
                valorCarta[i] = jogadores[i].mao[indiceEmpate].mercy;
                break;
            }

            if (jogadores[i].mao[indiceEmpate].superTrunfo)
            {
                superTrunfo = i;
            }
            else if (jogadores[i].mao[indiceEmpate].letraClassificacao == 'A' && cartaA != -2)
            {
                if (cartaA == -1)
                {
                    cartaA = i;
                }
                else
                {
                    cartaA = -2;
                }
            }
        }
    }

    int maiorValor = -1;
    int empate = 0;

    for (int i = 0; i < numJogadores; i++)
    {
        if (jogadores[i].cartasRestantes > 0)
        {
            if (valorCarta[i] > maiorValor)
            {
                maiorValor = valorCarta[i];
                vencedor = i;
                empate = 0;
            }
            else if (valorCarta[i] == maiorValor)
            {
                empate = 1;
            }
        }
    }

    if (empate > 0)
    {
        vencedor = -1;
    }

    if (superTrunfo != -1)
    {
        if (cartaA > -1 && jogadores[superTrunfo].mao[indiceEmpate].letraClassificacao != 'A')
        {
            vencedor = cartaA;
        }
        else
        {
            vencedor = superTrunfo;
        }
    }

    free(valorCarta);
    return vencedor;
}

void transferirCartas(Jogador *jogadores, int indiceVencedor, int numJogadores, int indiceEmpate)
{

    for (int i = 0; i <= indiceEmpate; i++)
    {
        for (int j = 0; j < numJogadores; j++)
        {

            if (jogadores[j].cartasRestantes <= 0)
            {
                continue;
            }

            jogadores[indiceVencedor].mao[jogadores[indiceVencedor].cartasRestantes] = jogadores[j].mao[0];
            jogadores[indiceVencedor].cartasRestantes++;

            for (int k = 0; k < jogadores[j].cartasRestantes - 1; k++)
            {
                jogadores[j].mao[k] = jogadores[j].mao[k + 1];
            }

            jogadores[j].cartasRestantes--;
        }
    }
}

int verificarFimDoJogo(Jogador *jogadores, int numJogadores, int indiceEmpate)
{
    int jogadoresComCartas = 0;
    int ganhador = 0;
    for (int i = 0; i < numJogadores; i++)
    {
        if (jogadores[i].cartasRestantes > (0 + indiceEmpate))
        {
            jogadoresComCartas++;
            ganhador = i;
        }
    }
    return (jogadoresComCartas == 1 ? ganhador : -1);
}

void gerarRelatorioCsv(Jogador *jogadores, int numJogadores, const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo)
    {
        perror("Erro ao abrir arquivo csv");
        return;
    }

    fprintf(arquivo, "Jogador,Cartas Restantes\n");
    for (int i = 0; i < numJogadores; i++)
    {
        fprintf(arquivo, "%s,%d\n", jogadores[i].nome, jogadores[i].cartasRestantes);
    }

    fclose(arquivo);

    printf("Relatório gerado: %s\n", nomeArquivo);
}
int bot(Jogador *jogador)
{
    srand(time(NULL));
    int dificulde = jogador->bot;
    switch (dificulde)
    {
    case 0:
        return (rand() % 4);
        break;
    case 1:
        if ((rand() % 2) == 0)
        {
            return (rand() % 4);
        }
        else
        {
            int maiorValor = 0;
            int indexValor = 0;

            if (jogador->mao[0].fight >= maiorValor)
            {
                maiorValor = jogador->mao[0].fight;
                indexValor = 0;
            }
            if (jogador->mao[0].iq >= maiorValor)
            {
                maiorValor = jogador->mao[0].iq;
                indexValor = 1;
            }
            if (jogador->mao[0].danger >= maiorValor)
            {
                maiorValor = jogador->mao[0].danger;
                indexValor = 2;
            }
            if (jogador->mao[0].mercy >= maiorValor)
            {
                maiorValor = jogador->mao[0].mercy;
                indexValor = 3;
            }
            return indexValor;
        }
        break;
    case 2:
        int maiorValor = 0;
        int indexValor = 0;

        if (jogador->mao[0].fight >= maiorValor)
        {
            maiorValor = jogador->mao[0].fight;
            indexValor = 0;
        }
        if (jogador->mao[0].iq >= maiorValor)
        {
            maiorValor = jogador->mao[0].iq;
            indexValor = 1;
        }
        if (jogador->mao[0].danger >= maiorValor)
        {
            maiorValor = jogador->mao[0].danger;
            indexValor = 2;
        }
        if (jogador->mao[0].mercy >= maiorValor)
        {
            maiorValor = jogador->mao[0].mercy;
            indexValor = 3;
        }
        return indexValor;
        break;
    default:
        return 3;
        break;
    }
}

void liberarMemoria(Jogador *jogadores, int numJogadores, CartaId *cartas)
{
    for (int i = 0; i < numJogadores; i++)
    {
        free(jogadores[i].mao);
    }
    free(cartas);
}
