#ifndef JOGADOR_H
#define JOGADOR_H

#include "utils.h"
typedef struct Player
{
    float x, y, h, w, velocidadeY;
    int vida, pontos, fichas, recorde, velocidade_movimento, forca_salto;
    bool movDireita, movEsquerda, pulando, direcao, nochao;

} Player;

Player jogador = {TELA_LARGURA / 2 - 25, TELA_ALTURA / 2 - 25, 100, 100};

SDL_Texture *idle[4];
SDL_Texture *run[6];
SDL_Texture *jump[2];

void desenhaJogador(Player *jogador, SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump);
bool iniciaJogador(Player *jogador, int selecao);
void atualizaJogador(Player *jogador);

void exibeVida(int vida);
#endif