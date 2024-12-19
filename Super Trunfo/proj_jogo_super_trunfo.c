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

// FUNÇÔES DA 1 PARTE DO CODIGO (INSERIR, EXIBIR, EXCLUIR, ALTERAR, PROCURAR CARTAS POR CARACTERISTICAS E ATRIBUTOS)
// A FUNÇÃO EXCLUIR CARTA ESTA NA MAIN

void insere_cartas(Carta deck_super_trunfo[], int tamanho_minimo_cartas, int *tamanho_adaptavel){

    /**
     * DESCRICAO DA FUNÇÃO:
     * Na main o usuario digita a quantidade de cartas que ele quer adicionar e na main acontece a realocação
     * para o aumento da alocação, é feita a chamada desta função onde é passado um ponteiro de inteiro (tamanho adaotado)
     * o tamanho minimo de cartas e o vetor de struct. A função recebe os parametros e começa a inserir o dados com o i tendo o valor da variavel 
     * tamanho_minimo_cartas para que seja inserido da carta 31 ate a carta de tamanho_adaptado (tamanho_adaptado = tamanho_minimo + tamanho_digitado_usuario)
     * a fim de ser o criterio de parada do for para que todas as cartas sejam adicionadas
    */

    int i = tamanho_minimo_cartas;

    int opcao_menu_letra_classificacao;

    int opcao_menu_carta_super_trunfo;

    for(i = tamanho_minimo_cartas; i<*tamanho_adaptavel; i++){

        setbuf(stdin, NULL);
        printf("Digite o nome da carta: \n");
        fgets(deck_super_trunfo[i].nome, 41, stdin);
        deck_super_trunfo[i].nome[strcspn(deck_super_trunfo[i].nome, "\n")] = '\0';
        setbuf(stdin, NULL);

        do{
            setbuf(stdin, NULL);
            printf("Digite o numero de classificacao da carta: \n");
            scanf("%i", &deck_super_trunfo[i].numero_classificacao);
            setbuf(stdin, NULL);

        }while(deck_super_trunfo[i].numero_classificacao < 1 || deck_super_trunfo[i].numero_classificacao > 8);

        do{

            printf("Escolha a opcao referente ao numero de classificacao da carta: \n");
            printf("1 - A \n");
            printf("2 - B \n");
            printf("3 - C \n");
            printf("4 - D \n");
            scanf("%i", &opcao_menu_letra_classificacao);

        }while(opcao_menu_letra_classificacao < 1 || opcao_menu_letra_classificacao > 4);

        switch(opcao_menu_letra_classificacao){

            case 1:

                deck_super_trunfo[i].letra_classificacao = 'A';

            break;

            case 2:

                deck_super_trunfo[i].letra_classificacao = 'B';

            break;

            case 3:

                deck_super_trunfo[i].letra_classificacao = 'C';

            break;

            case 4:

                deck_super_trunfo[i].letra_classificacao = 'D';

            break;

        }

        do{

            printf("Escolha a opcao referente a carta super trunfo: \n");
            printf("1 - A carta e um super trunfo \n");
            printf("2 - A carta nao e um super trunfo \n");
            scanf("%i", &opcao_menu_carta_super_trunfo);

        }while(opcao_menu_carta_super_trunfo < 1 || opcao_menu_carta_super_trunfo > 2);

        switch(opcao_menu_carta_super_trunfo){

            case 1:

                deck_super_trunfo[i].carta_super_trunfo = 1;

            break;

            case 2:

                deck_super_trunfo[i].carta_super_trunfo = 0;

            break;

        }

        setbuf(stdin, NULL);
        printf("Digite o Fight da carta: \n");
        scanf("%i", &deck_super_trunfo[i].fight);
        setbuf(stdin, NULL);

        setbuf(stdin, NULL);
        printf("Digite o IQ da carta: \n");
        scanf("%i", &deck_super_trunfo[i].iq);
        setbuf(stdin, NULL);

        setbuf(stdin, NULL);
        printf("Digite o Danger da carta: \n");
        scanf("%i", &deck_super_trunfo[i].danger);
        setbuf(stdin, NULL);

        setbuf(stdin, NULL);
        printf("Digite a Mercy da carta: \n");
        scanf("%i", &deck_super_trunfo[i].mercy);
        setbuf(stdin, NULL);

    }

    return;

}

void exibe_todas_cartas(Carta deck_super_trunfo[], int *tamanho_adaptavel){

    /**
     * DESCRIÇÃO DA FUNÇÃO:
     * Ela recebe o vetor de struct e um ponteiro para um inteiro (tamanho_adaptado),
     * e com o vetor e esse ponteiro é possivel exibir todas cartas de i tamanho (i = 0) até a carta tamanho_adaptado (tamanho_adaptado = tamanho_minimo + tamanho_digitado_usuario)
    */

    int i = 0;

    for(i = 0; i<*tamanho_adaptavel; i++){

        printf("\n");

        printf("Nome da carta: %s \n", deck_super_trunfo[i].nome);
        printf("Classificacao da carta: %i%c \n", deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao);

        if(deck_super_trunfo[i].carta_super_trunfo == 1 ){

            printf("A carta e um super trunfo \n");
            
        }else{

            printf("A carta nao e um super trunfo \n");
        }

        printf("Fight da carta: %i \n", deck_super_trunfo[i].fight);
        printf("IQ da carta: %i \n", deck_super_trunfo[i].iq);
        printf("Danger da carta: %i \n", deck_super_trunfo[i].danger);
        printf("Mercy da carta: %i \n", deck_super_trunfo[i].mercy);

        printf("\n");

    }

    return;

}

