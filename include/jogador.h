#ifndef JOGADOR_H
#define JOGADOR_H

#include "utils.h"

#include "estruturas.h"

extern Jogador jogador;
SDL_Texture **idle;
SDL_Texture **run;
SDL_Texture **jump;

/*SDL_Texture *idle[8];
SDL_Texture *run[6];
SDL_Texture *jump[4];*/

void desenhaJogador(Jogador *jogador, SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump);
bool iniciaJogador(Jogador *jogador, int selecao);
void atualizaJogador(Jogador *jogador);
void colisaoJogadorInimigo(Jogador *jogador, Inimigo *inimigo);
void exibeVida(int vida);

#endif