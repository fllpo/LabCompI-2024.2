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

    renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);
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
    TTF_CloseFont(fonte);
    TTF_Quit();
    SDL_Quit();
    exit(0);
}

void renderiza()
{
    frameStart = SDL_GetTicks();

    renderizaJogador(&raposa);
    exibeVida(raposa.vida);
    exibePontos(raposa.pontos);

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_TIME)
    {
        SDL_Delay(FRAME_TIME - frameTime);
    }
}

void processaEventosJogo(SDL_Event *e)
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
                raposa.vida--;
                break;
            case SDLK_d:
                raposa.movDireita = true;
                break;
            case SDLK_a:
                raposa.movEsquerda = true;
                break;
            case SDLK_SPACE:
                if (!raposa.pulando)
                {
                    raposa.pulando = true;
                    velocidadeY = FORCA_SALTO;
                    alturaInicial = raposa.y;
                }
                raposa.pontos = raposa.pontos + 100;
                break;
            }
        }
        else if (e->type == SDL_KEYUP)
        {
            switch (e->key.keysym.sym)
            {
            case SDLK_d:
                raposa.movDireita = false;
                break;
            case SDLK_a:
                raposa.movEsquerda = false;
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

void gravarRecordes(char *nomeJogador, int maiorPonto) // TODO: Ordenação de recordes; Receber nomes dinamicamente
{
    char registro[10];
    sprintf(registro, "%s %d\n", nomeJogador, maiorPonto);
    FILE *arquivo = fopen("bin/score.bin", "ab");
    if (arquivo != NULL)
    {
        fwrite(registro, sizeof(registro), 1, arquivo);
        fclose(arquivo);
    }
    else
        perror("Erro ao abrir arquivo score.bin");
}
