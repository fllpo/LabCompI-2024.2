#ifndef JOGADOR_H
#define JOGADOR_H

#include "utils.h"
typedef struct Player
{
    float x, y, h, w;
    int vida, pontos, fichas, recorde;
    bool movDireita, movEsquerda, pulando, direcao;

} Player;

Player raposa = {TELA_LARGURA / 2 - 25, TELA_ALTURA / 2 - 25, 150, 150};

SDL_Texture *idle[4];
SDL_Texture *run[6];
SDL_Texture *jump[2];

int alturaInicial = 0;
void moveJogador(SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump);
void exibeVida(int vida);
void renderizaJogador(Player *raposa);

#endif