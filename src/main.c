#include "utils.c"
#include "jogador.c"

int main(int argc, char *args[])
{
    if (iniciaJanela())
    {
        inicio();
        while (1)
        {
            frameStart = SDL_GetTicks();

            processaEventos(&e);

            renderiza();
        }
    }
    else
    {
        destroi(janela);
        return 0;
    }
}
