#include "../include/utils.h"
#include "../include/jogador.h"

void moveJogador(SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump)
{
    SDL_Rect rectPlayer = {jogador.x, jogador.y, jogador.w, jogador.h};

    if (jogador.movDireita)
    {
        jogador.x += jogador.velocidade_movimento;
        for (int i = 0; i < 6; i++)
        {
            frameStart = SDL_GetTicks();
            deltaTime = (frameStart - lastFrame) / 1000;
            lastFrame = frameStart;
            SDL_RenderClear(renderizador);
            SDL_RenderCopy(renderizador, run[i], NULL, &rectPlayer);
            frameTime = SDL_GetTicks() - frameStart;
            if (FRAME_DELAY > frameTime)
            {
                SDL_Delay(FRAME_DELAY - frameTime);
            }
            SDL_RenderPresent(renderizador);
        }
        jogador.direcao = 0;
    }
    if (jogador.movEsquerda)
    {
        jogador.x -= jogador.velocidade_movimento;
        for (int i = 0; i < 6; i++)
        {
            frameStart = SDL_GetTicks();
            SDL_RenderClear(renderizador);
            SDL_RenderCopyEx(renderizador, run[i], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
            frameTime = SDL_GetTicks() - frameStart;
            if (FRAME_DELAY > frameTime)
            {
                SDL_Delay(FRAME_DELAY - frameTime);
            }
            SDL_RenderPresent(renderizador);
        }
        jogador.direcao = 1;
    }

    if (jogador.pulando)
    {
        jogador.y += jogador.velocidadeY;
        jogador.velocidadeY += GRAVIDADE;

        if (jogador.velocidadeY > 0)
        {

            if (jogador.movEsquerda)
            {
                frameStart = SDL_GetTicks();
                SDL_RenderClear(renderizador);
                SDL_RenderCopyEx(renderizador, jump[1], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
                frameTime = SDL_GetTicks() - frameStart;
                if (FRAME_DELAY > frameTime)
                {
                    SDL_Delay(FRAME_DELAY - frameTime);
                }
                SDL_RenderPresent(renderizador);
            }
            else if (jogador.movDireita)
            {
                frameStart = SDL_GetTicks();
                SDL_RenderClear(renderizador);
                SDL_RenderCopy(renderizador, jump[1], NULL, &rectPlayer);
                frameTime = SDL_GetTicks() - frameStart;
                if (FRAME_DELAY > frameTime)
                {
                    SDL_Delay(FRAME_DELAY - frameTime);
                }
                SDL_RenderPresent(renderizador);
            }
        }
        if (jogador.velocidadeY <= 0)
        {
            if (jogador.movEsquerda || jogador.direcao == 1)
            {
                frameStart = SDL_GetTicks();
                SDL_RenderClear(renderizador);
                SDL_RenderCopyEx(renderizador, jump[0], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);

                frameTime = SDL_GetTicks() - frameStart;
                if (FRAME_DELAY > frameTime)
                {
                    SDL_Delay(FRAME_DELAY - frameTime);
                }

                SDL_RenderPresent(renderizador);
            }
            if (jogador.movDireita || jogador.direcao == 0)
            {
                frameStart = SDL_GetTicks();
                SDL_RenderClear(renderizador);
                SDL_RenderCopy(renderizador, jump[0], NULL, &rectPlayer);
                frameTime = SDL_GetTicks() - frameStart;
                if (FRAME_DELAY > frameTime)
                {
                    SDL_Delay(FRAME_DELAY - frameTime);
                }
                SDL_RenderPresent(renderizador);
            }
        }

        if (jogador.y >= TELA_ALTURA - jogador.h - 100) // Tratamento de colisão (chão)
        {
            jogador.y = TELA_ALTURA - jogador.h;
            jogador.pulando = false;
            jogador.nochao = true;
        }
    }
    if (!jogador.movDireita && !jogador.movEsquerda && !jogador.pulando)
    {
        int i = 0;

        if (jogador.direcao == 0)
        {
            while (i < 4)
            {
                frameStart = SDL_GetTicks();

                SDL_RenderClear(renderizador);
                SDL_RenderCopy(renderizador, idle[i], NULL, &rectPlayer);

                frameTime = SDL_GetTicks() - frameStart;
                if (FRAME_DELAY > frameTime)
                {
                    SDL_Delay(FRAME_DELAY - frameTime);
                }
                SDL_RenderPresent(renderizador);
                i++;
            }
            while (i > 0)
            {
                i--;
                frameStart = SDL_GetTicks();
                SDL_RenderClear(renderizador);
                SDL_RenderCopy(renderizador, idle[i], NULL, &rectPlayer);
                frameTime = SDL_GetTicks() - frameStart;

                if (FRAME_DELAY > frameTime)
                {
                    SDL_Delay(FRAME_DELAY - frameTime);
                }
                SDL_RenderPresent(renderizador);
            }
        }
        if (jogador.direcao == 1)
        {
            while (i < 4)
            {
                frameStart = SDL_GetTicks();
                SDL_RenderClear(renderizador);
                SDL_RenderCopyEx(renderizador, idle[i], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);

                frameTime = SDL_GetTicks() - frameStart;

                if (FRAME_DELAY > frameTime)
                {
                    SDL_Delay(FRAME_DELAY - frameTime);
                }
                SDL_RenderPresent(renderizador);
                i++;
            }
            while (i > 0)
            {
                i--;
                frameStart = SDL_GetTicks();
                SDL_RenderClear(renderizador);
                SDL_RenderCopyEx(renderizador, idle[i], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
                frameTime = SDL_GetTicks() - frameStart;

                if (FRAME_DELAY > frameTime)
                {
                    SDL_Delay(FRAME_DELAY - frameTime);
                }
                SDL_RenderPresent(renderizador);
            }
        }
    }
}

void renderizaJogador(Player *jogador)
{
    moveJogador(idle, run, jump);
}