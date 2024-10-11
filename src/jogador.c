#include "../include/utils.h"
#include "../include/jogador.h"

void moveJogador(Player *jogador, SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump)
{
    SDL_Rect rectPlayer = {jogador->x, jogador->y, jogador->w, jogador->h};
    frameStart = SDL_GetTicks();

    // Movimento horizontal
    if (jogador->movDireita)
    {
        jogador->x += jogador->velocidade_movimento * deltaTime;
        jogador->direcao = 0;
    }
    if (jogador->movEsquerda)
    {
        jogador->x -= jogador->velocidade_movimento * deltaTime;
        jogador->direcao = 1;
    }

    // Pulo e queda
    if (jogador->pulando || !jogador->nochao)
    {
        jogador->y += jogador->velocidadeY;
        jogador->velocidadeY += GRAVIDADE;

        if (jogador->y >= TELA_ALTURA - jogador->h - 10) // Tratamento de colisão (chão)
        {
            jogador->y = TELA_ALTURA - jogador->h - 10;
            jogador->pulando = false;
            jogador->nochao = true;
            jogador->velocidadeY = 0;
        }
    }

    // Renderização
    SDL_RenderClear(renderizador);

    SDL_Texture *texturaAtual;
    if (jogador->pulando || !jogador->nochao)
    {
        texturaAtual = (jogador->velocidadeY > 0) ? jump[1] : jump[0];
    }
    else if (jogador->movDireita || jogador->movEsquerda)
    {
        texturaAtual = run[SDL_GetTicks() / 150 % 6]; // Animação de corrida mais lenta
    }
    else
    {
        texturaAtual = idle[SDL_GetTicks() / 300 % 4]; // Animação parado mais lenta
    }

    rectPlayer.x = jogador->x;
    rectPlayer.y = jogador->y;

    if (jogador->direcao == 1)
    {
        SDL_RenderCopyEx(renderizador, texturaAtual, NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        SDL_RenderCopy(renderizador, texturaAtual, NULL, &rectPlayer);
    }
    exibeVida(jogador->vida);
    exibePontos(jogador->pontos);
    SDL_RenderPresent(renderizador);

    // Controle de FPS
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}
bool iniciaJogador(Player *jogador, int selecao)
{
    if (selecao == 0) // Personagem raposa
    {

        jogador->vida = 3;
        jogador->pontos = 0;
        jogador->recorde = 0;
        jogador->movDireita = false;
        jogador->direcao = 0;
        jogador->movEsquerda = false;
        jogador->pulando = true;
        jogador->x = TELA_LARGURA / 2 - jogador->w;
        jogador->y = TELA_ALTURA / 2 - jogador->h;
        jogador->velocidadeY = 0;
        jogador->velocidade_movimento = 1000;
        jogador->forca_salto = -80;

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

        for (int i = 0; i < 6; i++)
        {
            if (run[i] == NULL)
                return 0;

            if (i < 4 && idle[i] == NULL)
            {
                return 0;
                if (i < 2 && idle[i] == NULL)
                    return 0;
            }
        }
    }
    if (selecao == 1) // Personagem esquilo
    {
        printf("Esquilo nao implementado\n");
        return 0;
    }

    return 1;
}