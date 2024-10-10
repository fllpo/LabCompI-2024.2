#include "../include/utils.h"
#include "../include/jogador.h"

#define FORCA_SALTO -5.0f // Reduzimos a força do salto
// Removemos a definição de FPS daqui, pois já está definida em utils.h
#define FRAME_DELAY (1000 / FPS)

void moveJogador(SDL_Texture **idle, SDL_Texture **run, SDL_Texture **jump)
{
    SDL_Rect rectPlayer = {jogador.x, jogador.y, jogador.w, jogador.h};
    Uint32 frameStart = SDL_GetTicks();

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

        if (jogador.y >= TELA_ALTURA - jogador.h - 100) // Tratamento de colisão (chão)
        {
            jogador.y = TELA_ALTURA - jogador.h - 100;
            jogador.pulando = false;
            jogador.nochao = true;
            jogador.velocidadeY = 0;
        }
    }

    // Renderização
    SDL_RenderClear(renderizador);

    SDL_Texture* currentTexture;
    if (jogador.pulando || !jogador.nochao)
    {
        currentTexture = (jogador.velocidadeY > 0) ? jump[1] : jump[0];
    }
    else if (jogador.movDireita || jogador.movEsquerda)
    {
        currentTexture = run[SDL_GetTicks() / 150 % 6]; // Animação de corrida mais lenta
    }
    else
    {
        currentTexture = idle[SDL_GetTicks() / 300 % 4]; // Animação parado mais lenta
    }

    rectPlayer.x = jogador.x;
    rectPlayer.y = jogador.y;

    if (jogador.direcao == 1)
    {
        SDL_RenderCopyEx(renderizador, currentTexture, NULL, &rectPlayer, 0, NULL, SDL_FLIP_HORIZONTAL);
    }
    else
    {
        SDL_RenderCopy(renderizador, currentTexture, NULL, &rectPlayer);
    }

    SDL_RenderPresent(renderizador);

    // Controle de FPS
    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

void renderizaJogador(Player *jogador)
{
    moveJogador(idle, run, jump);
}
    
void inicializaJogador(Player *jogador)
{
    // ... outras inicializações ...
    jogador->velocidade_movimento = 100; // Alterado para int
    jogador->forca_salto = FORCA_SALTO;
    // ... resto do código ...
}