void altera_todas_cartas(Carta deck_super_trunfo[], int *tamanho_adaptavel){

    /**
     * DESCRIÇÃO DA FUNÇÃO:
     * Ela recebe o vetor de struct e um ponteiro  para um inteiro (tamanho_adaptado) e ela começa com um menu perguntando ao usuario qual campo da carta ele deseja alterar,
     * depois ela pergunta o indice da carta que o usuario deseja alterar e pede o valor da alteração para poder trocar, no caso do super trunfo ela verifica qual carta é o super trunfo, troca ela por 0 e coloca a carta do indice
     * que o usuario deseja alterar como o novo super trunfo, o menu é repetido até o usuário digitar que deseja sair do menu de alterações, a fim de que o usuário possa alterar todos os campos que desejar antes de sair da função
    */

    int i = 0;

    int opcao_alterar_carta;

    int opcao_altera_letra_classificacao;

    int indice_carta_alteracao = 0;

    char novo_nome_carta[41];

    char nova_letra_classificacao;

    int novo_numero_classificacao = 0;

    int novo_fight_carta = 0;

    int novo_iq_carta = 0;

    int novo_danger_carta = 0;

    int novo_mercy_carta = 0;

    do{

        do{

            printf("Digite o tipo de alteracao que deseja fazer: \n");
            printf("1 - Alterar o nome da carta \n");
            printf("2 - Alterar o numero de classificacao da carta \n");
            printf("3 - Alterar letra de classificacao da carta \n");
            printf("4 - Alterar carta super trunfo \n");
            printf("5 - Alterar Fight da carta \n");
            printf("6 - Alterar IQ da carta \n");
            printf("7 - Alterar Danger da carta \n");
            printf("8 - Alterar a Mercy da carta \n");
            printf("9 - Alteracoes concluidas (Sair do menu de alteracoes) \n");
            scanf("%i", &opcao_alterar_carta);

        }while(opcao_alterar_carta < 1 || opcao_alterar_carta > 9);

        do{

            setbuf(stdin, NULL);
            printf("Digite o indice da carta que deseja alterar: \n");
            scanf("%i", &indice_carta_alteracao);
            setbuf(stdin, NULL);

        }while(indice_carta_alteracao < 0 || indice_carta_alteracao > 31);

        printf("\n");

        switch(opcao_alterar_carta){

            case 1:

                printf("\n");

                setbuf(stdin, NULL);

                printf("Voce escolheu a opcao 'Alterar o nome da carta' \n");

                printf("\n");

                setbuf(stdin, NULL);
                printf("Digite o novo nome da carta: \n");
                fgets(novo_nome_carta, 41, stdin);
                novo_nome_carta[strcspn(novo_nome_carta, "\n")] = '\0';
                setbuf(stdin, NULL);

                strcpy(deck_super_trunfo[indice_carta_alteracao].nome, novo_nome_carta);

                printf("Alteracao feita! \n");

                setbuf(stdin, NULL);

                printf("\n");

            break;

            case 2:

                printf("\n");

                setbuf(stdin, NULL);

                printf("Voce escolheu a opcao 'Alterar o numero de classificacao da carta' \n");

                printf("\n");

                printf("Digite o novo numero da carta: \n");
                scanf("%i", &novo_numero_classificacao);

                deck_super_trunfo[indice_carta_alteracao].numero_classificacao = novo_numero_classificacao;

                printf("Alteracao feita! \n");

                setbuf(stdin, NULL);

                printf("\n");

            break;

            case 3:

                printf("\n");

                setbuf(stdin, NULL);

                printf("Voce escolheu a opcao 'Alterar letra de classificacao da carta' \n");

                printf("\n");

                do{

                    printf("Escolha a opcao da letra de classificacao da carta: \n");
                    printf("1 - A \n");
                    printf("2 - B \n");
                    printf("3 - C \n");
                    printf("4 - D \n");
                    scanf("%i", &opcao_altera_letra_classificacao);

                }while(opcao_altera_letra_classificacao < 1 || opcao_altera_letra_classificacao > 4);

                switch(opcao_altera_letra_classificacao){

                    case 1:

                        nova_letra_classificacao = 'A';

                    break;

                    case 2:

                        nova_letra_classificacao = 'B';

                    break;

                    case 3:

                        nova_letra_classificacao = 'C';

                    break;

                    case 4:

                        nova_letra_classificacao = 'D';

                    break;

                }

                deck_super_trunfo[i].letra_classificacao = nova_letra_classificacao;
                
                printf("Alteracao feita! \n");

                setbuf(stdin, NULL);

                printf("\n");

            break;

            case 4:

                printf("\n");

                setbuf(stdin, NULL);

                printf("Voce escolheu a opcao 'Alterar carta super trunfo' \n");

                printf("\n");

                for(i = 0; i<*tamanho_adaptavel; i++){

                    if(deck_super_trunfo[i].carta_super_trunfo == 1){

                        deck_super_trunfo[i].carta_super_trunfo = 0;

                    }

                }

                deck_super_trunfo[indice_carta_alteracao].carta_super_trunfo = 1;

                printf("Alteracao feita! \n");

               setbuf(stdin, NULL);

               printf("\n");

            break;

            case 5:

                printf("\n");

                printf("Voce escolheu a opcao 'Alterar Fight da carta' \n");

                printf("\n");

                printf("Digite o novo fight da carta: \n");
                scanf("%i", &novo_fight_carta);

                deck_super_trunfo[indice_carta_alteracao].fight = novo_fight_carta;

                printf("Alteracao feita! \n");

                printf("\n");

            break;

            case 6:

                printf("\n");

                printf("Voce escolheu a opcao 'Alterar IQ da carta' \n");
                
                printf("\n");

                printf("Digite o novo IQ da carta: \n");
                scanf("%i", &novo_iq_carta);

                deck_super_trunfo[indice_carta_alteracao].iq = novo_iq_carta;

                printf("Alteracao feita! \n");

                printf("\n");

            break;

            case 7:

                printf("\n");

                printf("Voce escolheu a opcao 'Alterar Danger da carta' \n");

                printf("\n");

                printf("Digite o novo Danger da carta: \n");
                scanf("%i", &novo_danger_carta);

                deck_super_trunfo[indice_carta_alteracao].danger = novo_danger_carta;

                printf("Alteracao feita! \n");

                printf("\n");

            break;

            case 8:

                printf("\n");

                printf("Voce escolheu a opcao 'Alterar a Mercy da carta' \n");

                printf("\n");

                printf("Digite a nova Mercy da carta: \n");
                scanf("%i", &novo_mercy_carta);

                deck_super_trunfo[indice_carta_alteracao].mercy = novo_mercy_carta;

                printf("Alteracao feita! \n");

                printf("\n");

            break;

            case 9:

                printf("\n");

                printf("Voce escolheu a opcao 'Alteracoes concluidas (Sair do menu de alteracoes)' \n");

                printf("\n");

                printf("Obrigada por utilizar o menu de alteracoes! \n");

                printf("\n");

            break;

        }


    }while(opcao_alterar_carta != 9);

    return;

}

