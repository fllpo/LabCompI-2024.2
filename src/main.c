#include "utils.c"
#include "jogador.c"
#include "telas.c"

void iniciaJogador(Player *quadrado)
{
    quadrado->vida = 3;
    quadrado->pontos = 0;
    quadrado->recorde = 0;
    quadrado->movDireita = false;
    quadrado->direcao = 0;
    quadrado->movEsquerda = false;
    quadrado->pulando = true;
    quadrado->x = TELA_LARGURA / 2 - quadrado->w;
    quadrado->y = TELA_ALTURA / 2 - quadrado->h;
}

int main(int argc, char *args[])
{
    printf("\nPara fins de teste:\n\nEspaco: +100 pontos\nC: -1 vida\nF: +3fichas\n");

    if (iniciaJanela() && carregaMidia())
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
