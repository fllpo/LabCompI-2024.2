#ifndef NPC_H
#define NPC_H

#include "utils.h"
typedef struct Npc
{
    float x, y, h, w, velocidadeY;
    int vida, velocidade_movimento, forca_salto;
    bool movDireita, movEsquerda, pulando, direcao, nochao, resgatado;

} Npc;

Npc npc;
bool iniciaNPC(Npc *npc);
void atualizaNPC(Npc *inimigo, Player *jogador);
void desenhaNPC(Npc *inimigo);

#endif
