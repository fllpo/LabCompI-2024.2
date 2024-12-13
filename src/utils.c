#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/inimigo.h"
#include "../include/estruturas.h"
#include "../include/npc.h"
#include "../include/telas.h"
#include "../include/cenario.h"

void carregaSons()
{
    pulo_sfx = Mix_LoadWAV("assets/sfx/Jump 1.wav");
    coleta_sfx = Mix_LoadWAV("assets/sfx/Fruit collect 1.wav");
    hit_sfx = Mix_LoadWAV("assets/sfx/Hit damage 1.wav");
    seleciona_sfx = Mix_LoadWAV("assets/sfx/Select 1.wav");
    if (!pulo_sfx || !coleta_sfx || !hit_sfx || !seleciona_sfx)
    {
        printf("Erro ao carregar som: %s\n", Mix_GetError());
    }
}
int iniciaJanela(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Erro ao iniciar SDL: %s\n", SDL_GetError());
        return 0;
    }
    if (TTF_Init() < 0)
    {
        printf("Erro ao iniciar SDL_TTF: %s\n", TTF_GetError());
        return 0;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Erro ao iniciar SDL_mixer: %s\n", Mix_GetError());
        return 0;
    }
    carregaSons();

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
        if (run[i])
            SDL_DestroyTexture(run[i]);
        if (i < 4 && idle[i])
            SDL_DestroyTexture(idle[i]);
        if (i < 2 && jump[i])
            SDL_DestroyTexture(jump[i]);
    }
    Mix_FreeChunk(pulo_sfx);
    Mix_FreeChunk(coleta_sfx);
    Mix_FreeChunk(hit_sfx);
    Mix_FreeChunk(seleciona_sfx);
    Mix_CloseAudio();
    TTF_CloseFont(fonte);
    TTF_Quit();
    SDL_Quit();
    exit(0);
}
void exibePosicao(int x, int y)
{
    char texto[30];
    sprintf(texto, "X:%d Y:%d", x, y);
    escreveTexto(texto, TELA_LARGURA - 200, TELA_ALTURA - 50, BRANCO);
}
void exibeQtdResgatando(int qtd_resgatando)
{
    char texto[30];
    sprintf(texto, "qtd_resgatando:%d", qtd_resgatando);
    escreveTexto(texto, 40, TELA_ALTURA - 50, BRANCO);
}
void fadeOut()
{
    for (int i = 0; i <= 255; i++)
    {
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, i);
        SDL_SetRenderDrawBlendMode(renderizador, SDL_BLENDMODE_BLEND);
        SDL_RenderFillRect(renderizador, NULL);
        SDL_RenderPresent(renderizador);
    }
}

bool verificaFimDeJogo(Jogador *jogador)
{
    if (jogador->x > 5200 && jogador->resgatando == num_npcs)
    {
        jogador->movDireita = true;
        if (jogador->x >= 6000)
        {
            jogador->movDireita = jogador->movEsquerda = false;
            jogador->x = 6000;
            return true;
        }
    }
    return false;
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

    // exibeVida(jogador.vida);
    // exibePontos(jogador.pontos);
    exibePosicao(jogador.x, jogador.y); // fins de teste
    // exibeQtdResgatando(jogador.resgatando); // fins de teste

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
            case SDLK_d:
                jogador->movDireita = true;
                break;
            case SDLK_a:
                jogador->movEsquerda = true;
                break;
            case SDLK_SPACE:
                Mix_PlayChannel(-1, pulo_sfx, 0);
                jogador->salta = true;
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
            case SDLK_SPACE:
                jogador->salta = false;
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

    SDL_FreeSurface(textoPreto);
    SDL_FreeSurface(textoBranco);
    SDL_DestroyTexture(texturaPreto);
    SDL_DestroyTexture(texturaBranco);
}
