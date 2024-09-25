#include "utils.c"

int main(int argc, char *args[])
{
    if (iniciaJanela())
    {
        inicio();
        while (1)
        {
            frameStart = SDL_GetTicks();

            processarEventos(&e, &movDireita, &movEsquerda, &pulando,
                             &quadrado, &velocidadeY, &alturaInicial);

            // Movimento
            if (movDireita)
            {
                quadrado.x += VELOCIDADE_MOVIMENTO;
            }
            if (movEsquerda)
            {
                quadrado.x -= VELOCIDADE_MOVIMENTO;
            }
            if (pulando)
            {
                quadrado.y += velocidadeY;
                velocidadeY += GRAVIDADE;

                if (quadrado.y >= TELA_ALTURA - quadrado.h)
                {
                    quadrado.y = TELA_ALTURA - quadrado.h;
                    pulando = false;
                }
            }

            renderizaJogador(&quadrado);

            frameTime = SDL_GetTicks() - frameStart;

            if (frameTime < FRAME_TIME)
            {
                SDL_Delay(FRAME_TIME - frameTime);
            }
        }
    }
    else
    {
        destroi(janela);
        return 0;
    }
}
