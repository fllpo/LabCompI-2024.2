#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/inimigo.h"
#include "../include/npc.h"
#include "../include/estruturas.h"
#include "../include/cenario.h"

Jogador jogador = {TELA_LARGURA / 2 - 25, TELA_ALTURA / 2 - 25, 100, 100};
extern int qtd_plataformas;
extern Plataforma plataformas[];
void liberaJogador(Jogador *jogador)
{
    if (idle)
    {
        for (int i = 0; i < jogador->num_idle; i++)
        {
            if (idle[i])
                SDL_DestroyTexture(idle[i]);
        }
        free(idle);
        idle = NULL;
    }
    if (run)
    {
        for (int i = 0; i < jogador->num_run; i++)
        {
            if (run[i])
                SDL_DestroyTexture(run[i]);
        }
        free(run);
        run = NULL;
    }
    if (jump)
    {
        for (int i = 0; i < jogador->num_jump; i++)
        {
            if (jump[i])
                SDL_DestroyTexture(jump[i]);
        }
        free(jump);
        jump = NULL;
    }
}

bool iniciaJogador(Jogador *jogador, int selecao)
{
    jogador->vida = 1;
    jogador->pontos = 0;
    jogador->movDireita = false;
    jogador->viradoParaEsquerda = 0;
    jogador->movEsquerda = false;

    jogador->x = TELA_LARGURA / 2 - jogador->w;
    jogador->scrollX = 0;
    jogador->y = TELA_ALTURA / 2 - jogador->h;
    jogador->velocidadeY = 0;
    jogador->resgatando = 0;
    jogador->imune = false;
    const char *personagem;

    switch (selecao)
    {
    case 0:
        personagem = "Foxy";
        jogador->num_idle = 4;
        jogador->num_run = 6;
        jogador->num_jump = 2;
        jogador->velocidade_movimento = 1000;
        jogador->forca_salto = -80;

        break;
    case 1:
        personagem = "Squirrel";
        jogador->num_idle = 8;
        jogador->num_run = 6;
        jogador->num_jump = 4;
        jogador->velocidade_movimento = 1000;
        jogador->forca_salto = -60;

        break;
    default:
        printf("Seleção de personagem inválida.\n");
        return false;
    }

    char caminho[256];

    idle = (SDL_Texture **)calloc(jogador->num_idle, sizeof(SDL_Texture *));
    run = (SDL_Texture **)calloc(jogador->num_run, sizeof(SDL_Texture *));
    jump = (SDL_Texture **)calloc(jogador->num_jump, sizeof(SDL_Texture *));

    if (!idle || !run || !jump)
    {
        liberaJogador(jogador);
        printf("Erro na alocação de memória para as texturas\n");
        return false;
    }

    // Carregando texturas idle
    for (int i = 0; i < jogador->num_idle; i++)
    {
        snprintf(caminho, sizeof(caminho), "assets/img/Characters/Players/%s/Sprites/idle/player-idle-%d.png", personagem, i + 1);
        idle[i] = IMG_LoadTexture(renderizador, caminho);

        if (idle[i] == NULL)
        {
            liberaJogador(jogador);
            printf("Erro ao carregar textura idle %d para %s: %s\n", i + 1, personagem, IMG_GetError());
            return false;
        }
    }

    // Carregando texturas run
    for (int i = 0; i < jogador->num_run; i++)
    {
        snprintf(caminho, sizeof(caminho), "assets/img/Characters/Players/%s/Sprites/run/player-run-%d.png", personagem, i + 1);
        run[i] = IMG_LoadTexture(renderizador, caminho);
        if (run[i] == NULL)
        {
            liberaJogador(jogador);
            printf("Erro ao carregar textura run %d para %s: %s\n", i + 1, personagem, IMG_GetError());
            return false;
        }
    }

    // Carregando texturas jump
    for (int i = 0; i < jogador->num_jump; i++)
    {
        snprintf(caminho, sizeof(caminho), "assets/img/Characters/Players/%s/Sprites/jump/player-jump-%d.png", personagem, i + 1);
        jump[i] = IMG_LoadTexture(renderizador, caminho);
        if (jump[i] == NULL)
        {
            liberaJogador(jogador);
            printf("Erro ao carregar textura jump %d para %s: %s\n", i + 1, personagem, IMG_GetError());
            return false;
        }
    }

    return true;
}

