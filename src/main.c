#include "utils.c"
#include "recordes.c"
#include "jogador.c"
#include "inimigo.c"
#include "telas.c"
#include "npc.c"
#include "cenario.c"

bool iniciaPersonagens(int selecao)
{
    iniciaJogador(&jogador, selecao);

    if (!criaNPCs(2))
        return false;

    if (!criaInimigos(2))
        return false;

    return true;
}

void gerenciarFrame(Uint32 frameStart)
{
    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_DELAY)
    {
        SDL_Delay(FRAME_DELAY - frameTime);
    }
}

void atualizarDeltaTime(Uint32 frameStart)
{
    deltaTime = (frameStart - lastFrame) / 1000.0f;
    lastFrame = frameStart;
}

void executarLoopJogo()
{
    while (jogador.vida > 0)
    {
        if (!verificaFimDeJogo(&jogador))
        {
            Uint32 frameStart = SDL_GetTicks();
            atualizarDeltaTime(frameStart);

            telaJogo();

            gerenciarFrame(frameStart);
        }
        else
            break;
    }
}

void limparRecursos()
{
    liberaNPCs();
    liberaInimigos();
    liberaJogador(&jogador);
    destroi(janela);
}

int main(int argc, char *args[])
{
    printf("Para fins de teste:\nRight Shift: +3 fichas (ao acabar o jogo)\n");

    if (!iniciaJanela())
    {
        printf("Falha ao iniciar a janela. Encerrando o jogo.\n");
        return 0;
    }

    telaApresentacao();

Inicio:

    telaInicial(&jogador);
    int selecao = telaSelecaoPersonagem(&jogador);

    while (1)
    {
        if (!iniciaPersonagens(selecao))
        {
            printf("Falha ao iniciar personagens. Encerrando o jogo.\n");
            destroi(janela);
            return 0;
        }

        executarLoopJogo();

        telaFinal(&jogador);

        if (jogador.fichas <= 0)
        {
            goto Inicio;
        }
    }

    limparRecursos();

    return 0;
}
