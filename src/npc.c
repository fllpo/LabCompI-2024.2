#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/npc.h"

Npc *npc = NULL;
int num_npcs;

bool criaNPCs(int quantidade)
{

    if (npc != NULL)
    {
        free(npc);
        npc = NULL;
    }

    npc = (Npc *)calloc(quantidade, sizeof(Npc));
    if (npc == NULL)
        return false;

    num_npcs = quantidade;

    for (int i = 0; i < num_npcs; i++)
        iniciaNPC(&npc[i]);

    return true;
}

bool iniciaNPC(Npc *npc)
{
    npc->viradoParaEsquerda = 0;
    npc->h = 50;
    npc->w = 50;
    npc->x = rand() % (4500 - 2000) + 2000;
    npc->y = TELA_ALTURA - npc->h - 50;
    npc->velocidadeY = 0;
    npc->velocidade_movimento = 200;
    npc->resgatado = false;
    npc->nochao = true;
    npc->posicao_fila = -1;

    // Carregando texturas
    char caminho[256];
    npc_textura = (SDL_Texture **)calloc(3, sizeof(SDL_Texture *));
    for (int i = 0; i < 3; i++)
    {
        snprintf(caminho, sizeof(caminho), "assets/img/Characters/Enemies and NPC/bunny/sprites/bunny%d.png", i + 1);
        npc_textura[i] = IMG_LoadTexture(renderizador, caminho);
        if (npc_textura[i] == NULL)
        {
            printf("Erro ao carregar textura %d para bunny: %s\n", i + 1, IMG_GetError());
            return false;
        }
    }
    return true;
}

void atualizaTodosNPCs(Jogador *jogador)
{
    for (int i = 0; i < num_npcs; i++)
    {
        atualizaNPC(&npc[i], jogador);
    }
}

void desenhaTodosNPCs()
{
    for (int i = 0; i < num_npcs; i++)
    {
        desenhaNPC(&npc[i]);
    }
}

void verificaTodasColisoesNPC(Jogador *jogador)
{
    for (int i = 0; i < num_npcs; i++)
    {
        colisaoJogadorNPC(jogador, &npc[i]);
    }
}

void liberaNPCs()
{
    if (npc != NULL)
    {
        free(npc);
        npc = NULL;
        num_npcs = 0;
    }
}

void movimentoHorizontalNPC(Npc *npc, Jogador *jogador)
{
    if (npc->resgatado)
    {
        float posicao_x = npc->x;

        if (jogador->viradoParaEsquerda)
        {
            posicao_x = jogador->x + 70 + (npc->posicao_fila * 50);
        }
        else
        {
            posicao_x = jogador->x - 50 + (npc->posicao_fila * 50);
        }

        if (npc->x + 20 < posicao_x)
        {
            npc->x += jogador->velocidade_movimento * deltaTime;
            npc->viradoParaEsquerda = 0;
        }
        if (npc->x - 20 > posicao_x)
        {
            npc->x -= jogador->velocidade_movimento * deltaTime;
            npc->viradoParaEsquerda = 1;
        }
    }
    else
    {
        npc->x = npc->x;
    }
}

bool verificarColisaoChaoNPC(Npc *npc)
{
    if (npc->y >= TELA_ALTURA - npc->h - 50)
    {
        npc->y = TELA_ALTURA - npc->h - 50;
        npc->nochao = true;
        npc->velocidadeY = 0;
        return true;
    }
    return false;
}

void movimentoVerticalNPC(Npc *npc, Jogador *jogador)
{
    if (npc->resgatado)
    {
        npc->y = jogador->y + npc->h;
    }
}

void atualizaFilaNPC(Npc *npc, Jogador *jogador)
{
    npc->posicao_fila = 0;
    if (npc->resgatado)
    {
        for (int i = 0; i < num_npcs; i++)
        {
            if (&npc[i] == npc)
            {
                break;
            }
            if (npc[i].resgatado)
            {
                npc->posicao_fila++;
            }
        }
    }
}

void atualizaNPC(Npc *npc, Jogador *jogador)
{
    atualizaFilaNPC(npc, jogador);
    movimentoHorizontalNPC(npc, jogador);
    movimentoVerticalNPC(npc, jogador);
}

void desenhaNPC(Npc *npc)
{

    SDL_Rect rectNpc = {npc->x + jogador.scrollX, npc->y, npc->w, npc->h};
    SDL_Texture *texturaAtual;

    if (!jogador.nochao)
    {
        texturaAtual = (npc->velocidadeY > 0) ? npc_textura[1] : npc_textura[2];
    }
    if (jogador.movDireita || jogador.movEsquerda)
    {
        texturaAtual = npc_textura[SDL_GetTicks() / 150 % 3];
    }
    else
    {
        if (npc->velocidadeY == 0)
        {
            texturaAtual = npc_textura[0];
        }
    }

    jogador.viradoParaEsquerda ? SDL_RenderCopyEx(renderizador, texturaAtual, NULL, &rectNpc, 0, NULL, SDL_FLIP_HORIZONTAL) : SDL_RenderCopy(renderizador, texturaAtual, NULL, &rectNpc);
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
            jogador->resgatando++;
        }
    }
}