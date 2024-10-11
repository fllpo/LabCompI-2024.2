#include "../include/utils.h"
#include "../include/jogador.h"

void moveJogador(SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump)
{
    SDL_Rect rectPlayer = {jogador.x, jogador.y, jogador.w, jogador.h};
    frameStart = SDL_GetTicks();

    // Movimento horizontal
    if (jogador.movDireita)
    {
        jogador.x += jogador.velocidade_movimento * deltaTime;
        jogador.direcao = 0;
    }
    if (jogador.movEsquerda)
    {
        jogador.x -= jogador.velocidade_movimento * deltaTime;
        jogador.direcao = 1;
    }

    // Pulo e queda
    if (jogador.pulando || !jogador.nochao)
    {
        jogador.y += jogador.velocidadeY;
        jogador.velocidadeY += GRAVIDADE;

        if (jogador.y >= TELA_ALTURA - jogador.h - 10) // Tratamento de colisão (chão)
        {
            jogador.y = TELA_ALTURA - jogador.h - 10;
            jogador.pulando = false;
            jogador.nochao = true;
            jogador.velocidadeY = 0;
        }
    }

    // Renderização
    SDL_RenderClear(renderizador);

    SDL_Texture *texturaAtual;
    if (jogador.pulando || !jogador.nochao)
    {
        texturaAtual = (jogador.velocidadeY > 0) ? jump[1] : jump[0];
    }
    else if (jogador.movDireita || jogador.movEsquerda)
    {
        texturaAtual = run[SDL_GetTicks() / 150 % 6]; // Animação de corrida mais lenta
    }
    else
    {
        texturaAtual = idle[SDL_GetTicks() / 300 % 4]; // Animação parado mais lenta
    }

    rectPlayer.x = jogador.x;
    rectPlayer.y = jogador.y;

    if (jogador.direcao == 1)
    {
        SDL_RenderCopyEx(renderizador, texturaAtual, NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        SDL_RenderCopy(renderizador, texturaAtual, NULL, &rectPlayer);
    }
    exibeFichas(jogador.fichas);
    exibePontos(jogador.pontos);
    SDL_RenderPresent(renderizador);

    // Controle de FPS
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

void renderizaJogador(Player *jogador)
{
    moveJogador(idle, run, jump);
}