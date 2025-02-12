#ifndef ASSETSLOADER_H
#define ASSETSLOADER_H


char **scan_assets(const char *caminho, const int maxQuantNomes);

void liberar_assets(char **nomes,int maxQuantNomes);

void padronizar_nome(char nome[]);

#endif