#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "funcoes_super_trunfo.h"
#include "estilizacao.h"
#include <time.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <errno.h>

    void Beep(unsigned int frequencia, unsigned int duracao) {
        char comando[100];
        snprintf(comando, sizeof(comando), "beep -f %u -l %u", frequencia, duracao);
        system(comando);
}
#endif

void abrirJogo(const char *executavelDoJogo, char *nome_usuario, int dificuldade)
{

    char dificuldade_jogo[2];
    snprintf(dificuldade_jogo, sizeof(dificuldade_jogo), "%d", dificuldade);

#ifdef _WIN32

    int contaCaracteres = strlen(executavelDoJogo) + 30;

    char chamada[contaCaracteres];

    // monta o comando que executar e criara o processo com os argumentos
    snprintf(chamada, sizeof(chamada), "\"%s\" %s %s", executavelDoJogo, nome_usuario, dificuldade_jogo);

    //  escrevendo 0 no tamanho de startupinfo, um objeto do sistema operacional, criando o novo processo
    STARTUPINFO startupinfo = {0};
    PROCESS_INFORMATION processinfo = {0};

    // define o tamaho da propia estrutura no iniciador do processo
    startupinfo.cb = sizeof(startupinfo);

    if (!CreateProcess(NULL, chamada, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &startupinfo, &processinfo))
    {

        perror("nao foi possivel criar o processo");
        printf("erro: %ld\n", GetLastError());
        exit(1);
    }

    // Aguarda
    printf("Jogo em execucao");
    WaitForSingleObject(processinfo.hProcess, INFINITE);

    // Fecha os handles do processo que esta o jogo
    CloseHandle(processinfo.hProcess);
    CloseHandle(processinfo.hThread);
#else
    pid_t pid = fork();
    printf("%d", pid);

    printf("Executável: %s\n", executavelDoJogo);
    printf("Argumento 1: %s\n", nome_usuario);
    printf("Argumento 2: %s\n", dificuldade_jogo);
    if (pid == 0)
    {

        //  Monta os argumentos
        //                                  |- ponteiro de ponteiro seria o mesmo que **args
        //                                  |               |- ponteiro                          |- O array de argumentos sempre terminara em NULL
        char *args[] = {(char *)executavelDoJogo, (char *)nome_usuario, (char *)dificuldade_jogo, NULL};

        // chama o programa
        execvp(executavelDoJogo, args);
        // caso ocorra algum erro o processo pai retorna o erro nas linhas a baixo
        perror("execvp falhou");
        printf("Erro código: %d\n", errno);
        exit(1);
    }

#endif
}
void som_beep(int tipo_beep){

    if(tipo_beep == 1){

        Beep(500, 350);

    }else if(tipo_beep == 2){

       Beep(750, 350);

    }else if(tipo_beep == 3){

        Beep(850, 350);

    }


    return;
    
}

