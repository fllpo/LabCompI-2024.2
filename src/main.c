#include <stdio.h>
#include "utils.c"
#include "jogador.c"
#include "telas.c"

bool iniciaJogador(Player *jogador, int selecao)
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
       const char *personagem;
    int num_idle, num_run, num_jump;

    switch(selecao) {
        case 0:
            personagem = "Foxy";
            num_idle = 4;
            num_run = 6;
            num_jump = 2;
            break;
        case 1:
            personagem = "Squirrel";
            num_idle = 8;
            num_run = 6;
            num_jump = 4;
            break;
        case 2:
            personagem = "sunny-bunny";
            num_idle = 4;  // Ajuste esses números conforme necessário
            num_run = 6;
            num_jump = 5;
            break;
        case 3:
            personagem = "Fiery Imp";
            num_idle = 4;  // Ajuste esses números conforme necessário
            num_run = 8;
            num_jump = 5;
            break;
        default:
            printf("Seleção de personagem inválida.\n");
            return false;
    }

    char caminho[256];

    // Carregando texturas idle
    for (int i = 0; i < num_idle; i++) {
        snprintf(caminho, sizeof(caminho), "assets/img/Characters/Players/%s/Sprites/idle/player-idle-%d.png", personagem, i+1);
        idle[i] = IMG_LoadTexture(renderizador, caminho);
        if (idle[i] == NULL) {
            printf("Erro ao carregar textura idle %d para %s: %s\n", i+1, personagem, IMG_GetError());
            return false;
        }
    }

    // Carregando texturas run
    for (int i = 0; i < num_run; i++) {
        snprintf(caminho, sizeof(caminho), "assets/img/Characters/Players/%s/Sprites/run/player-run-%d.png", personagem, i+1);
        run[i] = IMG_LoadTexture(renderizador, caminho);
        if (run[i] == NULL) {
            printf("Erro ao carregar textura run %d para %s: %s\n", i+1, personagem, IMG_GetError());
            return false;
        }
    }

    // Carregando texturas jump
    for (int i = 0; i < num_jump; i++) {
        snprintf(caminho, sizeof(caminho), "assets/img/Characters/Players/%s/Sprites/jump/player-jump-%d.png", personagem, i+1);
        jump[i] = IMG_LoadTexture(renderizador, caminho);
        if (jump[i] == NULL) {
            printf("Erro ao carregar textura jump %d para %s: %s\n", i+1, personagem, IMG_GetError());
            return false;
        }
    }

    printf("Todas as texturas carregadas com sucesso para %s.\n", personagem);
    return true;
}

int main(int argc, char *args[])
{
    printf("\nPara fins de teste:\n\nEspaco: +100 pontos\nC: -1 vida\nF: +3 fichas (ao acabar o jogo)\n");

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
            else
            {
                printf("Falha ao iniciar o jogador. Encerrando o jogo.\n");
                destroi(janela);
                return 1;
            }
        }
    }
    else
    {
        printf("Falha ao iniciar a janela. Encerrando o jogo.\n");
        destroi(janela);
        return 1;
    }

    destroi(janela);
    return 0;
}
