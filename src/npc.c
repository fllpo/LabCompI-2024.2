#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/npc.h"

bool iniciaNPC(Npc *npc)
{
    npc->vida = 1;
    npc->direcao = 0;
    npc->pulando = true;
    npc->h = 20;
    npc->w = 20;
    npc->x = TELA_LARGURA - 25;
    npc->y = TELA_ALTURA / 2 - npc->h;
    npc->velocidadeY = 0;
    npc->velocidade_movimento = 200;
    npc->resgatado = false;
    printf("NPC iniciado\n");
    return true;
}

void atualizaNPC(Npc *npc, Player *jogador)
{

    // Movimento horizontal
    if (npc->resgatado == true)
    {
        if (npc->x < jogador->x)
        {
            npc->x += jogador->velocidade_movimento * deltaTime;
            npc->direcao = 0;
        }
        if (npc->x > jogador->x)
        {
            npc->x -= jogador->velocidade_movimento * deltaTime;
            npc->direcao = 1;
        }

        // Pulo e queda
        if (jogador->pulando || !jogador->nochao)
        {
            npc->y += jogador->velocidadeY;
            npc->velocidadeY += GRAVIDADE;
            if (npc->y >= TELA_ALTURA - npc->h - 10)
            {
                npc->y = TELA_ALTURA - npc->h - 10;
                npc->pulando = false;
                npc->nochao = true;
                npc->velocidadeY = 0;
            }
        }
    }
    if (npc->resgatado == false)
    {
        npc->x = npc->x;
    }

    if (!npc->nochao)
    {
        npc->y += jogador->velocidadeY;
        npc->velocidadeY += GRAVIDADE;
        if (npc->y >= TELA_ALTURA - npc->h - 10)
        {
            npc->y = TELA_ALTURA - npc->h - 10;
            npc->pulando = false;
            npc->nochao = true;
            npc->velocidadeY = 0;
        }
    }
}

void desenhaNPC(Npc *npc)
{
    SDL_Rect rectNpc = {npc->x, npc->y, npc->w, npc->h};
    SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 255);
    SDL_RenderFillRect(renderizador, &rectNpc);
}
