#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/inimigo.h"
#include "../include/estruturas.h"
#include "../include/npc.h"
#include "../include/telas.h"
#include "../include/cenario.h"

int iniciaJanela(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Erro ao iniciar SDL: %s\n", SDL_GetError());
        return 0;
    }
    if (TTF_Init() < 0)
    {
        printf("Erro ao iniciar TTF: %s\n", TTF_GetError());
        return 0;
    }
    fonte = TTF_OpenFont("assets/font/Roboto.ttf", 25);
    if (fonte == NULL)
    {
        printf("Erro ao encontrar fonte\n");
        return 0;
    }

    janela = SDL_CreateWindow("SDL",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              TELA_LARGURA,
                              TELA_ALTURA,
                              SDL_WINDOW_SHOWN);
    if (!janela)
    {
        printf("Erro ao criar a janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderizador)
    {
        printf("Erro ao criar o renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(janela);
        SDL_Quit();
        return 0;
    }

    return 1;
}

void destroi(SDL_Window *janela)
{
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);

    for (int i = 0; i < 6; i++)
    {
        SDL_DestroyTexture(run[i]);
        if (i < 4)
        {
            SDL_DestroyTexture(idle[i]);
            if (i < 2)
            {
                SDL_DestroyTexture(jump[i]);
            }
        }
    }

    TTF_CloseFont(fonte);
    TTF_Quit();
    SDL_Quit();
    exit(0);
}

void renderiza()
{
    SDL_RenderClear(renderizador);

    atualizaJogador(&jogador);
    atualizaTodosInimigos(&jogador);
    atualizaTodosNPCs(&jogador);

    desenhaCenario();
    desenhaTodosInimigos();
    desenhaJogador(&jogador, idle, run, jump);
    desenhaTodosNPCs();

    verificaTodasColisoesNPC(&jogador);
    verificaTodasColisoesInimigo(&jogador);

    exibeVida(jogador.vida);
    exibePontos(jogador.pontos);

    SDL_RenderPresent(renderizador);
    limitaFPS();
}

void limitaFPS()
{
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

void processaEventosJogo(Jogador *jogador, SDL_Event *e)
{
    while (SDL_PollEvent(e))
    {
        if (e->type == SDL_QUIT)
        {
            destroi(janela);
            exit(0);
        }
        else if (e->type == SDL_KEYDOWN)
        {
            switch (e->key.keysym.sym)
            {
            case SDLK_ESCAPE:
                telaPause();
                break;
            case SDLK_d:
                jogador->movDireita = true;
                break;
            case SDLK_a:
                jogador->movEsquerda = true;
                break;
            case SDLK_SPACE:
                if (jogador->nochao)
                {
                    jogador->nochao = false;
                    jogador->velocidadeY = jogador->forca_salto;
                }
                break;
            }
        }
        else if (e->type == SDL_KEYUP)
        {
            switch (e->key.keysym.sym)
            {
            case SDLK_d:
                jogador->movDireita = false;
                break;
            case SDLK_a:
                jogador->movEsquerda = false;
                break;
            }
        }
    }
}
void exibeFichas(int fichas)
{
    char texto[10];
    sprintf(texto, "Fichas: %d", fichas);
    escreveTexto(texto, 10, 10, BRANCO);
}
void exibePontos(int pontos)
{
    char texto[30];
    sprintf(texto, "Pontos:%d", pontos);
    escreveTexto(texto, TELA_LARGURA - 200, 10, BRANCO);
}
void exibeVida(int vida)
{
    char texto[50];
    sprintf(texto, "Vida: %d", vida);
    escreveTexto(texto, 10, 10, BRANCO);
}
void escreveTexto(char *texto, int x, int y, SDL_Color cor)
{
    // Renderiza o texto preto para a borda
    SDL_Surface *textoPreto = TTF_RenderText_Solid(fonte, texto, PRETO);
    SDL_Texture *texturaPreto = SDL_CreateTextureFromSurface(renderizador, textoPreto);
    SDL_Rect posicaoPreto = {x - 1, y - 1, 0, 0};
    SDL_QueryTexture(texturaPreto, NULL, NULL, &posicaoPreto.w, &posicaoPreto.h);

    SDL_Rect bordas[8] = {
        {x - 1, y - 1, posicaoPreto.w, posicaoPreto.h},
        {x + 1, y - 1, posicaoPreto.w, posicaoPreto.h},
        {x - 1, y + 1, posicaoPreto.w, posicaoPreto.h},
        {x + 1, y + 1, posicaoPreto.w, posicaoPreto.h},
        {x, y - 1, posicaoPreto.w, posicaoPreto.h},
        {x, y + 1, posicaoPreto.w, posicaoPreto.h},
        {x - 1, y, posicaoPreto.w, posicaoPreto.h},
        {x + 1, y, posicaoPreto.w, posicaoPreto.h}};

    for (int i = 0; i < 8; i++)
    {
        SDL_RenderCopy(renderizador, texturaPreto, NULL, &bordas[i]);
    }

    SDL_Surface *textoBranco = TTF_RenderText_Solid(fonte, texto, cor);
    SDL_Texture *texturaBranco = SDL_CreateTextureFromSurface(renderizador, textoBranco);
    SDL_Rect posicaoBranco = {x, y, posicaoPreto.w, posicaoPreto.h};
    SDL_RenderCopy(renderizador, texturaBranco, NULL, &posicaoBranco);

    // Libera os recursos
    SDL_FreeSurface(textoPreto);
    SDL_FreeSurface(textoBranco);
    SDL_DestroyTexture(texturaPreto);
    SDL_DestroyTexture(texturaBranco);
}
