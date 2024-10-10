#include "utils.c"
#include "jogador.c"
#include "telas.c"

bool iniciaJogador(Player *jogador, int selecao)
{
    if (selecao == 1) // Personagem raposa
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
        jogador->velocidade_movimento = 250;
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
    return 1;
}

int main(int argc, char *args[])
{
    printf("\nPara fins de teste:\n\nEspaco: +100 pontos\nC: -1 vida\nF: +3fichas (ao acabar o jogo)\n");

    if (iniciaJanela())
    {
        telaApresentacao();
        telaInicial();
        int selecao = telaSelecaoPersonagem();
        while (jogador.fichas > 0)
        {
            if (iniciaJogador(&jogador, selecao))
            {
                while (jogador.vida > 0)
                {
                    Uint32 frameStart = SDL_GetTicks();
                    deltaTime = (frameStart - lastFrame) / 1000.0f;
                    lastFrame = frameStart;

                    telaJogo();

                    Uint32 frameTime = SDL_GetTicks() - frameStart;
                    if (frameTime < FRAME_DELAY)
                    {
                        SDL_Delay(FRAME_DELAY - frameTime);
                    }
                }
                telaFinal();
            }
        }
    }
    else
    {
        destroi(janela);
        return 0;
    }
}
