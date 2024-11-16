#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct
{
    float x, y, w, h, scrollX, velocidadeY, velocidade_movimento, forca_salto;
    int vida, pontos, fichas, recorde, viradoParaEsquerda, num_jump, num_idle, num_run;
    bool pulando, nochao, imune, resgatando, movDireita, movEsquerda;

} Jogador;

typedef struct
{
    float x, y, w, h, velocidadeY, velocidade_movimento;
    int direcao, viradoParaEsquerda, vida;
    bool ativo, nochao, pulando;

} Inimigo;
typedef struct
{
    float x, y;
    float velocidadeY;
    int w, h;
    bool viradoParaEsquerda;
    bool pulando;
    bool nochao;
    float velocidade_movimento;
    bool resgatado;
} Npc;
typedef struct
{
    int x, y, w, h;
} Plataforma;
#endif