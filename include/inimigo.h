#ifndef INIMIGO_H
#define INIMIGO_H

#include "utils.h"
typedef struct Inimigo
{
    float x, y, h, w, velocidadeY;
    int vida, velocidade_movimento, forca_salto;
    bool movDireita, movEsquerda, pulando, direcao, nochao;

} Inimigo;

Inimigo inimigo = {TELA_LARGURA / 2 - 25, TELA_ALTURA / 2 - 25, 80, 80};

bool iniciaInimigo(Inimigo *inimigo);
void atualizaInimigo(Inimigo *inimigo);
void desenhaInimigo(Inimigo *inimigo);

#endif
