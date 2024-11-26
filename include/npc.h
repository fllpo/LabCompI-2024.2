#ifndef NPC_H
#define NPC_H

#include "jogador.h"

extern Npc *npc;
extern int num_npcs;
SDL_Texture **npc_textura;
bool criaNPCs(int quantidade);
bool iniciaNPC(Npc *npc, int index);
void desenhaNPC(Npc *npc);
void atualizaNPC(Npc *npc, Jogador *jogador);
void atualizaTodosNPCs(Jogador *jogador);
void desenhaTodosNPCs(void);
void colisaoJogadorNPC(Jogador *jogador, Npc *npc);
void verificaTodasColisoesNPC(Jogador *jogador);
void liberaNPCs(void);

#endif
