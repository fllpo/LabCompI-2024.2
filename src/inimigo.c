#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/inimigo.h"

Inimigo *inimigos = NULL;
int num_inimigos = 0;

bool criaInimigos(int quantidade)
{
    if (inimigos != NULL)
    {
        free(inimigos);
    }

    inimigos = (Inimigo *)malloc(quantidade * sizeof(Inimigo));
    if (inimigos == NULL)
    {
        return false;
    }

    num_inimigos = quantidade;

    for (int i = 0; i < num_inimigos; i++)
    {
        iniciaInimigo(&inimigos[i], i);
    }

    return true;
}

bool iniciaInimigo(Inimigo *inimigo, int index)
{
    inimigo->vida = 1;
    inimigo->h = 100;
    inimigo->w = 100;
    inimigo->x = TELA_LARGURA - (200 * (index + 1));
    inimigo->y = TELA_ALTURA - inimigo->h - 50;
    inimigo->viradoParaEsquerda = 0;
    inimigo->pulando = true;
    inimigo->velocidadeY = 0;
    inimigo->velocidade_movimento = 200;
    inimigo->nochao = true;

    // Carregando texturas
    char caminho[256];
    inimigo_textura = (SDL_Texture **)malloc(3 * sizeof(SDL_Texture *));
    for (int i = 0; i < 4; i++)
    {
        snprintf(caminho, sizeof(caminho), "assets/img/Characters/Enemies and NPC/Dog/Sprites/Dog/dog%d.png", i + 1);

        inimigo_textura[i] = IMG_LoadTexture(renderizador, caminho);
        if (inimigo_textura[i] == NULL)
        {
            printf("Erro ao carregar textura %d para bunny: %s\n", i + 1, IMG_GetError());
            return false;
        }
    }

    return true;
}

void atualizaTodosInimigos(Jogador *jogador)
{
    for (int i = 0; i < num_inimigos; i++)
    {
        atualizaInimigo(&inimigos[i], jogador);
    }
}

void desenhaTodosInimigos()
{
    for (int i = 0; i < num_inimigos; i++)
    {
        desenhaInimigo(&inimigos[i]);
    }
}

void verificaTodasColisoesInimigo(Jogador *jogador)
{
    for (int i = 0; i < num_inimigos; i++)
    {
        colisaoJogadorInimigo(jogador, &inimigos[i]);
    }
}

void liberaInimigos()
{
    if (inimigos != NULL)
    {
        free(inimigos);
        inimigos = NULL;
        num_inimigos = 0;
    }
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
    SDL_Texture *texturaAtual;

    /*if (!jogador.nochao)
    {
        texturaAtual = (inimigo->velocidadeY > 0) ? inimigo_textura[1] : inimigo_textura[2];
    }*/
    if (inimigo->velocidade_movimento != 0)
    {
        texturaAtual = inimigo_textura[SDL_GetTicks() / 150 % 4];
    }

    !inimigo->viradoParaEsquerda ? SDL_RenderCopyEx(renderizador, texturaAtual, NULL, &rectInimigo, 0, NULL, SDL_FLIP_HORIZONTAL) : SDL_RenderCopy(renderizador, texturaAtual, NULL, &rectInimigo);
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
