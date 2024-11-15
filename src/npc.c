#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/npc.h"

Npc npc;

bool iniciaNPC(Npc *npc)
{
    npc->viradoParaEsquerda = 0;
    npc->pulando = true;
    npc->h = 50;
    npc->w = 50;
    npc->x = TELA_LARGURA - 25;
    npc->y = TELA_ALTURA - 200;
    npc->velocidadeY = 0;
    npc->velocidade_movimento = 200;
    npc->resgatado = false;
    return true;
}

void atualizaNPC(Npc *npc, Jogador *jogador)
{

    // Movimento horizontal
    if (npc->resgatado == true)
    {
        if (npc->x + 50 < jogador->x)
        {
            npc->x += jogador->velocidade_movimento * deltaTime;
            npc->viradoParaEsquerda = 0;
        }
        if (npc->x - 100 > jogador->x)
        {
            npc->x -= jogador->velocidade_movimento * deltaTime;
            npc->viradoParaEsquerda = 1;
        }

        // Pulo e queda
        if (jogador->pulando || !jogador->nochao)
        {
            npc->y += jogador->velocidadeY;
            npc->velocidadeY += GRAVIDADE;

            if (npc->y >= TELA_ALTURA - npc->h - 50)
            {
                npc->y = TELA_ALTURA - npc->h - 50;
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
    SDL_Rect rectNpc = {npc->x + jogador.scrollX, npc->y, npc->w, npc->h};
    SDL_SetRenderDrawColor(renderizador, 0, 0, 255, 255);
    SDL_RenderFillRect(renderizador, &rectNpc);
}
void colisaoJogadorNPC(Jogador *jogador, Npc *npc)
{
    if (jogador->x + jogador->w >= npc->x && jogador->x <= npc->x + npc->w &&
        jogador->y + jogador->h >= npc->y && jogador->y <= npc->y + npc->h)
    {
        if (npc->resgatado == false)
        {
            jogador->pontos = jogador->pontos + 100;
            npc->resgatado = true;
        }
    }
}