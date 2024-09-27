#include "utils.c"
#include "jogador.c"

int main(int argc, char *args[])
{
    printf("Para fins de teste:\n\nEspaco:pula e +100 pontos\nC:-1 vida\n");
    if (iniciaJanela())
    {
        telaInicial();
        while (fichas > 0)
        {
            quadrado.vida = 3;

            while (quadrado.vida > 0)
            {
                frameStart = SDL_GetTicks();
                processaEventos(&e);
                renderiza();
            }

            telaFinal();
        }
    }
    else
    {
        destroi(janela);
        return 0;
    }
}
