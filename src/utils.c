#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/telas.h"

int iniciaJanela(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Erro ao iniciar SDL: %s\n", SDL_GetError());
        return 0;
    }
    if (TTF_Init() < 0)
    {
        printf("Erro ao iniciar TTF: %s\n", TTF_GetError());
        return 0;
    }
    fonte = TTF_OpenFont("assets/font/Roboto.ttf", 25);
    if (fonte == NULL)
    {
        printf("Erro ao encontrar fonte\n");
        return 0;
    }

    janela = SDL_CreateWindow("SDL",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              TELA_LARGURA,
                              TELA_ALTURA,
                              SDL_WINDOW_SHOWN);
    if (!janela)
    {
        printf("Erro ao criar a janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderizador)
    {
        printf("Erro ao criar o renderizador: %s\n", SDL_GetError());
        SDL_DestroyWindow(janela);
        SDL_Quit();
        return 0;
    }

    return 1;
}

void destroi(SDL_Window *janela)
{
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);

    for (int i = 0; i < 6; i++)
    {
        SDL_DestroyTexture(run[i]);
        if (i < 4)
        {
            SDL_DestroyTexture(idle[i]);
            if (i < 2)
            {
                SDL_DestroyTexture(jump[i]);
            }
        }
    }

    TTF_CloseFont(fonte);
    TTF_Quit();
    SDL_Quit();
    exit(0);
}

void renderiza()
{
    moveJogador(&jogador, idle, run, jump);
}

void processaEventosJogo(Player *jogador, SDL_Event *e)
{
    while (SDL_PollEvent(e))
    {
        if (e->type == SDL_QUIT)
        {
            destroi(janela);
            exit(0);
        }
        else if (e->type == SDL_KEYDOWN)
        {
            switch (e->key.keysym.sym)
            {
            case SDLK_ESCAPE:
                telaPause();
                break;
            case SDLK_c:
                jogador->vida--;
                break;
            case SDLK_d:
                jogador->movDireita = true;
                break;
            case SDLK_a:
                jogador->movEsquerda = true;
                break;
            case SDLK_SPACE:
                if (!jogador->pulando && jogador->nochao)
                {
                    jogador->pulando = true;
                    jogador->nochao = false;
                    jogador->velocidadeY = jogador->forca_salto;
                    jogador->pontos += 5;
                }
                break;
            }
        }
        else if (e->type == SDL_KEYUP)
        {
            switch (e->key.keysym.sym)
            {
            case SDLK_d:
                jogador->movDireita = false;
                break;
            case SDLK_a:
                jogador->movEsquerda = false;
                break;
            }
        }
    }
}
void exibeFichas(int fichas)
{
    char texto[10];
    sprintf(texto, "Fichas: %d", fichas);
    escreveTexto(texto, 10, 10, BRANCO);
}
void exibePontos(int pontos)
{
    char texto[30];
    sprintf(texto, "Pontos:%d", pontos);
    escreveTexto(texto, TELA_LARGURA - 200, 10, BRANCO);
}
void exibeVida(int vida)
{
    char texto[50];
    sprintf(texto, "Vida: %d", vida);
    escreveTexto(texto, 10, 10, BRANCO);
}
void escreveTexto(char *texto, int x, int y, SDL_Color cor)
{
    SDL_Surface *textoSuperficie = TTF_RenderText_Solid(fonte, texto, cor);
    SDL_Texture *textoTextura = SDL_CreateTextureFromSurface(renderizador, textoSuperficie);
    SDL_Rect textoPosicao = {x, y, 0, 0};
    SDL_FreeSurface(textoSuperficie);
    SDL_QueryTexture(textoTextura, NULL, NULL, &textoPosicao.w, &textoPosicao.h);
    SDL_RenderCopy(renderizador, textoTextura, NULL, &textoPosicao);
    SDL_DestroyTexture(textoTextura);
}

void gravarRecordes(char *nomeJogador, int maiorPonto)
{

    Recorde recordes[MAX_REGISTROS];
    int numRecordes = 0;
    FILE *arquivo = fopen("bin/score.bin", "rb");
    if (arquivo != NULL)
    {
        while (fread(&recordes[numRecordes], sizeof(Recorde), 1, arquivo) == 1 && numRecordes < MAX_REGISTROS)
        {
            numRecordes++;
        }
        fclose(arquivo);
    }
    else
        perror("Erro ao abrir arquivo score.bin");

    if (numRecordes < MAX_REGISTROS)
    {
        strncpy(recordes[numRecordes].nome, nomeJogador, sizeof(recordes[numRecordes].nome) - 1);
        recordes[numRecordes].nome[sizeof(recordes[numRecordes].nome) - 1] = '\n';
        recordes[numRecordes].pontos = maiorPonto;
        numRecordes++;
    }

    // Ordena os recordes
    for (int i = 0; i < numRecordes - 1; i++)
    {
        for (int j = 0; j < numRecordes - i - 1; j++)
        {
            if (recordes[j].pontos < recordes[j + 1].pontos)
            {
                Recorde temp = recordes[j];
                recordes[j] = recordes[j + 1];
                recordes[j + 1] = temp;
            }
        }
    }

    arquivo = fopen("bin/score.bin", "wb");
    if (arquivo != NULL)
    {
        for (int i = 0; i < numRecordes; i++)
        {
            fwrite(&recordes[i], sizeof(Recorde), 1, arquivo);
        }
        fclose(arquivo);
    }
    else
    {
        perror("Erro ao abrir arquivo score.bin para escrita");
    }
}
