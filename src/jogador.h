#ifndef JOGADOR_H
#define JOGADOR_H

#include "utils.h"
typedef struct Player
{
    float x, y, h, w;
    int vida, pontos, fichas, recorde;
    bool movDireita, movEsquerda, pulando;

} Player;
Player quadrado = {TELA_LARGURA / 2 - 25, TELA_ALTURA / 2 - 25, 50, 50};

int alturaInicial = 0;
void renderizaJogador(Player *quadrado);
void moveJogador();
void exibeVida(int vida);

#endif