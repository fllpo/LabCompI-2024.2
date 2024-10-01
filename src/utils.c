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
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
    SDL_RenderClear(renderizador);

    renderizaJogador(&quadrado);
    exibeVida(quadrado.vida);
    exibePontos(quadrado.pontos);

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < FRAME_TIME)
    {
        SDL_Delay(FRAME_TIME - frameTime);
    }
    SDL_RenderPresent(renderizador);
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
            case SDLK_c:
                quadrado.vida--;
                break;
            case SDLK_d:
                quadrado.movDireita = true;
                break;
            case SDLK_a:
                quadrado.movEsquerda = true;
                break;
            case SDLK_SPACE:
                if (!quadrado.pulando)
                {
                    quadrado.pulando = true;
                    velocidadeY = FORCA_SALTO;
                    alturaInicial = quadrado.y;
                }
                quadrado.pontos = quadrado.pontos + 100;

                break;
            }
        }
        else if (e->type == SDL_KEYUP)
        {
            switch (e->key.keysym.sym)
            {
            case SDLK_d:
                quadrado.movDireita = false;
                break;
            case SDLK_a:
                quadrado.movEsquerda = false;
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
    char texto[50];
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
}

void gravarRecordes(char *nomeJogador, int maiorPonto) // TODO: Ordenação de recordes; Receber nomes dinamicamente
{
    char registro[10];
    sprintf(registro, "%s %d\n", nomeJogador, maiorPonto);
    FILE *arquivo = fopen("src/bin/score.bin", "ab");
    if (arquivo != NULL)
    {
        fwrite(registro, sizeof(registro), 1, arquivo);
        fclose(arquivo);
    }
    else
        perror("Erro ao abrir arquivo score.bin");
}

void telaRecordes()
{

    FILE *arquivo = fopen("src/bin/score.bin", "rb");
    char score[10];

    int menu = 1;

    while (menu)
    {
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
        escreveTexto("Recorde", TELA_LARGURA / 2 - 50, 50, BRANCO);

        if (arquivo != NULL)
        {
            fseek(arquivo, 0, SEEK_SET);
            for (int i = 0; i < 15; i++)
            {
                fread(&score, sizeof(score), 1, arquivo);

                escreveTexto(score, TELA_LARGURA / 2 - 50, 100 + (i * 30), BRANCO);
            }
        }
        else
            perror("Erro ao abrir arquivo score.bin");

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
                    menu = 0;
                    break;
                case SDLK_r:
                    menu = 0;
                    break;
                }
            }
        }

        SDL_RenderPresent(renderizador);
    }
    fclose(arquivo);
}
void telaMenu()
{
}
void telaFinal()
{
    quadrado.fichas--;
    int final = 1;
    while (final)
    {
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
        if (quadrado.fichas == 0)
        {
            escreveTexto("Obrigado por jogar!", 200, 200, BRANCO);
            telaRecordes();
        }

        else
        {
            escreveTexto("Pressione Enter para jogar novamente", 200, 200, BRANCO);
            exibeFichas(quadrado.fichas);
        }

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
                    final = 0;
                    break;
                }
            }
        }
        SDL_RenderPresent(renderizador);
    }
    if (quadrado.recorde < quadrado.pontos)
    {
        quadrado.recorde = quadrado.pontos;
        gravarRecordes("FEL", quadrado.recorde);
    }
}

void telaInicial()
{

    for (int i = 0; i < 200; i++)
    {
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, i, 255);
        SDL_RenderPresent(renderizador);
    }

    int inicial = 1;
    quadrado.fichas = 3;

    while (inicial)
    {
        SDL_RenderClear(renderizador);

        escreveTexto("Por Andre, Fellipe e Guilherme.", 100, 100, BRANCO);
        escreveTexto("Pressione Enter para iniciar jogo", 200, 200, BRANCO);
        escreveTexto("Pressione R para recordes", 200, 300, BRANCO);
        exibeFichas(quadrado.fichas);

        escreveTexto("Use A,D e espaco para se movimentar", 200, 500, BRANCO);

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
                case SDLK_r:
                    telaRecordes();
                    break;
                case SDLK_RETURN:
                    inicial = 0;
                    break;
                }
            }
        }
        SDL_RenderPresent(renderizador);
    }
}