#ifndef UTILS_RECORDES_H
#define UTILS_RECORDES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    char nome[20];
    int pontos;
} Recorde;
#define MAX_REGISTROS 100
#define TAM_REGISTRO 50
#define MAX_RECORDES 10
#define ALTURA_LINHA 30
int carregarRecordes(Recorde *recordes);
void gravarRecordes(char *nomeJogador, int maiorPonto);
void adicionarNovoRecorde(Recorde *recordes, int *numRecordes, char *nomeJogador, int maiorPonto);
void ordenarRecordes(Recorde *recordes, int numRecordes);
void salvarRecordes(Recorde *recordes, int numRecordes);

#endif