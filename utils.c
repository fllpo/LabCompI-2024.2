#include "utils.h"

// Inicializa a janela e o renderizador
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
    fonte = TTF_OpenFont("Roboto.ttf", 25);
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

// Libera recursos e encerra o programa
void destroi(SDL_Window *janela)
{
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(janela);
    TTF_CloseFont(fonte);
    TTF_Quit();
    SDL_Quit();
    exit(0);
}

// Função para renderizar um jogador
void renderizaJogador(Player *quadrado)
{
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
    SDL_RenderClear(renderizador);

    SDL_SetRenderDrawColor(renderizador, 0, 100, 100, 255);
    SDL_Rect rectPlayer = {quadrado->x, quadrado->y, quadrado->w, quadrado->h};
    SDL_RenderFillRect(renderizador, &rectPlayer);

    SDL_RenderPresent(renderizador);
}

// Função para processar eventos
void processarEventos(SDL_Event *e, bool *movDireita, bool *movEsquerda, bool *pulando, Player *quadrado, float *velocidadeY, int *alturaInicial)
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
                *movDireita = true;
                break;
            case SDLK_a:
                *movEsquerda = true;
                break;
            case SDLK_SPACE:
                if (!*pulando)
                {
                    *pulando = true;
                    *velocidadeY = FORCA_SALTO;
                    *alturaInicial = quadrado->y;
                }
                break;
            }
        }
        else if (e->type == SDL_KEYUP)
        {
            switch (e->key.keysym.sym)
            {
            case SDLK_d:
                *movDireita = false;
                break;
            case SDLK_a:
                *movEsquerda = false;
                break;
            }
        }
    }
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

        // Texto Creditos
        SDL_Surface *textoSuperficie_Creditos = TTF_RenderText_Solid(fonte, "Por Andre, Fellipe e Guilherme.", BRANCO);
        SDL_Texture *textoTextura_Creditos = SDL_CreateTextureFromSurface(renderizador, textoSuperficie_Creditos);
        SDL_Rect posicao_Creditos = {100, 100, 0, 0};
        SDL_FreeSurface(textoSuperficie_Creditos);
        SDL_QueryTexture(textoTextura_Creditos, NULL, NULL, &posicao_Creditos.w, &posicao_Creditos.h);
        SDL_RenderCopy(renderizador, textoTextura_Creditos, NULL, &posicao_Creditos);

        // Texto "Pressione Enter"
        SDL_Surface *textoSuperficie_PressioneEnter = TTF_RenderText_Solid(fonte, "Pressione Enter", BRANCO);
        SDL_Texture *textoTextura_PressioneEnter = SDL_CreateTextureFromSurface(renderizador, textoSuperficie_PressioneEnter);
        SDL_Rect posicao_PressioneEnter = {200, 200, 0, 0};
        SDL_FreeSurface(textoSuperficie_PressioneEnter);
        SDL_QueryTexture(textoTextura_PressioneEnter, NULL, NULL, &posicao_PressioneEnter.w, &posicao_PressioneEnter.h);
        SDL_RenderCopy(renderizador, textoTextura_PressioneEnter, NULL, &posicao_PressioneEnter);

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