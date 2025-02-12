#ifndef STLOGICA_H
#define STLOGICA_H


typedef struct
{
    char nome[41];
    int numeroClassificacao;
    char letraClassificacao;
    bool superTrunfo;
    int fight;
    int iq;
    int danger;
    int mercy;
} Carta;

typedef struct
{
    char nome[41];
    int numeroClassificacao;
    char letraClassificacao;
    bool superTrunfo;
    int fight;
    int iq;
    int danger;
    int mercy;
    int imgid;
} CartaId;

typedef struct
{
    char nome[50];
    int bot;
    CartaId *mao;
    int cartasRestantes;

} Jogador;


CartaId *carregarCartas(const char *nomeArquivo, int *totalCartas);

bool embaralharCartas(CartaId *cartas, int totalCartas);

bool distribuirCartas(CartaId *cartas, int totalCartas, Jogador *jogadores, int numJogadores);

int resolverRodada(Jogador *jogadores, int numJogadores, int atributo, int indiceEmpate);

void transferirCartas(Jogador *jogadores, int indiceVencedor, int numJogadores, int indiceEmpate);

int verificarFimDoJogo(Jogador *jogadores, int numJogadores, int indiceEmpate);

void gerarRelatorioCsv(Jogador *jogadores, int numJogadores, const char *nomeArquivo);

int bot(Jogador *jogador);

void liberarMemoria(Jogador *jogadores, int numJogadores, CartaId *cartas);


#endif