#ifndef JOGADOR_H
#define JOGADOR_H

#include "utils.h"
#include "estruturas.h"
extern Jogador jogador;

static SDL_Texture **idle = NULL;
static SDL_Texture **run = NULL;
static SDL_Texture **jump = NULL;

void desenhaJogador(Jogador *jogador, SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump);
bool iniciaJogador(Jogador *jogador, int selecao);
void atualizaJogador(Jogador *jogador);
void colisaoJogadorInimigo(Jogador *jogador, Inimigo *inimigo);
void exibeVida(int vida);

#endif