void procura_carta_caracteristica(Carta deck_super_trunfo[], int *tamanho_adaptado){

    /**
     * DESCRIÇÃO DA FUNÇÃO:
     * Ela recebe um vetor de struct e um ponteiro para inteiro(tamanho_adaptado) e ela começa com um menu perguntando ao usuário qual campo da carta que ele deseja buscar,
     * após ele digitar o campo que deseja buscar e inserir o valor para a busca, caso a contador encontrar uma carta ou mais ele printa na tela que foi encontrada a carta que o usuário está buscando
     * e exibe ela na tela, caso contrário ele exibe que a carta não foi encontrada, a função só para quando o usuário digitar a opcao de saída do menu, a fim de que o usuário possa procurar todas as cartas
     * que deseja até que ele já tenha buscado tudo que precisa e digite a opção de saída do menu.     * 
    */

    int opcao_menu_busca_carta;

    int contador_cartas_achadas = 0;

    char nome_digitado[41];

    int opcao_letra_classificacao;

    int numero_digitado;

    char letra_digitada;

    int fight_digitado;

    int iq_digitado;

    int danger_digitado;

    int mercy_digitado;

    int i = 0;

    do{

        printf("Digite uma opcao para buscar a carta: \n");
        printf("1 - Buscar pelo nome \n");
        printf("2 - Buscar pela classificacao da carta \n");
        printf("3 - Buscar pelo super trunfo \n");
        printf("4 - Buscar pelo fight \n");
        printf("5 - Buscar pelo iq \n");
        printf("6 - Buscar pelo danger \n");
        printf("7 - Buscar pela mercy \n");
        printf("8 - Sair do menu de busca da carta \n");
        scanf("%i", &opcao_menu_busca_carta);

    }while(opcao_menu_busca_carta < 1 || opcao_menu_busca_carta > 8);

    switch(opcao_menu_busca_carta){

        case 1:

            contador_cartas_achadas = 0;

            printf("Voce escolheu a opcao: 'Buscar pelo nome' \n");

            setbuf(stdin, NULL);
            printf("Digite o nome da carta que deseja buscar: \n");
            fgets(nome_digitado, 41, stdin);
            nome_digitado[strcspn(nome_digitado, "\n")] = '\0';
            setbuf(stdin, NULL);

            for(i = 0; i<*tamanho_adaptado; i++){

                if(strcmp(deck_super_trunfo[i].nome, nome_digitado) == 0){

                    contador_cartas_achadas++;

                    if(contador_cartas_achadas >= 1){

                        printf("Carta encontrada! \n");

                        printf("Nome da carta: %s \n", deck_super_trunfo[i].nome);
                        printf("Classificacao da carta: %i%c \n", deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao);
                    
                        if(deck_super_trunfo[i].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else {

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da carta: %i \n", deck_super_trunfo[i].fight);
                        printf("IQ da carta: %i \n", deck_super_trunfo[i].iq);
                        printf("Danger da carta: %i \n", deck_super_trunfo[i].danger);
                        printf("Mercy da carta: %i \n", deck_super_trunfo[i].mercy);

                    }else{

                        printf("Carta nao encontrada! \n");

                    }

                }
            }

        break;

        case 2:

            contador_cartas_achadas = 0;

            printf("Voce escolheu a opcao: 'Buscar pela classificacao da carta' \n");

            do{

                printf("Digite o numero da classificacao da carta que deseja buscar: \n");
                scanf("%i", &numero_digitado);

            }while(numero_digitado < 1 || numero_digitado > 8);

            do{

                printf("Escolha a opcao da letra da carta que deseja buscar: \n");
                printf("1 - A \n");
                printf("2 - B \n");
                printf("3 - C \n");
                printf("4 - D \n");
                scanf("%i", &opcao_letra_classificacao);

            }while(opcao_letra_classificacao < 1 || opcao_letra_classificacao > 4);

            switch(opcao_letra_classificacao){

                case 1:

                    letra_digitada = 'A';

                break;

                case 2:

                    letra_digitada = 'B';

                break;

                case 3:

                    letra_digitada = 'C';

                break;

                case 4:

                    letra_digitada = 'D';

                break;

            }

            for(i = 0; i<*tamanho_adaptado; i++){

                if(deck_super_trunfo[i].numero_classificacao == numero_digitado && deck_super_trunfo[i].letra_classificacao == letra_digitada){

                    contador_cartas_achadas++;

                    if(contador_cartas_achadas >= 1){

                        printf("Carta encontrada! \n");

                        printf("Nome da carta: %s \n", deck_super_trunfo[i].nome);
                        printf("Classificacao da carta: %i%c \n", deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao);
                    
                        if(deck_super_trunfo[i].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da carta: %i \n", deck_super_trunfo[i].fight);
                        printf("IQ da carta: %i \n", deck_super_trunfo[i].iq);
                        printf("Danger da carta: %i \n", deck_super_trunfo[i].danger);
                        printf("Mercy da carta: %i \n", deck_super_trunfo[i].mercy);


                    }else{

                        printf("Carta nao encontrada! \n");

                    }
                }
            }

        break;

        case 3:

            contador_cartas_achadas = 0;

            printf("Voce escolheu a opcao: 'Buscar pelo super trunfo' \n");

            for(i = 0; i<*tamanho_adaptado; i++){

                if(deck_super_trunfo[i].carta_super_trunfo == 1){

                    contador_cartas_achadas++;

                    if(contador_cartas_achadas >=1){

                        printf("Carta encontrada! \n");

                        printf("Nome da carta: %s \n", deck_super_trunfo[i].nome);
                        printf("Classificacao da carta: %i%c \n", deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao);
                        printf("A carta e um super trunfo \n");
                        printf("Fight da carta: %i \n", deck_super_trunfo[i].fight);
                        printf("IQ da carta: %i \n", deck_super_trunfo[i].iq);
                        printf("Danger da carta: %i \n", deck_super_trunfo[i].danger);
                        printf("Mercy da carta: %i \n", deck_super_trunfo[i].mercy);

                    }else{

                        printf("Cartao nao encontrada! \n");

                    }
                }
            }

        break;

        case 4:
        
            contador_cartas_achadas = 0;

            printf("Voce escolheu a opcao: 'Buscar pelo fight' \n");

            printf("Digite o fight da carta que deseja buscar: \n");
            scanf("%i", &fight_digitado);

            for(i = 0; i<*tamanho_adaptado; i++){

                if(deck_super_trunfo[i].fight == fight_digitado){

                    contador_cartas_achadas++;

                    if(contador_cartas_achadas >= 1){

                        printf("Carta encontrada! \n");

                        printf("Nome da carta: %s \n", deck_super_trunfo[i].nome);
                        printf("Classificacao da carta; %i%c \n", deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao);
                        
                        if(deck_super_trunfo[i].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");
                            
                        }else{

                            printf("A carta nao e um super trunfo \n");
                        }

                        printf("Fight da carta: %i \n", deck_super_trunfo[i].fight);
                        printf("IQ da carta: %i \n", deck_super_trunfo[i].iq);
                        printf("Danger da carta: %i \n", deck_super_trunfo[i].danger);
                        printf("Mercy da carta: %i \n", deck_super_trunfo[i].mercy);


                    }else{

                        printf("Carta nao encontrada! \n");

                    }
                }
            }

        break;

        case 5:

            contador_cartas_achadas = 0;

            printf("Voce escolheu a opcao: 'Buscar pelo IQ' \n");

            printf("Digite o IQ que deseja buscar: \n");
            scanf("%i", &iq_digitado);

            for(i = 0; i<*tamanho_adaptado; i++){

                if(deck_super_trunfo[i].iq == iq_digitado){

                    contador_cartas_achadas++;

                    if(contador_cartas_achadas >= 1){

                        printf("Carta encontrada! \n");

                        printf("Nome da carta: %s \n", deck_super_trunfo[i].nome);
                        printf("Classificacao da carta: %i%c \n", deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao);

                        if(deck_super_trunfo[i].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else {

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da carta: %i \n", deck_super_trunfo[i].fight);
                        printf("IQ da carta: %i \n", deck_super_trunfo[i].iq);
                        printf("Danger da carta: %i \n", deck_super_trunfo[i].danger);
                        printf("Mercy da carta: %i \n", deck_super_trunfo[i].mercy);

                    }else {

                        printf("Carta nao encontrada! \n");

                    }
                }
            }

        break;

        case 6:

            contador_cartas_achadas = 0;

            printf("Voce escolheu a opcao: 'Buscar pelo Danger' \n");

            printf("Digite o Danger que deseja buscar: \n");
            scanf("%i", &danger_digitado);

            for(i = 0; i<*tamanho_adaptado; i++){

                if(deck_super_trunfo[i].danger == danger_digitado){

                    contador_cartas_achadas++;

                    if(contador_cartas_achadas >=1){

                        printf("Carta encontrada! \n");

                        printf("Nome da carta: %s \n", deck_super_trunfo[i].nome);
                        printf("Classificacao da carta: %i%c \n", deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao);
                        
                        if(deck_super_trunfo[i].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da carta: %i \n", deck_super_trunfo[i].fight);
                        printf("IQ da carta: %i \n", deck_super_trunfo[i].iq);
                        printf("Danger da carta: %i \n", deck_super_trunfo[i].danger);
                        printf("Mercy da carta: %i \n", deck_super_trunfo[i].mercy);


                    }else{

                        printf("Carta nao encontrada! \n");
                    }
                }
            }

        break;

        case 7:

            contador_cartas_achadas = 0;

            printf("Voce escolheu a opcao 'Buscar pela mercy' \n");

            printf("Digite a mercy que deseja buscar: \n");
            scanf("%i", &mercy_digitado);

            for(i = 0; i<*tamanho_adaptado; i++){

                if(deck_super_trunfo[i].mercy == mercy_digitado){

                    contador_cartas_achadas++;

                    if(contador_cartas_achadas >= 1){

                        printf("Carta encontrada! \n");

                        printf("Nome da carta: %s \n", deck_super_trunfo[i].nome);
                        printf("Classificacao da carta: %i%c \n", deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao);
                        
                        if(deck_super_trunfo[i].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da carta: %i \n", deck_super_trunfo[i].fight);
                        printf("IQ da carta: %i \n", deck_super_trunfo[i].iq);
                        printf("Danger da carta: %i \n", deck_super_trunfo[i].danger);
                        printf("Mercy da carta: %i \n", deck_super_trunfo[i].mercy);

                    }else{

                        printf("Carta nao encontrada! \n");

                    }
                }
            }

        break;

        case 8:

            printf("Obrigada por usar o menu de busca carta por caracteristica! \n");

        break;

    }

    return;

}

void procura_carta_atributo(Carta deck_super_trunfo[], int *tamanho_adaptado){

    /**
     * DESCRICAO DA FUNÇÃO:
     * Ela recebe um vetor de struct e um ponteiro para inteiro (tamanho_adaptado), ela começa com o menu perguntando ao usuário qual atributo ele deseja procurar
     * podendo ser digitando um valor exibindo a carta que é menor e maior que este valor ou exibindo a maior carta e a menor carta daquele atributo, a função só para quando o usuário digitar a opção de saída do menu
     * a fim de que o usuário possa pesquisar todas as cartas por atributo que ele desejar até que já se tenha feito todas as pesquisas
     * 
    */

    int i = 0;

    int opcao_menu_inicial_atributos;

    int opcao_menu_procura_atributos;

    int compara_numero_digitado = 0;

    int compara_numero_digitado_maior = 0;

    int compara_numero_digitado_menor = 0;

    int indice_maior_digitado;

    int indice_menor_digitado;

    int contador_carta_maior_achada = 0;

    int contador_carta_menor_achada = 0;

    int opcao_menu_procura_atributos_geral;

    int compara_carta_maior_geral;

    int compara_carta_menor_geral;

    int indice_carta_maior_geral;

    int indice_carta_menor_geral;

    do{

        do{

            printf("Escolha uma opcao de procura por atributos: \n");
            printf("1 - Maior / Menor que um valor digitado \n");
            printf("2 - Maior / Menor carta geral \n");
            printf("3 - Sair do menu \n");
            scanf("%i", &opcao_menu_inicial_atributos);

        }while(opcao_menu_inicial_atributos < 1 || opcao_menu_inicial_atributos > 3);

        switch(opcao_menu_inicial_atributos){


            case 1:

                do{

                    printf("Escolha a opcao para qual atributo deseja procurar: \n");
                    printf("1 - Fight \n");
                    printf("2 - IQ \n");
                    printf("3 - Danger \n");
                    printf("4 - Mercy \n");
                    printf("5 - Sair do menu de atributo maior / menor que numero digitado \n");
                    scanf("%i", &opcao_menu_procura_atributos);

                }while(opcao_menu_procura_atributos < 1 || opcao_menu_procura_atributos > 5);

                switch(opcao_menu_procura_atributos){

                    case 1:

                        printf("\n");

                        contador_carta_maior_achada = 0;

                        contador_carta_menor_achada = 0;

                        printf("Voce escolheu a opcao 'Fight' \n");

                        printf("Digite o valor do fight que deseja comparar: \n");
                        scanf("%i", &compara_numero_digitado);

                        compara_numero_digitado_maior = compara_numero_digitado;

                        compara_numero_digitado_menor = compara_numero_digitado;

                        for(i = 0; i<*tamanho_adaptado; i++){

                            if(deck_super_trunfo[i].fight > compara_numero_digitado_maior){

                                compara_numero_digitado_maior = deck_super_trunfo[i].fight;

                                indice_maior_digitado = i;

                                contador_carta_maior_achada++;

                            }

                            if(deck_super_trunfo[i].fight < compara_numero_digitado_menor){

                                compara_numero_digitado_menor = deck_super_trunfo[i].fight;

                                indice_menor_digitado = i;

                                contador_carta_menor_achada++;
                            }

                        }

                        if(contador_carta_maior_achada >= 1){

                            printf("Carta cujo Fight e maior que: %i \n", compara_numero_digitado);

                            printf("Nome da Carta: %s \n",deck_super_trunfo[indice_maior_digitado].nome);
                            printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_maior_digitado].numero_classificacao, deck_super_trunfo[indice_maior_digitado].letra_classificacao);
                            
                            if(deck_super_trunfo[indice_maior_digitado].carta_super_trunfo == 1){

                                printf("A carta e um super trunfo \n");

                            }else{

                                printf("A carta nao e um super trunfo \n");

                            }

                            printf("Fight da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].fight);
                            printf("IQ da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].iq);
                            printf("Danger da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].danger);
                            printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].mercy);

                        }else{

                            printf("Nao existe nenhuma carta com o fight maior que %i \n", compara_numero_digitado);

                        }

                        if(contador_carta_menor_achada >= 1){

                            printf("Carta cujo Fight e menor que: %i \n", compara_numero_digitado);

                            printf("Nome da Carta: %s \n", deck_super_trunfo[indice_menor_digitado].nome);
                            printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_menor_digitado].numero_classificacao, deck_super_trunfo[indice_maior_digitado].letra_classificacao);
                            
                            if(deck_super_trunfo[indice_menor_digitado].carta_super_trunfo == 1){

                                printf("A carta e um super trunfo \n");

                            }else{

                                printf("A carta nao e um super trunfo \n");

                            }

                            printf("Fight da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].fight);
                            printf("IQ da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].iq);
                            printf("Danger da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].danger);
                            printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].mercy);

                        }else{

                            printf("Nao existe nenhuma carta com o fight menor que %i \n", compara_numero_digitado);
                        }
        
                        printf("\n");


                    break;

                    case 2:

                        printf("\n");

                        contador_carta_maior_achada = 0;

                        contador_carta_menor_achada = 0;

                        printf("Voce escolheu a opcao 'IQ' \n");

                        printf("Digite o valor do IQ que deseja comparar: \n");
                        scanf("%i", &compara_numero_digitado);

                        compara_numero_digitado_maior = compara_numero_digitado;

                        compara_numero_digitado_menor = compara_numero_digitado;

                        for(i = 0; i<*tamanho_adaptado; i++){

                            if(deck_super_trunfo[i].iq > compara_numero_digitado_maior){

                                compara_numero_digitado_maior = deck_super_trunfo[i].iq;

                                indice_maior_digitado = i;

                                contador_carta_maior_achada++;

                            }

                            if(deck_super_trunfo[i].iq < compara_numero_digitado_menor){

                                compara_numero_digitado_menor = deck_super_trunfo[i].iq;

                                indice_menor_digitado = i;

                                contador_carta_menor_achada++;
                            }

                        }

                        if(contador_carta_maior_achada >= 1){

                            printf("Carta cujo IQ e maior que: %i \n", compara_numero_digitado);

                            printf("Nome da Carta: %s \n",deck_super_trunfo[indice_maior_digitado].nome);
                            printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_maior_digitado].numero_classificacao, deck_super_trunfo[indice_maior_digitado].letra_classificacao);
                            
                            if(deck_super_trunfo[indice_maior_digitado].carta_super_trunfo == 1){

                                printf("A carta e um super trunfo \n");

                            }else{

                                printf("A carta nao e um super trunfo \n");

                            }

                            printf("Fight da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].fight);
                            printf("IQ da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].iq);
                            printf("Danger da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].danger);
                            printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].mercy);

                        }else{

                            printf("Nao existe nenhuma carta com o IQ maior que %i \n", compara_numero_digitado);

                        }

                        if(contador_carta_menor_achada >= 1){

                            printf("Carta cujo IQ e menor que: %i \n", compara_numero_digitado);

                            printf("Nome da Carta: %s \n",deck_super_trunfo[indice_menor_digitado].nome);
                            printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_menor_digitado].numero_classificacao, deck_super_trunfo[indice_maior_digitado].letra_classificacao);
                            
                            if(deck_super_trunfo[indice_menor_digitado].carta_super_trunfo == 1){

                                printf("A carta e um super trunfo \n");

                            }else{

                                printf("A carta nao e um super trunfo \n");

                            }

                            printf("Fight da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].fight);
                            printf("IQ da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].iq);
                            printf("Danger da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].danger);
                            printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].mercy);

                        }else{

                            printf("Nao existe nenhuma carta com o IQ menor que %i \n", compara_numero_digitado);
                        }


                        printf("\n");

                    break;

                    case 3:

                        printf("\n");

                        contador_carta_maior_achada = 0;

                        contador_carta_menor_achada = 0;

                        printf("Voce escolheu a opcao 'Danger' \n");

                        printf("Digite o valor do Danger que deseja comparar: \n");
                        scanf("%i", &compara_numero_digitado);

                        compara_numero_digitado_maior = compara_numero_digitado;

                        compara_numero_digitado_menor = compara_numero_digitado;

                        for(i = 0; i<*tamanho_adaptado; i++){

                            if(deck_super_trunfo[i].danger > compara_numero_digitado_maior){

                                compara_numero_digitado_maior = deck_super_trunfo[i].danger;

                                indice_maior_digitado = i;

                                contador_carta_maior_achada++;

                            }

                            if(deck_super_trunfo[i].danger < compara_numero_digitado_menor){

                                compara_numero_digitado_menor = deck_super_trunfo[i].danger;

                                indice_menor_digitado = i;

                                contador_carta_menor_achada++;
                            }

                        }

                        if(contador_carta_maior_achada >= 1){

                            printf("Carta cujo Danger e maior que: %i \n", compara_numero_digitado);

                            printf("Nome da Carta: %s \n",deck_super_trunfo[indice_maior_digitado].nome);
                            printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_maior_digitado].numero_classificacao, deck_super_trunfo[indice_maior_digitado].letra_classificacao);
                            
                            if(deck_super_trunfo[indice_maior_digitado].carta_super_trunfo == 1){

                                printf("A carta e um super trunfo \n");

                            }else{

                                printf("A carta nao e um super trunfo \n");

                            }

                            printf("Fight da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].fight);
                            printf("IQ da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].iq);
                            printf("Danger da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].danger);
                            printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].mercy);

                        }else{

                            printf("Nao existe nenhuma carta com o Danger maior que %i \n", compara_numero_digitado);

                        }

                        if(contador_carta_menor_achada >= 1){

                            printf("Carta cujo Danger e menor que: %i \n", compara_numero_digitado);

                            printf("Nome da Carta: %s \n",deck_super_trunfo[indice_menor_digitado].nome);
                            printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_menor_digitado].numero_classificacao, deck_super_trunfo[indice_maior_digitado].letra_classificacao);
                            
                            if(deck_super_trunfo[indice_menor_digitado].carta_super_trunfo == 1){

                                printf("A carta e um super trunfo \n");

                            }else{

                                printf("A carta nao e um super trunfo \n");

                            }

                            printf("Fight da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].fight);
                            printf("IQ da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].iq);
                            printf("Danger da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].danger);
                            printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].mercy);

                        }else{

                            printf("Nao existe nenhuma carta com o Danger menor que %i \n", compara_numero_digitado);
                        }

                        printf("\n");

                    break;

                    case 4:

                        printf("\n");

                        contador_carta_maior_achada = 0;

                        contador_carta_menor_achada = 0;

                        printf("Voce escolheu a opcao 'Mercy' \n");

                        printf("Digite o valor do Mercy que deseja comparar: \n");
                        scanf("%i", &compara_numero_digitado);

                        compara_numero_digitado_maior = compara_numero_digitado;

                        compara_numero_digitado_menor = compara_numero_digitado;

                        for(i = 0; i<*tamanho_adaptado; i++){

                            if(deck_super_trunfo[i].mercy > compara_numero_digitado_maior){

                                compara_numero_digitado_maior = deck_super_trunfo[i].mercy;

                                indice_maior_digitado = i;

                                contador_carta_maior_achada++;

                            }

                            if(deck_super_trunfo[i].mercy < compara_numero_digitado_menor){

                                compara_numero_digitado_menor = deck_super_trunfo[i].mercy;

                                indice_menor_digitado = i;

                                contador_carta_menor_achada++;
                            }

                        }

                        if(contador_carta_maior_achada >= 1){

                            printf("Carta cuja Mercy e maior que: %i \n", compara_numero_digitado);

                            printf("Nome da Carta: %s \n",deck_super_trunfo[indice_maior_digitado].nome);
                            printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_maior_digitado].numero_classificacao, deck_super_trunfo[indice_maior_digitado].letra_classificacao);
                            
                            if(deck_super_trunfo[indice_maior_digitado].carta_super_trunfo == 1){

                                printf("A carta e um super trunfo \n");

                            }else{

                                printf("A carta nao e um super trunfo \n");

                            }

                            printf("Fight da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].fight);
                            printf("IQ da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].iq);
                            printf("Danger da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].danger);
                            printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_maior_digitado].mercy);

                        }else{

                            printf("Nao existe nenhuma carta com a Mercy maior que %i \n", compara_numero_digitado);

                        }

                        if(contador_carta_menor_achada >= 1){

                            printf("Carta cuja Mercy e menor que: %i \n", compara_numero_digitado);

                            printf("Nome da Carta: %s \n",deck_super_trunfo[indice_menor_digitado].nome);
                            printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_menor_digitado].numero_classificacao, deck_super_trunfo[indice_maior_digitado].letra_classificacao);
                            
                            if(deck_super_trunfo[indice_menor_digitado].carta_super_trunfo == 1){

                                printf("A carta e um super trunfo \n");

                            }else{

                                printf("A carta nao e um super trunfo \n");

                            }

                            printf("Fight da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].fight);
                            printf("IQ da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].iq);
                            printf("Danger da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].danger);
                            printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_menor_digitado].mercy);

                        }else{

                            printf("Nao existe nenhuma carta com a Mercy menor que %i \n", compara_numero_digitado);
                        }

                        printf("\n");

                    break;

                    case 5:

                        printf("Obrigada por utilizar o menu procura carta por atributo maior / menor que numero digitado! \n");

                    break;

                }


            break;

            case 2:

                do{

                    printf("Escolha a opcao para qual atributo maior geral deseja procurar: \n");
                    printf("1 - Fight \n");
                    printf("2 - IQ \n");
                    printf("3 - Danger \n");
                    printf("4 - Mercy \n");
                    printf("5 - Sair do menu procura carta por atributo maior / menor geral \n");
                    scanf("%i", &opcao_menu_procura_atributos_geral);

                }while(opcao_menu_procura_atributos_geral < 1 || opcao_menu_procura_atributos_geral > 5);

                switch(opcao_menu_procura_atributos_geral){

                    case 1:

                        printf("\n");

                        printf("Voce escolheu a opcao 'Fight' \n");

                        compara_carta_maior_geral = deck_super_trunfo[0].fight;
                        compara_carta_menor_geral = deck_super_trunfo[0].fight;

                        for(i = 0; i<*tamanho_adaptado; i++){

                            if(deck_super_trunfo[i].fight > compara_carta_maior_geral){

                                compara_carta_maior_geral = deck_super_trunfo[i].fight;

                                indice_carta_maior_geral = i;

                            }

                            if(deck_super_trunfo[i].fight < compara_carta_menor_geral){

                                compara_carta_menor_geral = deck_super_trunfo[i].fight;

                                indice_carta_menor_geral = i;

                            }

                        }

                        //exibindo a carta maior

                        printf("Carta com o maior Fight Geral \n");
                        printf("Nome da Carta: %s \n", deck_super_trunfo[indice_carta_maior_geral].nome);
                        printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_carta_maior_geral].numero_classificacao, deck_super_trunfo[indice_carta_maior_geral].letra_classificacao);

                        if(deck_super_trunfo[indice_carta_maior_geral].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].fight);
                        printf("IQ da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].iq);
                        printf("Danger da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].danger);
                        printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].mercy);

                        //exibindo a menor carta

                        printf("Carta com o menor Fight Geral \n");
                        printf("Nome da Carta: %s \n", deck_super_trunfo[indice_carta_menor_geral].nome);
                        printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_carta_menor_geral].numero_classificacao, deck_super_trunfo[indice_carta_maior_geral].letra_classificacao);

                        if(deck_super_trunfo[indice_carta_menor_geral].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].fight);
                        printf("IQ da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].iq);
                        printf("Danger da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].danger);
                        printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].mercy);

                        printf("\n");

                    break;

                    case 2:

                        printf("\n");

                        printf("Voce escolheu a opcao 'IQ' \n");

                        compara_carta_maior_geral = deck_super_trunfo[0].iq;
                        compara_carta_menor_geral = deck_super_trunfo[0].iq;

                        for(i = 0; i<*tamanho_adaptado; i++){

                            if(deck_super_trunfo[i].iq > compara_carta_maior_geral){

                                compara_carta_maior_geral = deck_super_trunfo[i].iq;

                                indice_carta_maior_geral = i;

                            }

                            if(deck_super_trunfo[i].iq < compara_carta_menor_geral){

                                compara_carta_menor_geral = deck_super_trunfo[i].iq;

                                indice_carta_menor_geral = i;

                            }

                        }

                        //exibindo a carta maior

                        printf("Carta com o maior IQ Geral \n");
                        printf("Nome da Carta: %s \n", deck_super_trunfo[indice_carta_maior_geral].nome);
                        printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_carta_maior_geral].numero_classificacao, deck_super_trunfo[indice_carta_maior_geral].letra_classificacao);

                        if(deck_super_trunfo[indice_carta_maior_geral].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].fight);
                        printf("IQ da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].iq);
                        printf("Danger da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].danger);
                        printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].mercy);

                        //exibindo a menor carta

                        printf("Carta com o menor IQ Geral \n");
                        printf("Nome da Carta: %s \n", deck_super_trunfo[indice_carta_menor_geral].nome);
                        printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_carta_menor_geral].numero_classificacao, deck_super_trunfo[indice_carta_maior_geral].letra_classificacao);

                        if(deck_super_trunfo[indice_carta_menor_geral].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].fight);
                        printf("IQ da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].iq);
                        printf("Danger da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].danger);
                        printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].mercy);

                        printf("\n");

                    break;

                    case 3:

                        printf("\n");

                        printf("Voce escolheu a opcao 'Danger' \n");

                        compara_carta_maior_geral = deck_super_trunfo[0].danger;
                        compara_carta_menor_geral = deck_super_trunfo[0].danger;

                        for(i = 0; i<*tamanho_adaptado; i++){

                            if(deck_super_trunfo[i].danger > compara_carta_maior_geral){

                                compara_carta_maior_geral = deck_super_trunfo[i].danger;

                                indice_carta_maior_geral = i;

                            }

                            if(deck_super_trunfo[i].danger < compara_carta_menor_geral){

                                compara_carta_menor_geral = deck_super_trunfo[i].danger;

                                indice_carta_menor_geral = i;

                            }

                        }

                        //exibindo a carta maior

                        printf("Carta com o maior Danger Geral \n");
                        printf("Nome da Carta: %s \n", deck_super_trunfo[indice_carta_maior_geral].nome);
                        printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_carta_maior_geral].numero_classificacao, deck_super_trunfo[indice_carta_maior_geral].letra_classificacao);

                        if(deck_super_trunfo[indice_carta_maior_geral].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].fight);
                        printf("IQ da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].iq);
                        printf("Danger da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].danger);
                        printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].mercy);

                        //exibindo a menor carta

                        printf("Carta com o menor Danger Geral \n");
                        printf("Nome da Carta: %s \n", deck_super_trunfo[indice_carta_menor_geral].nome);
                        printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_carta_menor_geral].numero_classificacao, deck_super_trunfo[indice_carta_maior_geral].letra_classificacao);

                        if(deck_super_trunfo[indice_carta_menor_geral].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].fight);
                        printf("IQ da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].iq);
                        printf("Danger da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].danger);
                        printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].mercy);

                        printf("\n");

                    break;

                    case 4:

                        printf("\n");

                        printf("Voce escolheu a opcao 'Mercy' \n");

                        compara_carta_maior_geral = deck_super_trunfo[0].mercy;
                        compara_carta_menor_geral = deck_super_trunfo[0].mercy;

                        for(i = 0; i<*tamanho_adaptado; i++){

                            if(deck_super_trunfo[i].mercy > compara_carta_maior_geral){

                                compara_carta_maior_geral = deck_super_trunfo[i].mercy;

                                indice_carta_maior_geral = i;

                            }

                            if(deck_super_trunfo[i].mercy < compara_carta_menor_geral){

                                compara_carta_menor_geral = deck_super_trunfo[i].mercy;

                                indice_carta_menor_geral = i;

                            }

                        }

                        //exibindo a carta maior

                        printf("Carta com a maior Mercy Geral \n");
                        printf("Nome da Carta: %s \n", deck_super_trunfo[indice_carta_maior_geral].nome);
                        printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_carta_maior_geral].numero_classificacao, deck_super_trunfo[indice_carta_maior_geral].letra_classificacao);

                        if(deck_super_trunfo[indice_carta_maior_geral].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].fight);
                        printf("IQ da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].iq);
                        printf("Danger da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].danger);
                        printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_carta_maior_geral].mercy);

                        //exibindo a menor carta

                        printf("Carta com a menor Mercy Geral \n");
                        printf("Nome da Carta: %s \n", deck_super_trunfo[indice_carta_menor_geral].nome);
                        printf("Classificacao da Carta: %i%c \n", deck_super_trunfo[indice_carta_menor_geral].numero_classificacao, deck_super_trunfo[indice_carta_maior_geral].letra_classificacao);

                        if(deck_super_trunfo[indice_carta_menor_geral].carta_super_trunfo == 1){

                            printf("A carta e um super trunfo \n");

                        }else{

                            printf("A carta nao e um super trunfo \n");

                        }

                        printf("Fight da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].fight);
                        printf("IQ da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].iq);
                        printf("Danger da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].danger);
                        printf("Mercy da Carta: %i \n", deck_super_trunfo[indice_carta_menor_geral].mercy);

                        printf("\n");

                    break;

                    case 5:

                        printf("Obrigada por utilizar o menu procura carta por atributo maior / menor geral! \n");

                    break;

                }

            break;

            case 3:

                printf("Obrigada por utilizar o menu de Procura Cartas por Atributo! \n");

            break;

        }


    }while(opcao_menu_inicial_atributos !=3);


    return;

}

