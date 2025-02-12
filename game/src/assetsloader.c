#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Assetsloader.h"
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

void padronizar_nome(char nome[])
{
    int i = 0, j = 0;
    while (nome[i] != '\0')
    {

        // encontrar 'ã' (0xC3 e 0xA3) -> o carcter pega 2 char
        if ((unsigned char)nome[i] == 0xC3 && (unsigned char)nome[i + 1] == 0xA3)
        {
            nome[j++] = 'a';
            i += 2;
        }
        else
        {
            nome[j++] = nome[i++];
        }
    }
    nome[j] = '\0';

    for (int i = 0; nome[i] != '\0'; i++)
    {
        if (nome[i] == ' ')
        {
            nome[i] = '_';
        }

        nome[i] = tolower(nome[i]);
    }
}

char **scan_assets(const char *caminho, const int maxQuantNomes)
{
    char **nome_arquivos = malloc(maxQuantNomes * sizeof(char *) + 1);
    if (nome_arquivos == NULL)
    {
        perror("Erro ao alocar memória para lista de nomes");
        return NULL;
    }

#ifdef _WIN32
    int stlencaminho = strlen(caminho) + strlen("\\*.png");
    char caminho_assets[stlencaminho];
    strcpy(caminho_assets, caminho);
    strcat(caminho_assets, "\\*.png");

    WIN32_FIND_DATA fft;
    HANDLE hFind = FindFirstFile(caminho_assets, &fft);

    int quantNomes = 0;
    do
    {
        if (quantNomes < maxQuantNomes)
        {
            nome_arquivos[quantNomes] = malloc(strlen(fft.cFileName) + 1);
            if (nome_arquivos[quantNomes])
            {
                strcpy(nome_arquivos[quantNomes], fft.cFileName);
                quantNomes++;
            }
            else
            {
                perror("Erro ao alocar memória");
                for (int i = 0; i < quantNomes; i++)
                {
                    free(nome_arquivos[i]);
                }
                free(nome_arquivos);
                return NULL;
            }
        }
        else
        {
            break;
        }
    } while (FindNextFile(hFind, &fft) != 0);

    FindClose(hFind);

#else
    struct dirent *asset;
    DIR *dir = opendir(caminho);

    if (dir == NULL)
    {
        perror("Erro ao abrir diretório");
        free(nome_arquivos);
        return NULL;
    }

    int quantNomes = 0;

    while ((asset = readdir(dir)) != NULL)
    {
        if (strstr(asset->d_name, ".png") != NULL)
        {
            if (quantNomes < maxQuantNomes)
            {
                nome_arquivos[quantNomes] = malloc(strlen(asset->d_name) + 1);
                if (nome_arquivos[quantNomes] != NULL)
                {
                    strcpy(nome_arquivos[quantNomes], asset->d_name);
                    quantNomes++;
                }
                else
                {
                    perror("Erro ao alocar memória");

                    // Libera a memória já alocada antes de retornar
                    for (int i = 0; i < quantNomes; i++)
                    {
                        free(nome_arquivos[i]);
                    }
                    free(nome_arquivos);
                    closedir(dir);
                    return NULL;
                }
            }
            else
            {
                break;
            }
        }
    }
    closedir(dir);

#endif
    if (quantNomes < maxQuantNomes)
    {
        nome_arquivos[quantNomes] = NULL;
    }
    else
    {
        nome_arquivos[maxQuantNomes] = NULL;
    }
    return nome_arquivos;
}
// Função para liberar a memória da lista de nomes
void liberar_assets(char **nomes, int maxQuantNomes)
{
    if (nomes == NULL)
    {
        perror("O nomes ja foram liberados");
        return;
    }

    for (int i = 0; i < maxQuantNomes; i++)
    {
        free(nomes[i]);
    }
    free(nomes);
}
