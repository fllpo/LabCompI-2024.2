#include "utils.h"
#include "jogador.h"

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
    fonte = TTF_OpenFont("../assets/font/Roboto.ttf", 25);
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
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
    SDL_RenderClear(renderizador);

    renderizaJogador(&quadrado);
    exibeFichas(fichas);

    SDL_RenderPresent(renderizador);

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_TIME)
    {
        SDL_Delay(FRAME_TIME - frameTime);
    }
}

void processaEventos(SDL_Event *e)
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
                destroi(janela);
                exit(0);
            case SDLK_m:
                // menu();
                break;
            case SDLK_d:
                movDireita = true;

                break;
            case SDLK_a:
                movEsquerda = true;
                break;
            case SDLK_SPACE:
                if (!pulando)
                {
                    pulando = true;
                    velocidadeY = FORCA_SALTO;
                    alturaInicial = quadrado.y;
                }
                break;
            }
        }
        else if (e->type == SDL_KEYUP)
        {
            switch (e->key.keysym.sym)
            {
            case SDLK_d:
                movDireita = false;
                break;
            case SDLK_a:
                movEsquerda = false;
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

void escreveTexto(char *texto, int x, int y, SDL_Color cor)
{
    SDL_Surface *textoSuperficie = TTF_RenderText_Solid(fonte, texto, cor);
    SDL_Texture *textoTextura = SDL_CreateTextureFromSurface(renderizador, textoSuperficie);
    SDL_Rect textoPosicao = {x, y, 0, 0};
    SDL_FreeSurface(textoSuperficie);
    SDL_QueryTexture(textoTextura, NULL, NULL, &textoPosicao.w, &textoPosicao.h);
    SDL_RenderCopy(renderizador, textoTextura, NULL, &textoPosicao);
}

void inicio()
{

    for (int i = 0; i < 200; i++)
    {
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, i, 255);
        SDL_RenderPresent(renderizador);
    }

    int inicial = 1;

    while (inicial)
    {
        SDL_RenderClear(renderizador);

        escreveTexto("Por Andre, Fellipe e Guilherme.", 100, 100, BRANCO);
        escreveTexto("Pressione Enter", 200, 200, BRANCO);

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                destroi(janela);
                exit(0);
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    destroi(janela);
                    exit(0);
                case SDLK_RETURN:
                    inicial = 0;
                    fichas = 3;
                    break;
                }
            }
        }
        SDL_RenderPresent(renderizador);
    }
}