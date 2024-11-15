#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/inimigo.h"

Inimigo inimigo = {TELA_LARGURA / 2, TELA_ALTURA / 2 - 25, 60, 60};

bool iniciaInimigo(Inimigo *inimigo)
{
    inimigo->vida = 1;
    inimigo->viradoParaEsquerda = 0;
    inimigo->pulando = true;
    inimigo->x = 50;
    inimigo->y = TELA_ALTURA / 2 - inimigo->h;
    inimigo->velocidadeY = 0;
    inimigo->velocidade_movimento = 200;
    return true;
}

void atualizaInimigo(Inimigo *inimigo, Jogador *jogador)
{

    // Movimento horizontal
    if (inimigo->x < jogador->x)
    {
        inimigo->x += inimigo->velocidade_movimento * deltaTime;
        inimigo->viradoParaEsquerda = 0;
    }
    if (inimigo->x > jogador->x)
    {
        inimigo->x -= inimigo->velocidade_movimento * deltaTime;
        inimigo->viradoParaEsquerda = 1;
    }

    // Pulo e queda
    if (inimigo->pulando || !inimigo->nochao)
    {
        inimigo->y += inimigo->velocidadeY;
        inimigo->velocidadeY += GRAVIDADE;

        if (inimigo->y >= TELA_ALTURA - inimigo->h - 50)
        {
            inimigo->y = TELA_ALTURA - inimigo->h - 50;
            inimigo->pulando = false;
            inimigo->nochao = true;
            inimigo->velocidadeY = 0;
        }
    }
}

void desenhaInimigo(Inimigo *inimigo)
{
    SDL_Rect rectInimigo = {inimigo->x + jogador.scrollX, inimigo->y, inimigo->w, inimigo->h};
    SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 255);
    SDL_RenderFillRect(renderizador, &rectInimigo);
}
void colisaoJogadorInimigo(Jogador *jogador, Inimigo *inimigo)
{
    if (jogador->x + jogador->w >= inimigo->x && jogador->x <= inimigo->x + inimigo->w &&
        jogador->y + jogador->h >= inimigo->y && jogador->y <= inimigo->y + inimigo->h)
    {
        if (jogador->resgatando == false)
        {
            jogador->vida--;
        }
        else if (jogador->resgatando == true)
        {
            jogador->resgatando = false;
        }
    }
}
