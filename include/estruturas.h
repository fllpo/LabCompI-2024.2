#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct
{
    float x, y, w, h, scrollX, velocidadeY, velocidade_movimento, forca_salto;
    int vida, pontos, fichas, recorde, viradoParaEsquerda, num_jump, num_idle, num_run;
    bool nochao, imune, resgatando, movDireita, movEsquerda, salta;

} Jogador;

typedef struct
{
    float x, y, w, h, velocidadeY, velocidade_movimento;
    int direcao, viradoParaEsquerda, vida;
    bool ativo, nochao, pulando;

} Inimigo;
typedef struct
{
    int w, h, posicao_fila;
    float x, y, velocidadeY, velocidade_movimento;
    bool viradoParaEsquerda, nochao, resgatado;
} Npc;
typedef struct
{
    int x, y, w, h;
} Plataforma;
typedef struct
{
    int x, y, w, h;
} Porta;

#endif