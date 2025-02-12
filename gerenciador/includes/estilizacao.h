#ifndef BIBLIOTECA_ESTILIZACAO
#define BIBLIOTECA_ESTILIZACAO

//Todas as cores e fontes que vão ser usadas no main.c e nas funções para estilizar elas

//Cores dos alertas
#define VERMELHO_NORMAL "\e[0;31m" // Vermelho
#define VERMELHO_VIVO "\e[0;91m" // Vermelho Intenso
#define VERMELHO_VIVO_NEGRITO "\e[1;91m" // Vermelho Intenso Negrito

//Cor para menu e agradecimentos
#define ROXO "\e[0;35m" 
#define ROXO_VIVO "\e[1;35m" // Magenta Negrito
#define ROXO_VIVO_NEGRITO "\e[1;95m" // Magenta Intenso Negrito

#define AZUL_VIVO_NEGRITO "\e[1;94m" // Azul Intenso Negrito
#define AZUL_NEGRITO "\e[1;34m" // Azul Negrito

#define CIANO_VIVO_NEGRITO "\e[1;96m" // Ciano Intenso Negrito
#define CIANO_NEGRITO "\e[1;36m" // Ciano Negrito


//Cor para alertas de cartas modificadas e encontradas
#define VERDE_VIVO "\e[0;92m" // Verde Intenso
#define VERDE_VIVO_NEGRITO "\e[1;92m" // Verde Intenso Negrito


// Reseta as cores - texto branco fundo preto
#define RESET "\e[0m"

#endif