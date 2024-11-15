#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// Estrutura do jogador
typedef struct
{
    float x, y, w, h, scrollX, velocidadeY, velocidade_movimento, forca_salto;
    int vida, pontos, fichas, recorde, viradoParaEsquerda, num_jump, num_idle, num_run;
    bool pulando, nochao, imune, resgatando, movDireita, movEsquerda;

} Jogador;

// Estrutura do inimigo
typedef struct
{
    float x, y, w, h, velocidadeY, velocidade_movimento;
    int direcao, viradoParaEsquerda, vida;
    bool ativo, nochao, pulando;

} Inimigo;

// Estrutura do NPC
typedef struct
{
    float x, y, w, h, velocidade_movimento, velocidadeY;
    int viradoParaEsquerda;
    bool resgatado, nochao, pulando;
} Npc;

#endif