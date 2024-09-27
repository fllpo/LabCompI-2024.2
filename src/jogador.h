#ifndef JOGADOR_H
#define JOGADOR_H

#include "utils.h"
typedef struct Player
{
    float x, y, h, w;
    int vida;
} Player;

Player quadrado = {TELA_LARGURA / 2 - 25, TELA_ALTURA / 2 - 25, 50, 50};
void renderizaJogador(Player *quadrado);
void moveJogador();
void exibeVida(Player *quadrado);

#endif