#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FPS 60
#define FRAME_TIME (1000 / FPS)
#define VELOCIDADE 3000
#define TELA_LARGURA 800
#define TELA_ALTURA 600
#define VELOCIDADE_MOVIMENTO 15
#define GRAVIDADE 1
#define FORCA_SALTO -15

float velocidadeY = 0;
int alturaInicial = 0;
int fichas = 0;
bool movDireita = false, movEsquerda = false, pulando = true;

typedef struct Player
{
    float x, y, h, w;
} Player;

SDL_Window *janela = NULL;
SDL_Renderer *renderizador = NULL;
SDL_Surface *telaSuperficie = NULL;
SDL_Color BRANCO = {255, 255, 255, 255};
SDL_Event e;
TTF_Font *fonte;

Player quadrado = {TELA_LARGURA / 2 - 25, TELA_ALTURA / 2 - 25, 50, 50};
Uint32 frameStart;
int frameTime;
int iniciaJanela();
void destroi();
void inicio();
void renderizaJogador(Player *quadrado);
void processarEventos(SDL_Event *e, bool *movDireita, bool *movEsquerda, bool *pulando, Player *quadrado, float *velocidadeY, int *alturaInicial);

#endif