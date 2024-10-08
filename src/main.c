#include "utils.c"
#include "jogador.c"
#include "telas.c"

void iniciaJogador(Player *quadrado)
{
    quadrado->vida = 3;
    quadrado->pontos = 0;
    quadrado->recorde = 0;
    quadrado->movDireita = false;
    quadrado->movEsquerda = false;
    quadrado->pulando = true;
    quadrado->x = TELA_LARGURA / 2 - quadrado->w;
    quadrado->y = TELA_ALTURA / 2 - quadrado->h;
}

int main(int argc, char *args[])
{
    printf("Para fins de teste:\nEspaco: pula e +100 pontos\nC: -1 vida\n");
    if (iniciaJanela())
    {
        telaApresentacao();
        telaInicial();
        while (raposa.fichas > 0)
        {
            iniciaJogador(&raposa);
            while (raposa.vida > 0)
            {
                telaJogo();
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
