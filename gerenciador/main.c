/**
 * @file proj_jogo_super_trunfo.c
 * @author Arieli, Gustavo Henrique, Gustavo Gaspar
 * @brief Parte básica do projeto super trunfo
 * @version 0.1
 * @date 2024-11-16
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "funcoes_super_trunfo.h"
#include "agradecimentos.h"
#include "estilizacao.h"
#include <time.h>



int main()
{
#ifdef _WIN32
    const char executavelDoJogo[] = ".\\bin\\undertale_trunfo.exe";
    const char caminhocsv[] = "data\\cartas.csv";
    const char caminhodat[] = "data\\dados_salvos.dat";
    const char caminhoRelatorio[] = "relatorios\\relatorio.txt";
#else
    const char executavelDoJogo[] = "bin/undertale_trunfo";
    const char caminhocsv[] = "data/cartas.csv";
    const char caminhodat[] = "data/dados_salvos.dat";
    const char caminhoRelatorio[] = "relatorios/relatorio.csv";
#endif

    Carta *deck_super_trunfo = NULL;
    char nome_usuario[20];
    int confirmacao_nome_usuario = 0;
    int dificuldade_jogo = 0;
    int i = 0;
    int tamanho_minimo_cartas = 32;
    int tamanho_digitado_usuario;
    int tamanho_adaptado = 0;
    int opcao_menu_principal = 0;
    int opcao_menu_gerenciamento = 0;
    int tipo_beep = 0;

    /**
     *
     * DESCRIÇÃO DA ABERTURA DOS ARQUIVOS;
     * Nesta parte caso na abertura do arquivo binário ele retorne um ponteiro nulo, o arquivo que vai ser aberto é o csv com uma mensagem de boas vindas,
     * mas se o ponteiro não for nulo o arquivo que vai ser aberto é o arquivo binário com uma mensagem de boas vindas de volta
     *
     */

    FILE *arq_binario = fopen(caminhodat, "rb");
    if (arq_binario == NULL)
    {
        printf("\n");
        printf(AZUL_VIVO_NEGRITO "Bem-Vindo ao Super Trunfo! \n");
        printf(RESET);
        printf("\n");

        FILE *arq = fopen(caminhocsv, "r");
        if (arq == NULL)
        {
            printf("O arquivo nao abriu \n");
            exit(1);
        }

        int linhas = 0;
        char caractere;
        while ((caractere = fgetc(arq)) != EOF)
        {
            if (caractere == '\n')
            {
                linhas++;
            }
        }

        tamanho_adaptado = linhas + 1;
        deck_super_trunfo = malloc(tamanho_adaptado * sizeof(Carta));
        if (deck_super_trunfo == NULL)
        {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }

        rewind(arq);
        while (fscanf(arq, "%[^,], %d, %c, %d, %d, %d, %d, %d\n",
                      deck_super_trunfo[i].nome,
                      &deck_super_trunfo[i].numero_classificacao,
                      &deck_super_trunfo[i].letra_classificacao,
                      (int *)&deck_super_trunfo[i].carta_super_trunfo,
                      &deck_super_trunfo[i].fight,
                      &deck_super_trunfo[i].iq,
                      &deck_super_trunfo[i].danger,
                      &deck_super_trunfo[i].mercy) == 8)
        {
            i++;
        }

        fclose(arq);
    }
    else
    {
        fseek(arq_binario, 0, SEEK_END);
        tamanho_adaptado = ftell(arq_binario) / sizeof(Carta);
        fseek(arq_binario, 0, SEEK_SET);

        printf("\n");
        printf(AZUL_VIVO_NEGRITO "Bem-Vindo de volta ao Super Trunfo! \n");
        printf(RESET);
        printf("\n ");

        deck_super_trunfo = malloc(tamanho_adaptado * sizeof(Carta));
        if (deck_super_trunfo == NULL)
        {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }

        fread(deck_super_trunfo, sizeof(Carta), tamanho_adaptado, arq_binario);
        fclose(arq_binario);
    }

    /**
     * DESCRIÇÃO DO MENU;
     * Ele começa com um menu principal dando a opção para o usuário de ir para o gerenciamento do jogo, ir para o jogo e sair do programa, ao escolher
     * a opção do modo de gerenciamento, há um submenu para que o usuário escolha a opção de gerenciamento (inserir cartas no deck, exibir todas as cartas, alterar as cartas, excluir as cartas, pesquisar as cartas por caracteristicas,
     * pesquisar as cartas por caracteristicas e exportar os dados para um arquivo csv).
     * O menu só para de repetir quando o usuário digitar a opção de saída do programa, a fim de que o usuário consiga gerenciar tudo o que ele precisar até que queira sair do programa
     *
     */

    do
    {

        do
        {

            setbuf(stdin, NULL);
            printf("Escolha uma opcao: \n");
            printf(AZUL_VIVO_NEGRITO "1");
            printf(RESET " - Modo de Gerenciamento do Jogo \n");
            printf(AZUL_VIVO_NEGRITO "2");
            printf(RESET " - Ir para o Jogo \n");
            printf(AZUL_VIVO_NEGRITO "3");
            printf(RESET " - Sair do Programa \n");
            scanf("%i", &opcao_menu_principal);

        } while (opcao_menu_principal < 1 || opcao_menu_principal > 3);

        switch (opcao_menu_principal)
        {

        case 1:

            do
            {

                setbuf(stdin, NULL);
                printf("Digite a opcao de Gerenciamento \n");
                printf(AZUL_VIVO_NEGRITO "1");
                printf(RESET " - Inserir Cartas \n");
                printf(AZUL_VIVO_NEGRITO "2");
                printf(RESET " - Exibir Cartas \n");
                printf(AZUL_VIVO_NEGRITO "3");
                printf(RESET " - Alterar Carta \n");
                printf(AZUL_VIVO_NEGRITO "4");
                printf(RESET " - Excluir Carta \n");
                printf(AZUL_VIVO_NEGRITO "5");
                printf(RESET " - Procurar Carta por Caracteristicas \n");
                printf(AZUL_VIVO_NEGRITO "6");
                printf(RESET " - Procurar Carta por Atributo \n");
                printf(AZUL_VIVO_NEGRITO "7");
                printf(RESET " - Exportar Dados para um arquivo csv \n");
                printf(AZUL_VIVO_NEGRITO "8");
                printf(RESET " - Sair do menu de Gerenciamento Global \n");
                scanf("%i", &opcao_menu_gerenciamento);

            } while (opcao_menu_gerenciamento < 1 || opcao_menu_gerenciamento > 8);

            switch (opcao_menu_gerenciamento)
            {

            case 1:

                deck_super_trunfo = inserir_carta(deck_super_trunfo, &tamanho_adaptado);

                break;

            case 2:

                exibe_todas_cartas(deck_super_trunfo, &tamanho_adaptado);

                break;

            case 3:

                altera_todas_cartas(deck_super_trunfo, &tamanho_adaptado);

                break;

            case 4:

                printf("Digite a quantidade de cartas que deseja excluir: \n");
                scanf("%i", &tamanho_digitado_usuario);

                tamanho_adaptado = tamanho_minimo_cartas - tamanho_digitado_usuario;

                deck_super_trunfo = realloc(deck_super_trunfo, tamanho_adaptado * sizeof(Carta));

                break;

            case 5:

                procura_carta_caracteristica(deck_super_trunfo, &tamanho_adaptado);

                break;

            case 6:

                procura_carta_atributo(deck_super_trunfo, &tamanho_adaptado);

                break;

            case 7:

                FILE *arq_relatorio_texto = fopen(caminhoRelatorio, "w");

                for (i = 0; i < tamanho_adaptado; i++)
                {

                    fprintf(arq_relatorio_texto, "%s,%i,%c,%d,%i,%i,%i,%i \n", deck_super_trunfo[i].nome, deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao, deck_super_trunfo[i].carta_super_trunfo, deck_super_trunfo[i].fight, deck_super_trunfo[i].iq, deck_super_trunfo[i].danger, deck_super_trunfo[i].mercy);
                }

                fclose(arq_relatorio_texto);

                break;

            case 8:

                printf(AZUL_VIVO_NEGRITO "Obrigada por utilizar o menu de gerenciamento! \n");
                printf(RESET);

                break;
            }

            break;

        case 2:
            arq_binario = fopen(caminhodat, "wb");
            if (arq_binario == NULL)
            {
                printf("Erro ao abrir o arquivo binário para escrita.\n");
                exit(1);
            }

            fwrite(deck_super_trunfo, sizeof(Carta), tamanho_adaptado, arq_binario);
            fclose(arq_binario);

            do
            {

                setbuf(stdin, NULL);
                printf("Digite seu nome: \n");
                fgets(nome_usuario, 20, stdin);
                nome_usuario[strcspn(nome_usuario, "\n")] = '\0';
                setbuf(stdin, NULL);

                nome_usuario[0] = toupper(nome_usuario[0]);

                printf("Confirmar o nome: %s \n", nome_usuario);
                printf(AZUL_VIVO_NEGRITO "1");
                printf(RESET);
                printf(" - Sim \n");
                printf(AZUL_VIVO_NEGRITO "2");
                printf(RESET);
                printf(" - Nao \n");
                scanf("%i", &confirmacao_nome_usuario);

                if (confirmacao_nome_usuario == 2)
                {

                    tipo_beep = 3;
                    som_beep(tipo_beep);
                    printf(VERMELHO_VIVO_NEGRITO "Por favor digite seu nome novamente! \n");
                    printf(RESET);
                }

            } while (confirmacao_nome_usuario < 1 || confirmacao_nome_usuario >= 2);

            do
            {

                tipo_beep = 2;
                som_beep(tipo_beep);

                setbuf(stdin, NULL);
                printf("Digite com qual dificuldade deseja jogar: \n");
                printf(AZUL_VIVO_NEGRITO "1");
                printf(RESET);
                printf(ROXO_VIVO_NEGRITO " - Aleatorio \n");
                printf(RESET);
                printf(AZUL_VIVO_NEGRITO "2");
                printf(RESET);
                printf(ROXO_VIVO_NEGRITO " - Medio \n");
                printf(RESET);
                printf(AZUL_VIVO_NEGRITO "3");
                printf(RESET);
                printf(VERMELHO_VIVO_NEGRITO " - Dificil \n");
                printf(RESET);
                scanf("%i", &dificuldade_jogo);

            } while (dificuldade_jogo < 1 || dificuldade_jogo > 3);

            if (dificuldade_jogo == 1)
            {

                tipo_beep = 1 + (rand() % 4);
                som_beep(tipo_beep);
            }
            else if (dificuldade_jogo == 2)
            {

                tipo_beep = 2;
                som_beep(tipo_beep);
            }
            else if (dificuldade_jogo == 3)
            {

                tipo_beep = 3;
                som_beep(tipo_beep);
            }
            abrirJogo(executavelDoJogo, nome_usuario, dificuldade_jogo - 1);

            break;

        case 3:

            printf(AZUL_VIVO_NEGRITO "Obrigada por utilizar nosso programa! \n");
            printf(RESET);

            break;
        }

    } while (opcao_menu_principal != 3);

    agradecimentos_finais();

    /* Salva as alterações que foram feitas no arquivo binário, fecha o arquivo e libera a memória alocada do vetor de struct */

    arq_binario = fopen(caminhodat, "wb");
    if (arq_binario == NULL)
    {
        printf("Erro ao abrir o arquivo binário para escrita.\n");
        exit(1);
    }

    fwrite(deck_super_trunfo, sizeof(Carta), tamanho_adaptado, arq_binario);
    fclose(arq_binario);

    free(deck_super_trunfo);

    return 0;
}