Carta* inserir_carta(Carta *deck_super_trunfo, int *tamanho_adaptavel){

    /**
     * DESCRICAO DA FUNÇÃO:
     * Ela recebe um vetor de struct e um ponteiro para inteiro (*tamanho_adaptado). A função começa perguntando o usuário quantas cartas ele quer adicionar, então é feito a conta do tamanho adaptavel
     * para que o for consiga adicionar desde o tamanho inicial de dados da struct até os dados adicionais feitos pelo usuário.
     * Dentro do for é onde ocorre a inserção de dados da carta e também onde tem uma verificação pra ver se já existe uma carta super trunfo
     * para que o usuário não acabe inserindo outra carta super trunfo, e caso não tenha uma carta super trunfo, o usuário pode optar por colocar que 
     * a carta que ele está adicionando seja uma carta super trunfo ou não, e a função se encerra retornando um ponteiro de uma struct
     * 
    */

    int tamanho_digitado_usuario;

    int tamanho_maximo_cartas = 40;

    int quantidade_disponivel_add_carta;

    int tipo_beep = 0;

    quantidade_disponivel_add_carta = tamanho_maximo_cartas - *tamanho_adaptavel;

    printf("\n");
    printf(VERMELHO_VIVO_NEGRITO "Ha %i cartas no deck, a capacidade maxima de cartas e %i \n", *tamanho_adaptavel, tamanho_maximo_cartas);
    printf(VERMELHO_VIVO_NEGRITO "Capacidade disponivel para adicionar mais cartas: %i \n", quantidade_disponivel_add_carta);
    printf(RESET "\n");

    printf("Digite a quantidade de cartas que deseja adicionar: \n");
    scanf("%d", &tamanho_digitado_usuario);

    *tamanho_adaptavel = *tamanho_adaptavel + tamanho_digitado_usuario;

    deck_super_trunfo = realloc(deck_super_trunfo, *tamanho_adaptavel * sizeof(Carta));

    if (deck_super_trunfo == NULL) {
        printf("Erro ao alocar memória\n");
        exit(1);
    }

    int opcao_classificacao_carta;

    int opcao_super_trunfo;

    int contador_carta_super_trunfo = 0;

    if(*tamanho_adaptavel > tamanho_maximo_cartas){

        printf(VERMELHO_VIVO_NEGRITO "A quantidade digitada atinge o limite de cartas que podem ser adicionadas! \n");
        printf(RESET "\n");

        tipo_beep = 2;
        som_beep(tipo_beep);
        
    }else{

        for(int i = *tamanho_adaptavel-tamanho_digitado_usuario; i < *tamanho_adaptavel; i++){

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
                printf(AZUL_VIVO_NEGRITO "1");
                printf(RESET " - A \n");
                printf(AZUL_VIVO_NEGRITO "2");
                printf(RESET " - B \n");
                printf(AZUL_VIVO_NEGRITO "3");
                printf(RESET " - C \n");
                printf(AZUL_VIVO_NEGRITO "4");
                printf(RESET " - D \n");
                scanf("%i", &opcao_classificacao_carta);

            }while(opcao_classificacao_carta < 1 || opcao_classificacao_carta > 4);

            switch(opcao_classificacao_carta){

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

            //verifica se já existe uma carta super trunfo
            contador_carta_super_trunfo = 0;
            for (int j = 0; j < *tamanho_adaptavel - tamanho_digitado_usuario; j++) {
                if (deck_super_trunfo[j].carta_super_trunfo == 1) {
                    contador_carta_super_trunfo++;
                }
            }
        
            if(contador_carta_super_trunfo == 1){

                deck_super_trunfo[i].carta_super_trunfo = 0;
                printf(VERMELHO_VIVO_NEGRITO "Ja existe uma carta SuperTrunfo \n");
                printf(RESET);

            }else{

                do{

                    printf("Escolha a opcao referente a carta super trunfo: \n");
                    printf(AZUL_VIVO_NEGRITO "1");
                    printf(RESET " - A carta e um super trunfo \n");
                    printf(AZUL_VIVO_NEGRITO "2");
                    printf(RESET " - A carta nao e um super trunfo \n");
                    scanf("%i", &opcao_super_trunfo);

                }while(opcao_super_trunfo < 1 || opcao_super_trunfo > 2);

                switch(opcao_super_trunfo){

                    case 1:

                        deck_super_trunfo[i].carta_super_trunfo = 1;

                    break;

                    case 2:

                        deck_super_trunfo[i].carta_super_trunfo = 0;

                    break;

                }

            }

            setbuf(stdin, NULL);
            printf("Digite o Fight da carta: \n");
            scanf("%d", &deck_super_trunfo[i].fight);
            setbuf(stdin, NULL);

            setbuf(stdin, NULL);
            printf("Digite o IQ da carta: \n");
            scanf("%d", &deck_super_trunfo[i].iq);
            setbuf(stdin, NULL);

            setbuf(stdin, NULL);
            printf("Digite o Danger da carta: \n");
            scanf("%d", &deck_super_trunfo[i].danger);
            setbuf(stdin, NULL);

            setbuf(stdin, NULL);
            printf("Digite a Mercy da carta: \n");
            scanf("%d", &deck_super_trunfo[i].mercy);
            setbuf(stdin, NULL);

        }

    }

    return deck_super_trunfo;

}

