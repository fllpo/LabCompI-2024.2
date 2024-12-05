#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct
{
    float x, y, w, h, scrollX, velocidadeY, velocidade_movimento, forca_salto;
    int vida, pontos, resgatando, fichas, recorde, viradoParaEsquerda, num_jump, num_idle, num_run;
    bool nochao, imune, movDireita, movEsquerda, salta;
    char *personagem;

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

#endif