void aplicarGravidadeJogador(Jogador *jogador)
{
    jogador->y += jogador->velocidadeY;
    jogador->velocidadeY += GRAVIDADE;
}

bool verificarColisaoPlataformas(Jogador *jogador)
{
    for (int i = 0; i < qtd_plataformas; i++)
    {
        // Adiciona uma margem de segurança
        const float margem = 5.0f;

        bool dentroDosLimitesHorizontais =
            jogador->x + jogador->w - margem > plataformas[i].x &&
            jogador->x + margem < plataformas[i].x + plataformas[i].w;

        bool atingiuPorCima =
            jogador->y + jogador->h >= plataformas[i].y &&
            jogador->y + jogador->h <= plataformas[i].y + jogador->velocidadeY;

        if (dentroDosLimitesHorizontais && atingiuPorCima)
        {
            jogador->y = plataformas[i].y - jogador->h;
            jogador->velocidadeY = 0;
            return true;
        }
    }
    return false;
}

void jogadorSalta(Jogador *jogador)
{
    if (jogador->salta)
    {
        if (jogador->nochao || verificarColisaoPlataformas(jogador))
        {
            jogador->velocidadeY = jogador->forca_salto;
            jogador->nochao = false;
        }
        jogador->salta = false;
    }
}

void movimentoVerticalJogador(Jogador *jogador)
{

    aplicarGravidadeJogador(jogador);

    jogador->nochao = verificarColisaoPlataformas(jogador);

    if (jogador->salta && jogador->nochao)
    {
        jogador->velocidadeY = jogador->forca_salto;
        jogador->salta = false;
        jogador->nochao = false;
    }

    if (jogador->y > TELA_ALTURA + 50)
    {
        jogador->vida--;
    }
}

void movimentoHorizontalJogador(Jogador *jogador)
{
    if (jogador->movDireita)
    {
        jogador->x += jogador->velocidade_movimento * deltaTime;
        jogador->viradoParaEsquerda = 0;
    }
    if (jogador->movEsquerda)
    {
        jogador->x -= jogador->velocidade_movimento * deltaTime;
        jogador->viradoParaEsquerda = 1;
    }

    jogador->scrollX = -jogador->x + TELA_LARGURA / 2 - jogador->w;

    if (jogador->scrollX > 0)
    {
        jogador->scrollX = 0;
    }
    if (jogador->scrollX < -16 * 300)
    {
        jogador->scrollX = -16 * 300;
    }
}
void atualizaJogador(Jogador *jogador)
{
    movimentoVerticalJogador(jogador);
    movimentoHorizontalJogador(jogador);
}

void desenhaJogador(Jogador *jogador, SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump)
{
    SDL_Rect rectJogador = {jogador->x + jogador->scrollX, jogador->y, jogador->w, jogador->h};
    SDL_Rect srcRect = {0, 0, 0, 0}; // Retângulo de origem para recortar o sprite

    // Obtém as dimensões da textura atual
    SDL_Texture *texturaAtual;
    int texturaLargura, texturaAltura;

    if (!jogador->nochao)
    {
        texturaAtual = (jogador->velocidadeY > 0) ? jump[1] : jump[0];
    }
    else if (jogador->movDireita || jogador->movEsquerda)
    {
        texturaAtual = run[SDL_GetTicks() / 150 % jogador->num_run];
    }
    else
    {
        if (jogador->velocidadeY == 0)
        {
            texturaAtual = idle[SDL_GetTicks() / 300 % jogador->num_idle];
        }
    }

    SDL_QueryTexture(texturaAtual, NULL, NULL, &texturaLargura, &texturaAltura);

    // Configura o retângulo de origem
    srcRect.w = texturaLargura;
    srcRect.h = texturaAltura;

    // Se for o esquilo (verificando pela força do salto e velocidade)
    if (jogador->velocidade_movimento == 1000 && jogador->forca_salto == -60)
    {
        srcRect.h -= 10; // Reduz 20 pixels da altura apenas para o esquilo
    }

    jogador->imune ? SDL_SetTextureAlphaMod(texturaAtual, 128) : SDL_SetTextureAlphaMod(texturaAtual, 255);

    // Usa o srcRect para recortar o sprite
    if (jogador->viradoParaEsquerda)
    {
        SDL_RenderCopyEx(renderizador, texturaAtual, &srcRect, &rectJogador, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        SDL_RenderCopy(renderizador, texturaAtual, &srcRect, &rectJogador);
    }
}
