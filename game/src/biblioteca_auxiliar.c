#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raygui.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "Biblioteca_auxiliar.h"

// =-----------------------------------------= O ARQUIVO "BIBLIOTECA_AUXILIAR.H" EXPLICA O QUE CADA FUNÇÃO FAZ =---------------------------------------------

bool Animacao(Texture2D Imagem_sprites, int quantidade_frames, int *frame, 
              Rectangle *source, Vector2 posicao, float updatetime, float *runningtime) 
{
    bool finalizado = false;
    int contador = 0;
    float deltatime = GetFrameTime();
    *runningtime += deltatime;

    if (*runningtime >= updatetime) 
    {
        *runningtime = 0.0f;
        *frame+= 1;

        if (*frame == quantidade_frames)
        {
            contador++;
        }
        

        if (*frame > quantidade_frames)
        {
            *frame = 0;
        }

        source->x = *frame * (float) source->width;
    }
    DrawTextureRec(Imagem_sprites, *source, posicao, WHITE); // Desenho do frame atual

    if (contador == 1)
    {
        finalizado = !finalizado;
    }
    
    return finalizado;
}

int DrawBlackButton(Rectangle botao, const char *texto)
{
    int resultado = 0;

    //estado normal
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(BLACK));       // Fundo preto 
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));       // Texto branco 
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(DARKGRAY));  // Borda cinza escuro 

    //estado focado
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(BLACK));      // Fundo cinza escuro 
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(YELLOW));     // Texto amarelo
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(YELLOW));   // Borda amarela

    //estado pressionado
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(DARKGRAY));   // Fundo cinza escuro
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(YELLOW));     // Texto amarelo
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(YELLOW));   // Borda amarela 

    //configurando a fonte dos botões
    GuiSetFont(GetFontDefault());
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32); // Definindo o tamanho do texto

    if(GuiButton(botao, texto))
    {
        resultado = 1;
    }

    return resultado;
}

int DrawBlackSlider(Rectangle slider, const char *texto_esquerda, const char *texto_direita, float *variavel, float minimo, float maximo)
{
    int resultado = 0;

    //estado normal
    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, ColorToInt(BLACK));       // Fundo preto 
    GuiSetStyle(SLIDER, TEXT_COLOR_NORMAL, ColorToInt(WHITE));       // Texto branco 
    GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, ColorToInt(DARKGRAY));  // Borda cinza escuro 

    //estado focado
    GuiSetStyle(SLIDER, BASE_COLOR_FOCUSED, ColorToInt(BLACK));      // Fundo cinza escuro 
    GuiSetStyle(SLIDER, TEXT_COLOR_FOCUSED, ColorToInt(YELLOW));     // Texto amarelo
    GuiSetStyle(SLIDER, BORDER_COLOR_FOCUSED, ColorToInt(YELLOW));   // Borda amarela

    //estado pressionado
    GuiSetStyle(SLIDER, BASE_COLOR_PRESSED, ColorToInt(DARKGRAY));   // Fundo cinza escuro
    GuiSetStyle(SLIDER, TEXT_COLOR_PRESSED, ColorToInt(YELLOW));     // Texto amarelo
    GuiSetStyle(SLIDER, BORDER_COLOR_PRESSED, ColorToInt(YELLOW));   // Borda amarela 

    //configurando a fonte dos botões
    GuiSetFont(GetFontDefault());
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32); // Definindo o tamanho do texto

    if(GuiSlider(slider, texto_esquerda, texto_direita, variavel, minimo, maximo))
    {
        resultado = 1;
    }

    return resultado;
}

int DrawblankButton(Rectangle botao, const char *texto)
{
    int resultado = 0;

    //estado normal
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(BLANK));          // Fundo transparente
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));          // Texto branco 
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(BLANK));        // Borda transparente

    //estado focado
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(BLANK));         // Fundo transparente
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(YELLOW));        // Texto amarelo
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(BLANK));       // Borda transparente

    //estado pressionado
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(BLANK));         // Fundo transparente
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(YELLOW));        // Texto amarelo
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(YELLOW));      // Borda amarela 

    //configurando a fonte dos botões
    GuiSetFont(GetFontDefault());
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32); // Definindo o tamanho do texto

    if(GuiButton(botao, texto))
    {
        resultado = 1;
    }

    return resultado;
}

void Fakebutton(Rectangle botao, const char *texto)
{
    //estado normal
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(BLANK));          // Fundo transparente
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));          // Texto branco 
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(BLANK));        // Borda transparente

    //estado focado
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(BLANK));         // Fundo transparente
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(WHITE));        // Texto amarelo
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(BLANK));       // Borda transparente

    //estado pressionado
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(BLANK));         // Fundo transparente
    GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(WHITE));        // Texto amarelo
    GuiSetStyle(BUTTON, BORDER_COLOR_PRESSED, ColorToInt(BLACK));      // Borda amarela 

    //configurando a fonte dos botões
    GuiSetFont(GetFontDefault());
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32); // Definindo o tamanho do texto

    GuiButton(botao, texto);
}

void Tocar_Som(Sound som, bool audio_ligado)
{
    if (audio_ligado == true)
    {
        PlaySound(som);
    } 
}

char *Maiusculo(char* nome)
{
    int tamanho = strlen(nome);

    for (int i = 0; i < tamanho; i++)
    {    
        nome[i] = toupper(nome[i]);
    }
    
    return nome;
}