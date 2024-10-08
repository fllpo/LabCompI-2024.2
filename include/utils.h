#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FPS 30
#define FRAME_TIME (1000 / FPS)
#define VELOCIDADE 1000
#define TELA_LARGURA 800
#define TELA_ALTURA 600
#define VELOCIDADE_MOVIMENTO 20
#define GRAVIDADE 3
#define FORCA_SALTO -25

float velocidadeY = 0;

SDL_Window *janela = NULL;
SDL_Renderer *renderizador = NULL;
SDL_Surface *telaSuperficie = NULL;
SDL_Color BRANCO = {255, 255, 255, 255};
SDL_Color PRETO = {0, 0, 0, 255};
SDL_Event e;
TTF_Font *fonte;

Uint32 frameStart;
int frameTime;

void destroi();
void escreveTexto(char *texto, int x, int y, SDL_Color cor);
void exibeFichas(int fichas);
void exibePontos(int pontos);

#endif