// FINAL DE TODAS AS FUNÇÕES


int main(){

    Carta *deck_super_trunfo = (Carta *) calloc (32, sizeof(Carta));

    int i = 0;

    int tamanho_minimo_cartas = 32; 

    int tamanho_digitado_usuario = 0;

    int *tamanho_adaptado; // soma/subtracao do minimo com o digitado pelo usuario

    int opcao_menu_principal;

    int opcao_menu_gerenciamento;

    if(deck_super_trunfo == NULL){

        printf("Erro: Memoria insuficiente \n");
        exit(1);

    }

    /**
     * 
     * DESCRIÇÃO DA ABERTURA DOS ARQUIVOS;
     * Nesta parte caso na abertura do arquivo binário ele retorne um ponteiro nulo, o arquivo que vai ser aberto é o csv com uma mensagem de boas vindas,
     * mas se o ponteiro não for nulo o arquivo que vai ser aberto é o arquivo binário com uma mensagem de boas vindas de volta
     * 
    */

    FILE *arq_binario;

    arq_binario = fopen("dados_salvos.dat", "rb");

    if(arq_binario == NULL){

        printf("\n");

        printf("Bem-Vindo ao Super Trunfo! \n");

        printf("\n");

        FILE *arq;

        arq = fopen("C:\\Super Trunfo\\projeto_dados_arrumado.txt", "r");

        if(arq == NULL){    

            printf("O arquivo nao abriu \n");
            exit(1);

        }

        while(!feof(arq)){
            if ((fscanf(arq, "%[^,], %d, %c, %d, %d, %d, %d, %d\n", 
            deck_super_trunfo[i].nome, &deck_super_trunfo[i].numero_classificacao, 
            &deck_super_trunfo[i].letra_classificacao, 
            (int*) &deck_super_trunfo[i].carta_super_trunfo, 
            &deck_super_trunfo[i].fight, &deck_super_trunfo[i].iq, 
            &deck_super_trunfo[i].danger, &deck_super_trunfo[i].mercy)) == 8){
            
                i++;
            
            }

        }

        fclose(arq);

    
    }else {

        printf("\n");

        printf("Bem-Vindo de volta ao Super Trunfo! \n");
        
        printf("\n");


        fread(tamanho_adaptado, sizeof(int), 1, arq_binario);
        fread(deck_super_trunfo, sizeof(Carta), *tamanho_adaptado, arq_binario);

    }

    fclose(arq_binario);

    /**
     * DESCRIÇÃO DO MENU;
     * Ele começa com um menu principal dando a opção para o usuário de ir para o gerenciamento do jogo, ir para o jogo e sair do programa, ao escolher
     * a opção do modo de gerenciamento, há um submenu para que o usuário escolha a opção de gerenciamento (inserir cartas no deck, exibir todas as cartas, alterar as cartas, excluir as cartas, pesquisar as cartas por caracteristicas, pesquisar as cartas por caracteristicas e exportar os dados para um arquivo csv), 
     * o menu só para de repetir quando o usuário digitar a opção de saída do programa, a fim de que o usuário consiga gerenciar tudo o que ele precisar até que queira sair do programa
     * 
    */

    do{

        do{

            printf("Escolha uma opcao: \n");
            printf("1 - Modo de Gerenciamento do Jogo \n");
            printf("2 - Ir para o Jogo \n");
            printf("3 - Sair do Programa \n");
            scanf("%i", &opcao_menu_principal);

        }while(opcao_menu_principal < 1 || opcao_menu_principal > 3);

        switch(opcao_menu_principal){

            case 1:

                do{
                    
                    printf("Digite a opcao de Gerenciamento \n");
                    printf("1 - Inserir Cartas \n");
                    printf("2 - Exibir Cartas \n");
                    printf("3 - Alterar Carta \n");
                    printf("4 - Excluir Carta \n");
                    printf("5 - Procurar Carta por Caracteristicas \n");
                    printf("6 - Procurar Carta por Atributo \n");
                    printf("7 - Exportar Dados para um arquivo csv \n");
                    printf("8 - Sair do menu de Gerenciamento Global \n");
                    scanf("%i", &opcao_menu_gerenciamento);

                }while(opcao_menu_gerenciamento < 1 || opcao_menu_gerenciamento > 8);

                switch(opcao_menu_gerenciamento){

                    case 1:

                        printf("Digite a quantidade de cartas que deseja adicionar: \n");
                        scanf("%i", &tamanho_digitado_usuario);

                        *tamanho_adaptado = tamanho_digitado_usuario + tamanho_minimo_cartas;

                        deck_super_trunfo = realloc(deck_super_trunfo, *tamanho_adaptado * sizeof(Carta));

                        insere_cartas(deck_super_trunfo, tamanho_minimo_cartas, tamanho_adaptado);

                    break;

                    case 2:

                        *tamanho_adaptado = tamanho_digitado_usuario + tamanho_minimo_cartas;

                        exibe_todas_cartas(deck_super_trunfo, tamanho_adaptado);

                    break;

                    case 3:

                        *tamanho_adaptado = tamanho_digitado_usuario + tamanho_minimo_cartas;

                        altera_todas_cartas(deck_super_trunfo, tamanho_adaptado);

                    break;

                    case 4:

                        printf("Digite a quantidade de cartas que deseja excluir: \n");
                        scanf("%i", &tamanho_digitado_usuario);

                        *tamanho_adaptado = tamanho_minimo_cartas - tamanho_digitado_usuario;

                        deck_super_trunfo = realloc(deck_super_trunfo, *tamanho_adaptado * sizeof(Carta));

                    break;

                    case 5:

                        *tamanho_adaptado = tamanho_digitado_usuario + tamanho_minimo_cartas;

                        procura_carta_caracteristica(deck_super_trunfo, tamanho_adaptado);

                    break;

                    case 6:

                        *tamanho_adaptado = tamanho_digitado_usuario + tamanho_minimo_cartas;

                        procura_carta_atributo(deck_super_trunfo, tamanho_adaptado);

                    break;

                    case 7:

                        FILE *arq_relatorio_texto = fopen("relatorio.csv", "w");

                        for(i = 0; i<*tamanho_adaptado; i++){

                            fprintf(arq_relatorio_texto, "%s,%i,%c,%d,%i,%i,%i,%i \n", deck_super_trunfo[i].nome, deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao, deck_super_trunfo[i].carta_super_trunfo, deck_super_trunfo[i].fight, deck_super_trunfo[i].iq, deck_super_trunfo[i].danger, deck_super_trunfo[i].mercy);
                               
                        }

                        fclose(arq_relatorio_texto);

                    break;

                    case 8:

                        printf("Obrigada por utilizar o menu de gerenciamento! \n");

                    break;
                }

            break;   
                    
            case 2:

                //AQUI VAI SER COLOCADA A ESTRUTURA DA LOGICA DO JOGO

            break;

            case 3:

                printf("Obrigada por utilizar nosso programa! \n");
                exit(1);

            break;

        }

    }while(opcao_menu_principal != 3);

    /* Salva as alterações que foram feitas no arquivo binário, fecha o arquivo e libera a memória alocada do vetor de struct */

    arq_binario = fopen("dados_salvos.dat", "wb");

    fwrite(tamanho_adaptado, sizeof(int), 1, arq_binario);
    fwrite(deck_super_trunfo, sizeof(Carta), *tamanho_adaptado, arq_binario);

    fclose(arq_binario);
    free(deck_super_trunfo);

    return 0;

}

