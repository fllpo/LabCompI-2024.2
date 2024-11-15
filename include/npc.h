#ifndef NPC_H
#define NPC_H

#include "utils.h"
#include "estruturas.h"

extern Npc npc;
bool iniciaNPC(Npc *npc);
void atualizaNPC(Npc *inimigo, Jogador *jogador);
void desenhaNPC(Npc *inimigo);
void colisaoJogadorNPC(Jogador *jogador, Npc *npc);
#endif
