#include "../include/utils.h"
#include "../include/jogador.h"

void moveJogador(SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump)
{
    idle[0] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/idle/player-idle-1.png");
    idle[1] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/idle/player-idle-2.png");
    idle[2] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/idle/player-idle-3.png");
    idle[3] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/idle/player-idle-4.png");
    run[0] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/run/player-run-1.png");
    run[1] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/run/player-run-2.png");
    run[2] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/run/player-run-3.png");
    run[3] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/run/player-run-4.png");
    run[4] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/run/player-run-5.png");
    run[5] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/run/player-run-6.png");
    jump[0] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/jump/player-jump-1.png");
    jump[1] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/jump/player-jump-2.png");

    SDL_Rect rectPlayer = {raposa.x, raposa.y, raposa.w, raposa.h};

    if (raposa.movDireita)
    {
        for (int i = 0; i < 6; i++)
        {
            SDL_RenderClear(renderizador);
            SDL_RenderCopy(renderizador, run[i], NULL, &rectPlayer);
            SDL_RenderPresent(renderizador);
            SDL_DestroyTexture(run[i]);
        }
        raposa.x += VELOCIDADE_MOVIMENTO;
    }
    if (raposa.movEsquerda)
    {
        for (int i = 0; i < 6; i++)
        {
            SDL_RenderClear(renderizador);
            SDL_RenderCopyEx(renderizador, run[i], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
            SDL_RenderPresent(renderizador);
            SDL_DestroyTexture(run[i]);
        }
        raposa.x -= VELOCIDADE_MOVIMENTO;
    }

    if (raposa.pulando)
    {
        raposa.y += velocidadeY;
        velocidadeY += GRAVIDADE;

        if (velocidadeY > 0)
        {
            SDL_RenderClear(renderizador);

            if (raposa.movEsquerda && raposa.pulando)
            {
                SDL_RenderCopyEx(renderizador, jump[1], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
            }
            else if (raposa.pulando)
            {
                SDL_RenderCopy(renderizador, jump[1], NULL, &rectPlayer);
            }

            SDL_RenderPresent(renderizador);
            SDL_DestroyTexture(jump[1]);
        }
        if (velocidadeY < 0)
        {
            SDL_RenderClear(renderizador);

            if (raposa.movEsquerda && raposa.pulando)
            {
                SDL_RenderCopyEx(renderizador, jump[0], NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
            }
            else if (raposa.pulando)
            {
                SDL_RenderCopy(renderizador, jump[0], NULL, &rectPlayer);
            }

            SDL_RenderPresent(renderizador);
            SDL_DestroyTexture(jump[0]);
        }

        if (raposa.y >= TELA_ALTURA - raposa.h)
        {
            raposa.y = TELA_ALTURA - raposa.h;
            raposa.pulando = false;
        }
    }
    if (!raposa.movDireita && !raposa.movEsquerda && !raposa.pulando)
    {
        int i = 0;
        while (i < 4)
        {
            SDL_RenderClear(renderizador);
            SDL_RenderCopy(renderizador, idle[i], NULL, &rectPlayer);
            SDL_DestroyTexture(idle[i]);
            SDL_RenderPresent(renderizador);
            i++;
        }
        while (i > 0)
        {
            i--;
            SDL_RenderClear(renderizador);
            SDL_RenderCopy(renderizador, idle[i], NULL, &rectPlayer);
            SDL_DestroyTexture(idle[i]);

            SDL_RenderPresent(renderizador);
        }
    }
}

void renderizaJogador(Player *raposa)
{
    moveJogador(idle, run, jump);
}