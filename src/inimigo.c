#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/inimigo.h"

bool iniciaInimigo(Inimigo *inimigo)
{
    inimigo->vida = 1;
    inimigo->movDireita = false;
    inimigo->direcao = 0;
    inimigo->movEsquerda = false;
    inimigo->pulando = true;
    inimigo->x = 550;
    inimigo->y = TELA_ALTURA / 2 - inimigo->h;
    inimigo->velocidadeY = 0;

    return true;
}

void atualizaInimigo(Inimigo *inimigo)
{
    // Movimento horizontal
    if (inimigo->movDireita)
    {
        inimigo->x += inimigo->velocidade_movimento * deltaTime;
        inimigo->direcao = 0;
    }
    if (inimigo->movEsquerda)
    {
        inimigo->x -= inimigo->velocidade_movimento * deltaTime;
        inimigo->direcao = 1;
    }

    // Pulo e queda
    if (inimigo->pulando || !inimigo->nochao)
    {
        inimigo->y += inimigo->velocidadeY;
        inimigo->velocidadeY += GRAVIDADE;

        if (inimigo->y >= TELA_ALTURA - inimigo->h - 10)
        {
            inimigo->y = TELA_ALTURA - inimigo->h - 10;
            inimigo->pulando = false;
            inimigo->nochao = true;
            inimigo->velocidadeY = 0;
        }
    }
}

void desenhaInimigo(Inimigo *inimigo)
{
    SDL_Rect rectInimigo = {inimigo->x, inimigo->y, inimigo->w, inimigo->h};
    SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255);
    SDL_RenderFillRect(renderizador, &rectInimigo);
}