void exibe_todas_cartas(Carta *deck_super_trunfo, int *tamanho_adaptado){

    /**
     * DESCRIÇÃO DA FUNÇÃO:
     * Ela recebe o vetor de struct e um ponteiro para um inteiro (*tamanho_adaptado),
     * e com o vetor e esse ponteiro é possivel exibir todas cartas de i tamanho (i = 0) até a carta *tamanho_adaptado (*tamanho_adaptado = tamanho_minimo + tamanho_digitado_usuario)
    */

    int i = 0;

    for(i = 0; i<*tamanho_adaptado; i++){

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

void altera_todas_cartas(Carta deck_super_trunfo[], int *tamanho_adaptado){

    /**
     * DESCRIÇÃO DA FUNÇÃO:
     * Ela recebe o vetor de struct e um ponteiro  para um inteiro (*tamanho_adaptado) e ela começa com um menu perguntando ao usuario qual campo da carta ele deseja alterar,
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

            setbuf(stdin, NULL);
            printf("Digite o tipo de alteracao que deseja fazer: \n");
            printf(AZUL_VIVO_NEGRITO "1");
            printf(RESET " - Alterar o nome da carta \n");
            printf(AZUL_VIVO_NEGRITO "2");
            printf(RESET " - Alterar o numero de classificacao da carta \n");
            printf(AZUL_VIVO_NEGRITO "3");
            printf(RESET " - Alterar letra de classificacao da carta \n");
            printf(AZUL_VIVO_NEGRITO "4");
            printf(RESET " - Alterar carta super trunfo \n");
            printf(AZUL_VIVO_NEGRITO "5");
            printf(RESET " - Alterar Fight da carta \n");
            printf(AZUL_VIVO_NEGRITO "6");
            printf(RESET " - Alterar IQ da carta \n");
            printf(AZUL_VIVO_NEGRITO "7");
            printf(RESET " - Alterar Danger da carta \n");
            printf(AZUL_VIVO_NEGRITO "8");
            printf(RESET " - Alterar a Mercy da carta \n");
            printf(AZUL_VIVO_NEGRITO "9");
            printf(RESET " - Alteracoes concluidas (Sair do menu de alteracoes) \n");
            scanf("%i", &opcao_alterar_carta);
            setbuf(stdin, NULL);

        }while(opcao_alterar_carta < 1 || opcao_alterar_carta > 9);

        switch(opcao_alterar_carta){

            case 1:

                printf("\n");
                setbuf(stdin, NULL);
                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Alterar o nome da carta' \n");
                printf(RESET);

                printf("\n");

                do{

                    setbuf(stdin, NULL);
                    printf("Digite o indice da carta que deseja alterar: \n");
                    scanf("%i", &indice_carta_alteracao);
                    setbuf(stdin, NULL);

                }while(indice_carta_alteracao < 0 || indice_carta_alteracao > *tamanho_adaptado);

                printf("\n");

                setbuf(stdin, NULL);
                printf("Digite o novo nome da carta: \n");
                fgets(novo_nome_carta, 41, stdin);
                novo_nome_carta[strcspn(novo_nome_carta, "\n")] = '\0';
                setbuf(stdin, NULL);

                strcpy(deck_super_trunfo[indice_carta_alteracao].nome, novo_nome_carta);

                printf(VERDE_VIVO_NEGRITO "Alteracao feita! \n");
                printf(RESET);
                setbuf(stdin, NULL);
                printf("\n");

            break;

            case 2:

                printf("\n");
                setbuf(stdin, NULL);
                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Alterar o numero de classificacao da carta' \n");
                printf(RESET);
                printf("\n");

                do{

                    setbuf(stdin, NULL);
                    printf("Digite o indice da carta que deseja alterar: \n");
                    scanf("%i", &indice_carta_alteracao);
                    setbuf(stdin, NULL);

                }while(indice_carta_alteracao < 0 || indice_carta_alteracao > *tamanho_adaptado);

                printf("\n");

                printf("Digite o novo numero da carta: \n");
                scanf("%i", &novo_numero_classificacao);

                deck_super_trunfo[indice_carta_alteracao].numero_classificacao = novo_numero_classificacao;

                printf(VERDE_VIVO_NEGRITO "Alteracao feita! \n");
                printf(RESET);
                setbuf(stdin, NULL);
                printf("\n");

            break;

            case 3:

                printf("\n");
                setbuf(stdin, NULL);
                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Alterar letra de classificacao da carta' \n");
                printf(RESET);
                printf("\n");

                do{

                    setbuf(stdin, NULL);
                    printf("Digite o indice da carta que deseja alterar: \n");
                    scanf("%i", &indice_carta_alteracao);
                    setbuf(stdin, NULL);

                }while(indice_carta_alteracao < 0 || indice_carta_alteracao > *tamanho_adaptado);

                printf("\n");

                do{

                    printf("Escolha a opcao da letra de classificacao da carta: \n");
                    printf(AZUL_VIVO_NEGRITO "1");
                    printf(RESET " - A \n");
                    printf(AZUL_VIVO_NEGRITO "1");
                    printf(RESET " - B \n");
                    printf(AZUL_VIVO_NEGRITO "1");
                    printf(RESET " - C \n");
                    printf(AZUL_VIVO_NEGRITO "1");
                    printf(RESET " - D \n");
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
                
                printf(VERDE_VIVO_NEGRITO "Alteracao feita! \n");
                printf(RESET);
                setbuf(stdin, NULL);
                printf("\n");

            break;

            case 4:

                printf("\n");
                setbuf(stdin, NULL);
                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Alterar carta super trunfo' \n");
                printf(RESET);
                printf("\n");

                do{

                    setbuf(stdin, NULL);
                    printf("Digite o indice da carta que deseja alterar: \n");
                    scanf("%i", &indice_carta_alteracao);
                    setbuf(stdin, NULL);

                }while(indice_carta_alteracao < 0 || indice_carta_alteracao > *tamanho_adaptado);

                printf("\n");

                for(i = 0; i<*tamanho_adaptado; i++){

                    if(deck_super_trunfo[i].carta_super_trunfo == 1){

                        deck_super_trunfo[i].carta_super_trunfo = 0;

                    }

                }

                deck_super_trunfo[indice_carta_alteracao].carta_super_trunfo = 1;

               printf(VERDE_VIVO_NEGRITO "Alteracao feita! \n");
               printf(RESET);
               setbuf(stdin, NULL);
               printf("\n");

            break;

            case 5:

                printf("\n");
                setbuf(stdin, NULL);
                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Alterar Fight da carta' \n");
                printf(RESET);
                printf("\n");

                do{

                    setbuf(stdin, NULL);
                    printf("Digite o indice da carta que deseja alterar: \n");
                    scanf("%i", &indice_carta_alteracao);
                    setbuf(stdin, NULL);

                }while(indice_carta_alteracao < 0 || indice_carta_alteracao > *tamanho_adaptado);

                printf("\n");

                printf("Digite o novo fight da carta: \n");
                scanf("%i", &novo_fight_carta);

                deck_super_trunfo[indice_carta_alteracao].fight = novo_fight_carta;

                printf(VERDE_VIVO_NEGRITO "Alteracao feita! \n");
                printf(RESET);
                printf("\n");

            break;

            case 6:

                printf("\n");
                setbuf(stdin, NULL);
                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Alterar IQ da carta' \n");
                printf(RESET);
                printf("\n");

                do{

                    setbuf(stdin, NULL);
                    printf("Digite o indice da carta que deseja alterar: \n");
                    scanf("%i", &indice_carta_alteracao);
                    setbuf(stdin, NULL);

                }while(indice_carta_alteracao < 0 || indice_carta_alteracao > *tamanho_adaptado);

                printf("\n");

                printf("Digite o novo IQ da carta: \n");
                scanf("%i", &novo_iq_carta);

                deck_super_trunfo[indice_carta_alteracao].iq = novo_iq_carta;

                printf(VERDE_VIVO_NEGRITO "Alteracao feita! \n");
                printf(RESET);
                printf("\n");

            break;

            case 7:

                printf("\n");
                setbuf(stdin, NULL);
                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Alterar Danger da carta' \n");
                printf(RESET);
                printf("\n");

                do{

                    setbuf(stdin, NULL);
                    printf("Digite o indice da carta que deseja alterar: \n");
                    scanf("%i", &indice_carta_alteracao);
                    setbuf(stdin, NULL);

                }while(indice_carta_alteracao < 0 || indice_carta_alteracao > *tamanho_adaptado);

                printf("\n");

                printf("Digite o novo Danger da carta: \n");
                scanf("%i", &novo_danger_carta);

                deck_super_trunfo[indice_carta_alteracao].danger = novo_danger_carta;

                printf(VERDE_VIVO_NEGRITO "Alteracao feita! \n");
                printf(RESET);
                printf("\n");

            break;

            case 8:

                printf("\n");
                setbuf(stdin, NULL);
                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Alterar a Mercy da carta' \n");
                printf(RESET);
                printf("\n");

                do{

                    setbuf(stdin, NULL);
                    printf("Digite o indice da carta que deseja alterar: \n");
                    scanf("%i", &indice_carta_alteracao);
                    setbuf(stdin, NULL);

                }while(indice_carta_alteracao < 0 || indice_carta_alteracao > *tamanho_adaptado);

                printf("\n");

                printf("Digite a nova Mercy da carta: \n");
                scanf("%i", &novo_mercy_carta);

                deck_super_trunfo[indice_carta_alteracao].mercy = novo_mercy_carta;

                printf(VERDE_VIVO_NEGRITO "Alteracao feita! \n");
                printf(RESET);
                printf("\n");

            break;

            case 9:

                printf("\n");
                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Alteracoes concluidas (Sair do menu de alteracoes)' \n");
                printf("Obrigada por utilizar o menu de alteracoes! \n");
                printf(RESET);
                printf("\n");

            break;

        }


    }while(opcao_alterar_carta != 9);

    return;

}

void procura_carta_caracteristica(Carta deck_super_trunfo[], int *tamanho_adaptado){

    /**
     * DESCRIÇÃO DA FUNÇÃO:
     * Ela recebe um vetor de struct e um ponteiro para inteiro(*tamanho_adaptado) e ela começa com um menu perguntando ao usuário qual campo da carta que ele deseja buscar,
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

    int tipo_beep = 0;

    do{

        do{

            setbuf(stdin, NULL);
            printf("Digite uma opcao para buscar a carta: \n");
            printf(AZUL_VIVO_NEGRITO "1");
            printf(RESET " - Buscar pelo nome \n");
            printf(AZUL_VIVO_NEGRITO "2");
            printf(RESET " - Buscar pela classificacao da carta \n");
            printf(AZUL_VIVO_NEGRITO "3");
            printf(RESET " - Buscar pelo super trunfo \n");
            printf(AZUL_VIVO_NEGRITO "4");
            printf(RESET " - Buscar pelo fight \n");
            printf(AZUL_VIVO_NEGRITO "5");
            printf(RESET " - Buscar pelo iq \n");
            printf(AZUL_VIVO_NEGRITO "6");
            printf(RESET " - Buscar pelo danger \n");
            printf(AZUL_VIVO_NEGRITO "7");
            printf(RESET " - Buscar pela mercy \n");
            printf(AZUL_VIVO_NEGRITO "8");
            printf(RESET " - Sair do menu de busca da carta \n");
            setbuf(stdin, NULL);
            scanf("%i", &opcao_menu_busca_carta);

        }while(opcao_menu_busca_carta < 1 || opcao_menu_busca_carta > 8);

        switch(opcao_menu_busca_carta){

            case 1:

                printf("\n");

                contador_cartas_achadas = 0;

                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao: 'Buscar pelo nome' \n");
                printf(RESET);
                printf("\n");

                setbuf(stdin, NULL);
                printf("Digite o nome da carta que deseja buscar: \n");
                fgets(nome_digitado, 41, stdin);
                nome_digitado[strcspn(nome_digitado, "\n")] = '\0';
                setbuf(stdin, NULL);

                for(i = 0; i<*tamanho_adaptado; i++){

                    if(strcmp(deck_super_trunfo[i].nome, nome_digitado) == 0){

                        contador_cartas_achadas++;

                        if(contador_cartas_achadas >= 1){

                            tipo_beep = 1;
                            som_beep(tipo_beep);

                            printf(VERDE_VIVO_NEGRITO "Carta encontrada! \n");
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Carta nao encontrada! \n");
                            printf(RESET);

                        }

                    }
                }

                printf("\n");

            break;

            case 2:

                printf("\n");

                contador_cartas_achadas = 0;

                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao: 'Buscar pela classificacao da carta' \n");
                printf(RESET);
                printf("\n");

                do{

                    printf("Digite o numero da classificacao da carta que deseja buscar: \n");
                    scanf("%i", &numero_digitado);

                }while(numero_digitado < 1 || numero_digitado > 8);

                do{

                    setbuf(stdin, NULL);
                    printf("Escolha a opcao da letra da carta que deseja buscar: \n");
                    printf(AZUL_VIVO_NEGRITO "1");
                    printf(RESET " - A");
                    printf(AZUL_VIVO_NEGRITO "2");
                    printf(RESET " - B");
                    printf(AZUL_VIVO_NEGRITO "3");
                    printf(RESET " - C");
                    printf(AZUL_VIVO_NEGRITO "4");
                    printf(RESET " - D");
                    setbuf(stdin, NULL);
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

                            tipo_beep = 1;
                            som_beep(tipo_beep);

                            printf(VERDE_VIVO_NEGRITO "Carta encontrada! \n");
                            printf(RESET);
                            printf("\n");

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

                            printf(VERMELHO_VIVO_NEGRITO "Carta nao encontrada! \n");
                            printf(RESET);

                        }
                    }
                }

                printf("\n");

            break;

            case 3:

                printf("\n");

                contador_cartas_achadas = 0;

                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao: 'Buscar pelo super trunfo' \n");
                printf(RESET);
                printf("\n");

                for(i = 0; i<*tamanho_adaptado; i++){

                    if(deck_super_trunfo[i].carta_super_trunfo == 1){

                        contador_cartas_achadas++;

                        if(contador_cartas_achadas >=1){

                            tipo_beep = 1;
                            som_beep(tipo_beep);

                            printf(VERDE_VIVO_NEGRITO "Carta encontrada! \n");
                            printf(RESET);

                            printf("Nome da carta: %s \n", deck_super_trunfo[i].nome);
                            printf("Classificacao da carta: %i%c \n", deck_super_trunfo[i].numero_classificacao, deck_super_trunfo[i].letra_classificacao);
                            printf("A carta e um super trunfo \n");
                            printf("Fight da carta: %i \n", deck_super_trunfo[i].fight);
                            printf("IQ da carta: %i \n", deck_super_trunfo[i].iq);
                            printf("Danger da carta: %i \n", deck_super_trunfo[i].danger);
                            printf("Mercy da carta: %i \n", deck_super_trunfo[i].mercy);

                        }else{

                            printf(VERMELHO_VIVO_NEGRITO "Cartao nao encontrada! \n");
                            printf(RESET);

                        }
                    }
                }

                printf("\n");

            break;

            case 4:

               printf("\n");
        
                contador_cartas_achadas = 0;

                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao: 'Buscar pelo fight' \n");
                printf(RESET);
                printf("\n");

                printf("Digite o fight da carta que deseja buscar: \n");
                scanf("%i", &fight_digitado);

                for(i = 0; i<*tamanho_adaptado; i++){

                    if(deck_super_trunfo[i].fight == fight_digitado){

                        contador_cartas_achadas++;

                        if(contador_cartas_achadas >= 1){

                            tipo_beep = 1;
                            som_beep(tipo_beep);

                            printf(VERDE_VIVO_NEGRITO "Carta encontrada! \n");
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Carta nao encontrada! \n");
                            printf(RESET);

                        }
                    }
                }

               printf("\n");

            break;

            case 5:

                printf("\n");

                contador_cartas_achadas = 0;

                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao: 'Buscar pelo IQ' \n");
                printf(RESET);
                printf("\n");

                printf("Digite o IQ que deseja buscar: \n");
                scanf("%i", &iq_digitado);

                for(i = 0; i<*tamanho_adaptado; i++){

                    if(deck_super_trunfo[i].iq == iq_digitado){

                        contador_cartas_achadas++;

                        if(contador_cartas_achadas >= 1){

                            tipo_beep = 1;
                            som_beep(tipo_beep);

                            printf(VERDE_VIVO_NEGRITO "Carta encontrada! \n");
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Carta nao encontrada! \n");
                            printf(RESET);

                        }
                    }
                }

                printf("\n");

            break;

            case 6:
            
                printf("\n");

                contador_cartas_achadas = 0;

                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao: 'Buscar pelo Danger' \n");
                printf(RESET);
                printf("\n");

                printf("Digite o Danger que deseja buscar: \n");
                scanf("%i", &danger_digitado);

                for(i = 0; i<*tamanho_adaptado; i++){

                    if(deck_super_trunfo[i].danger == danger_digitado){

                        contador_cartas_achadas++;

                        if(contador_cartas_achadas >=1){

                            tipo_beep = 1;
                            som_beep(tipo_beep);

                            printf(VERDE_VIVO_NEGRITO "Carta encontrada! \n");
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Carta nao encontrada! \n");
                            printf(RESET);

                        }
                    }
                }

               printf("\n");

            break;

            case 7:

                printf("\n");

                contador_cartas_achadas = 0;

                printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Buscar pela mercy' \n");
                printf(RESET);
                printf("\n");

                printf("Digite a mercy que deseja buscar: \n");
                scanf("%i", &mercy_digitado);

                for(i = 0; i<*tamanho_adaptado; i++){

                    if(deck_super_trunfo[i].mercy == mercy_digitado){

                        contador_cartas_achadas++;

                        if(contador_cartas_achadas >= 1){

                            tipo_beep = 1;
                            som_beep(tipo_beep);

                            printf(VERDE_VIVO_NEGRITO "Carta encontrada! \n");
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Carta nao encontrada! \n");
                            printf(RESET);

                        }
                    }   
                }

               printf("\n");

            break;

            case 8:

                printf("\n");

                printf(AZUL_VIVO_NEGRITO "Obrigada por usar o menu de busca carta por caracteristica! \n");
                printf(RESET);

               printf("\n");

            break;

        }

    }while(opcao_menu_busca_carta != 8);

    return;

}

void procura_carta_atributo(Carta deck_super_trunfo[], int *tamanho_adaptado){

    /**
     * DESCRICAO DA FUNÇÃO:
     * Ela recebe um vetor de struct e um ponteiro para inteiro (*tamanho_adaptado), ela começa com o menu perguntando ao usuário qual atributo ele deseja procurar
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

            setbuf(stdin, NULL);
            printf("Escolha uma opcao de procura por atributos: \n");
            printf(AZUL_VIVO_NEGRITO "1");
            printf(RESET " - Maior / Menor que um valor digitado \n");
            printf(AZUL_VIVO_NEGRITO "2");
            printf(RESET " - Maior / Menor carta geral \n");
            printf(AZUL_VIVO_NEGRITO "3");
            printf(RESET " - Sair do menu \n");
            setbuf(stdin, NULL);
            scanf("%i", &opcao_menu_inicial_atributos);

        }while(opcao_menu_inicial_atributos < 1 || opcao_menu_inicial_atributos > 3);

        switch(opcao_menu_inicial_atributos){


            case 1:

                do{

                    setbuf(stdin, NULL);
                    printf("Escolha a opcao para qual atributo deseja procurar: \n");
                    printf(AZUL_VIVO_NEGRITO "1");
                    printf(RESET " - Fight");
                    printf(AZUL_VIVO_NEGRITO "2");
                    printf(RESET " - IQ ");
                    printf(AZUL_VIVO_NEGRITO "3");
                    printf(RESET " - Danger \n");
                    printf(AZUL_VIVO_NEGRITO "4");
                    printf(RESET " - Mercy \n");
                    printf(AZUL_VIVO_NEGRITO "5");
                    printf(RESET " - Sair do menu de atributo maior / menor que numero digitado \n");
                    setbuf(stdin, NULL);
                    scanf("%i", &opcao_menu_procura_atributos);

                }while(opcao_menu_procura_atributos < 1 || opcao_menu_procura_atributos > 5);

                switch(opcao_menu_procura_atributos){

                    case 1:

                        printf("\n");

                        contador_carta_maior_achada = 0;

                        contador_carta_menor_achada = 0;

                        printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Fight' \n");
                        printf(RESET);
                        printf("\n");

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

                            printf(VERDE_VIVO_NEGRITO "Carta cujo Fight e maior que: %i \n", compara_numero_digitado);
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Nao existe nenhuma carta com o fight maior que %i \n", compara_numero_digitado);
                            printf(RESET);

                        }

                        if(contador_carta_menor_achada >= 1){

                            printf(VERMELHO_VIVO_NEGRITO "Carta cujo Fight e menor que: %i \n", compara_numero_digitado);
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Nao existe nenhuma carta com o fight menor que %i \n", compara_numero_digitado);
                            printf(RESET);

                        }
        
                        printf("\n");


                    break;

                    case 2:

                        printf("\n");

                        contador_carta_maior_achada = 0;

                        contador_carta_menor_achada = 0;

                        printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'IQ' \n");
                        printf(RESET);
                        printf("\n");

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

                            printf(VERDE_VIVO_NEGRITO "Carta cujo IQ e maior que: %i \n", compara_numero_digitado);
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Nao existe nenhuma carta com o IQ maior que %i \n", compara_numero_digitado);
                            printf(RESET);

                        }

                        if(contador_carta_menor_achada >= 1){

                            printf(VERMELHO_VIVO_NEGRITO "Carta cujo IQ e menor que: %i \n", compara_numero_digitado);
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Nao existe nenhuma carta com o IQ menor que %i \n", compara_numero_digitado);
                            printf(RESET);
                       
                        }
                        
                        printf("\n");

                    break;

                    case 3:

                        printf("\n");

                        contador_carta_maior_achada = 0;

                        contador_carta_menor_achada = 0;

                        printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Danger' \n");
                        printf(RESET);
                        printf("\n");

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

                            printf(VERDE_VIVO_NEGRITO "Carta cujo Danger e maior que: %i \n", compara_numero_digitado);
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Nao existe nenhuma carta com o Danger maior que %i \n", compara_numero_digitado);
                            printf(RESET);

                        }

                        if(contador_carta_menor_achada >= 1){

                            printf(VERMELHO_VIVO_NEGRITO "Carta cujo Danger e menor que: %i \n", compara_numero_digitado);
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Nao existe nenhuma carta com o Danger menor que %i \n", compara_numero_digitado);
                            printf(RESET);
                       
                        }

                        printf("\n");

                    break;

                    case 4:

                        printf("\n");

                        contador_carta_maior_achada = 0;

                        contador_carta_menor_achada = 0;

                        printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Mercy' \n");
                        printf(RESET);
                        printf("\n");

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

                            printf(VERDE_VIVO_NEGRITO "Carta cuja Mercy e maior que: %i \n", compara_numero_digitado);
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Nao existe nenhuma carta com a Mercy maior que %i \n", compara_numero_digitado);
                            printf(RESET);

                        }

                        if(contador_carta_menor_achada >= 1){

                            printf(VERMELHO_VIVO_NEGRITO "Carta cuja Mercy e menor que: %i \n", compara_numero_digitado);
                            printf(RESET);

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

                            printf(VERMELHO_VIVO_NEGRITO "Nao existe nenhuma carta com a Mercy menor que %i \n", compara_numero_digitado);
                            printf(RESET);
                        
                        }

                        printf("\n");

                    break;

                    case 5:

                        printf(AZUL_VIVO_NEGRITO "Obrigada por utilizar o menu procura carta por atributo maior / menor que numero digitado! \n");
                        printf(RESET);

                    break;

                }


            break;

            case 2:

                do{

                    setbuf(stdin, NULL);
                    printf("Escolha a opcao para qual atributo maior geral deseja procurar: \n");
                    printf(AZUL_VIVO_NEGRITO "1");
                    printf(RESET " - Fight \n");
                    printf(AZUL_VIVO_NEGRITO "2");
                    printf(RESET " - IQ \n");
                    printf(AZUL_VIVO_NEGRITO "3");
                    printf(RESET " - Danger \n");
                    printf(AZUL_VIVO_NEGRITO "4");
                    printf(RESET " - Mercy \n");
                    printf(AZUL_VIVO_NEGRITO "5");
                    printf(RESET " - Sair do menu procura carta por atributo maior / menor geral \n");
                    setbuf(stdin, NULL);
                    scanf("%i", &opcao_menu_procura_atributos_geral);

                }while(opcao_menu_procura_atributos_geral < 1 || opcao_menu_procura_atributos_geral > 5);

                switch(opcao_menu_procura_atributos_geral){

                    case 1:

                        printf("\n");
                        printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Fight' \n");
                        printf(RESET);
                        printf("\n");

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

                        printf(VERDE_VIVO_NEGRITO "Carta com o maior Fight Geral \n");
                        printf(RESET);
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

                        printf(VERMELHO_VIVO_NEGRITO "Carta com o menor Fight Geral \n");
                        printf(RESET);
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
                        printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'IQ' \n");
                        printf(RESET);
                        printf("\n");

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

                        printf(VERDE_VIVO_NEGRITO "Carta com o maior IQ Geral \n");
                        printf(RESET);
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

                        printf(VERMELHO_VIVO_NEGRITO "Carta com o menor IQ Geral \n");
                        printf(RESET);
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
                        printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Danger' \n");
                        printf(RESET);
                        printf("\n");

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

                        printf(VERDE_VIVO_NEGRITO "Carta com o maior Danger Geral \n");
                        printf(RESET);
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

                        printf(VERMELHO_VIVO_NEGRITO "Carta com o menor Danger Geral \n");;
                        printf(RESET);
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
                        printf(AZUL_VIVO_NEGRITO "Voce escolheu a opcao 'Mercy' \n");
                        printf(RESET);
                        printf("\n");

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

                        printf(VERDE_VIVO_NEGRITO "Carta com a maior Mercy Geral \n");
                        printf(RESET);
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

                        printf(VERMELHO_VIVO_NEGRITO "Carta com a menor Mercy Geral \n");
                        printf(RESET);
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

                        printf(AZUL_VIVO_NEGRITO "Obrigada por utilizar o menu procura carta por atributo maior / menor geral! \n");
                        printf(RESET);

                    break;

                }

            break;

            case 3:

                printf(AZUL_VIVO_NEGRITO "Obrigada por utilizar o menu de Procura Cartas por Atributo! \n");
                printf(RESET);

            break;

        }

    }while(opcao_menu_inicial_atributos !=3);

    return;

}

