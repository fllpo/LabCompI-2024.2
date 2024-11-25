#ifndef JOGADOR_H
#define JOGADOR_H

#include "utils.h"
#include "estruturas.h"
extern Jogador jogador;

SDL_Texture **idle;
SDL_Texture **run;
SDL_Texture **jump;

void desenhaJogador(Jogador *jogador, SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump);
bool iniciaJogador(Jogador *jogador, int selecao);
void atualizaJogador(Jogador *jogador);
void colisaoJogadorInimigo(Jogador *jogador, Inimigo *inimigo);
void exibeVida(int vida);

#endif