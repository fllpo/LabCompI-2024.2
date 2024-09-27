#include "utils.h"
#include "jogador.h"

void moveJogador()
{
    if (movDireita)
    {
        quadrado.x += VELOCIDADE_MOVIMENTO;
    }
    if (movEsquerda)
    {
        quadrado.x -= VELOCIDADE_MOVIMENTO;
    }
    if (pulando)
    {
        quadrado.y += velocidadeY;
        velocidadeY += GRAVIDADE;

        if (quadrado.y >= TELA_ALTURA - quadrado.h)
        {
            quadrado.y = TELA_ALTURA - quadrado.h;
            pulando = false;
        }
    }
}

void renderizaJogador(Player *quadrado)
{
    moveJogador();
    SDL_SetRenderDrawColor(renderizador, 0, 100, 100, 255);
    SDL_Rect rectPlayer = {quadrado->x, quadrado->y, quadrado->w, quadrado->h};
    SDL_RenderFillRect(renderizador, &rectPlayer);
}