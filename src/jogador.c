#include "../include/utils.h"
#include "../include/jogador.h"

void moveJogador(SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump)
{
    SDL_Rect rectPlayer = {raposa.x, raposa.y, raposa.w, raposa.h};

    if (raposa.movDireita)
    {
        raposa.x += VELOCIDADE_MOVIMENTO;
        for (int i = 0; i < 6; i++)
        {
            SDL_RenderClear(renderizador);
            SDL_RenderCopy(renderizador, run[i], NULL, &rectPlayer);
            SDL_RenderPresent(renderizador);
        }
        raposa.direcao = 0;
    }
    if (raposa.movEsquerda)
    {
        for (int i = 0; i < 6; i++)
        {
            SDL_RenderClear(renderizador);
            SDL_RenderCopyEx(renderizador, run[i], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
            SDL_RenderPresent(renderizador);
        }
        raposa.x -= VELOCIDADE_MOVIMENTO;
        raposa.direcao = 1;
    }

    if (raposa.pulando)
    {
        velocidadeY += GRAVIDADE;
        raposa.y += velocidadeY;

        if (velocidadeY > 0)
        {
            if (raposa.movEsquerda && raposa.pulando)
            {
                SDL_RenderClear(renderizador);
                SDL_RenderCopyEx(renderizador, jump[1], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
                SDL_RenderPresent(renderizador);
            }
            else if (raposa.pulando)
            {
                SDL_RenderClear(renderizador);
                SDL_RenderCopy(renderizador, jump[1], NULL, &rectPlayer);
                SDL_RenderPresent(renderizador);
            }
        }
        if (velocidadeY < 0)
        {

            if ((raposa.movEsquerda && raposa.pulando) || (raposa.direcao == 1 && raposa.pulando))
            {
                SDL_RenderClear(renderizador);
                SDL_RenderCopyEx(renderizador, jump[0], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
                SDL_RenderPresent(renderizador);
            }
            else if (raposa.direcao == 0 && raposa.pulando)
            {
                SDL_RenderClear(renderizador);
                SDL_RenderCopy(renderizador, jump[0], NULL, &rectPlayer);
                SDL_RenderPresent(renderizador);
            }
        }

        if (raposa.y >= TELA_ALTURA - raposa.h - 100)
        {
            raposa.y = TELA_ALTURA - raposa.h;
            raposa.pulando = false;
        }
    }
    if (!raposa.movDireita && !raposa.movEsquerda && !raposa.pulando)
    {
        int i = 0;

        if (raposa.direcao == 0)
        {
            while (i < 4)
            {
                SDL_RenderClear(renderizador);
                SDL_RenderCopy(renderizador, idle[i], NULL, &rectPlayer);
                SDL_RenderPresent(renderizador);
                i++;
            }
            while (i > 0)
            {
                i--;
                SDL_RenderClear(renderizador);
                SDL_RenderCopy(renderizador, idle[i], NULL, &rectPlayer);
                SDL_RenderPresent(renderizador);
            }
        }
        if (raposa.direcao == 1)
        {
            while (i < 4)
            {
                SDL_RenderClear(renderizador);
                SDL_RenderCopyEx(renderizador, idle[i], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
                SDL_RenderPresent(renderizador);
                i++;
            }
            while (i > 0)
            {
                i--;
                SDL_RenderClear(renderizador);
                SDL_RenderCopyEx(renderizador, idle[i], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
                SDL_RenderPresent(renderizador);
            }
        }
    }
}

void renderizaJogador(Player *raposa)
{
    frameStart = SDL_GetTicks();

    moveJogador(idle, run, jump);

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}