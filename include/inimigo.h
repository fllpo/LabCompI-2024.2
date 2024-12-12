#ifndef INIMIGO_H
#define INIMIGO_H

#include "utils.h"
#include "estruturas.h"

extern Inimigo *inimigos;
extern int num_inimigos;
SDL_Texture **inimigo_textura;

bool criaInimigos(int quantidade);
bool iniciaInimigo(Inimigo *inimigo);
void atualizaTodosInimigos(Jogador *jogador);
void desenhaTodosInimigos(void);
void verificaTodasColisoesInimigo(Jogador *jogador);
void liberaInimigos(void);
void atualizaInimigo(Inimigo *inimigo, Jogador *jogador);
void desenhaInimigo(Inimigo *inimigo);
void colisaoJogadorInimigo(Jogador *jogador, Inimigo *inimigo);
bool verificarColisaoChaoInimigo(Inimigo *inimigo);

#endif
