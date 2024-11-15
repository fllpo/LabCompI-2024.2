#include "utils.c"
#include "utils_recordes.c"
#include "jogador.c"
#include "inimigo.c"
#include "telas.c"
#include "npc.c"
#include "cenario.c"

int iniciaPersonagens(int selecao)
{
    iniciaJogador(&jogador, selecao);
    iniciaNPC(&npc);
    iniciaInimigo(&inimigo);
    return 1;
}

int main(int argc, char *args[])
{

    printf("Para fins de teste:\n\nEspaco: +pontos\nF: +3 fichas (ao acabar o jogo)\n");

    if (iniciaJanela())
    {
        telaApresentacao();
        telaInicial(&jogador);
        int selecao = telaSelecaoPersonagem(&jogador);

        while (jogador.fichas > 0)
        {
            if (iniciaPersonagens(selecao))
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
                telaFinal(&jogador);
            }
            else
            {
                printf("Falha ao iniciar personagens. Encerrando o jogo.\n");
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