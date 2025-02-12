#ifndef BIBLIOTECAAUXILIAR_H
#define BIBLIOTECAAUXILIAR_H

// Animação =----------------------------------------
bool Animacao(Texture2D Imagem_sprites, int quantidade_frames, int *frame,                  // Pega um sprite_sheet (arquivo.png com varios frames)
              Rectangle *source, Vector2 posicao, float updatetime, float *runningtime);    // e anima eles fazendo uma animação

// Estilos dos botões =-----------------------------
// Botão preto =---
int DrawBlackButton(Rectangle botao, const char *texto); // Cria um botão preto, usado apenas no menu do pause //
// Slider preto =---= Cria um slider preto, usado apenas no menu do pause //
int DrawBlackSlider(Rectangle slider, const char *texto_esquerda, const char *texto_direita, float *variavel, float minimo, float maximo); 
// Botão fundo transparente =---
int DrawblankButton(Rectangle botao, const char *texto); // Cria um botão com fundo transparente, usado apenas nas cartas //
// Botão inutil =---
void Fakebutton(Rectangle botao, const char *texto); // Cria um botão falso //

// Tocar Sound effects =----------------------------
void Tocar_Som(Sound som, bool audio_ligado); // toca um som (basicamente para automatizar o processo em uma linha apenas) //

char *Maiusculo(char* nome);

#endif