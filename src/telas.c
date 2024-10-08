
#include "../include/utils.h"
#include "../include/jogador.h"

void telaJogo()
{
    processaEventosJogo(&e);
    renderiza();
}

void telaRecordes() // OK
{
    char score[10];
    int menu = 1;
    FILE *arquivo = fopen("bin/score.bin", "rb");
    SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);

    while (menu)
    {
        SDL_RenderClear(renderizador);
        escreveTexto("Recordes", TELA_LARGURA / 2 - 50, 50, BRANCO);

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
                    menu = 0;
                    break;
                case SDLK_RETURN:
                    menu = 0;
                    break;
                }
            }
        }

        SDL_RenderPresent(renderizador);
    }
    fclose(arquivo);
}
void telaPause() // OK
{
    int pause = 1;
    escreveTexto("Pausado", TELA_LARGURA / 2 - 50, TELA_ALTURA / 2 - 50, BRANCO);
    SDL_RenderPresent(renderizador);
    while (pause)
    {
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
                    pause = 0;
                    break;
                case SDLK_p:
                    pause = 0;
                    break;
                }
            }
        }
    }
}
void telaFinal() // TODO
{
    raposa.fichas--;
    int final = 1;
    while (final)
    {
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
        if (raposa.fichas == 0)
        {
            escreveTexto("Obrigado por jogar!", 200, 200, BRANCO);
            telaRecordes();
        }

        else
        {
            escreveTexto("Pressione Enter para jogar novamente", 200, 200, BRANCO);
            exibeFichas(raposa.fichas);
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
    if (raposa.recorde < raposa.pontos)
    {
        raposa.recorde = raposa.pontos;
        gravarRecordes("FEL", raposa.recorde);
    }
}
void telaApresentacao() // OK
{
    SDL_Texture *img = IMG_LoadTexture(renderizador, "assets/img/rural_logo.png");
    SDL_SetTextureAlphaMod(img, 0);
    SDL_Rect r = {TELA_LARGURA / 2 - 150, TELA_ALTURA / 2 - 150, 300, 300};

    for (int i = 0; i < 255; i++)
    {
        SDL_RenderClear(renderizador);

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
                }
            }
        }
        if (i > 127 && i <= 255)
        {
            SDL_SetTextureAlphaMod(img, i * 2);
        }

        SDL_SetRenderDrawColor(renderizador, i, i, i, 255);
        SDL_RenderCopy(renderizador, img, NULL, &r);
        SDL_Delay(10);
        SDL_RenderPresent(renderizador);
    }

    SDL_Delay(1000);
    SDL_DestroyTexture(img);
}
void telaInstrucoes() // TODO
{

    int menu = 1;

    while (menu)
    {
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
        escreveTexto("Instrucoes", TELA_LARGURA / 2 - 50, TELA_ALTURA / 4 - 50, BRANCO);
        escreveTexto("A: esquerda", TELA_LARGURA / 2 - 50, TELA_ALTURA / 2 - 50, BRANCO);
        escreveTexto("D: direita", TELA_LARGURA / 2 - 50, TELA_ALTURA / 2, BRANCO);
        escreveTexto("Espaco: Saltar", TELA_LARGURA / 2 - 50, TELA_ALTURA / 2 + 50, BRANCO);

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
                    menu = 0;
                    break;
                case SDLK_RETURN:
                    menu = 0;
                    break;
                }
            }
        }

        SDL_RenderPresent(renderizador);
    }
}
void telaInicial() // OK
{

    int inicial = 1, selecao = 0;
    raposa.fichas = 3;

    while (inicial)
    {
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 200, 255);

        escreveTexto("Iniciar", 200, 200, PRETO);
        escreveTexto("Instrucoes", 200, 250, PRETO);
        escreveTexto("Recordes", 200, 300, PRETO);
        escreveTexto("Por Andre, Fellipe e Guilherme.", 10, TELA_ALTURA - 35, BRANCO);

        exibeFichas(raposa.fichas);

        switch (selecao)
        {
        case 0:
            escreveTexto("Iniciar", 200, 200, BRANCO);
            break;
        case 1:
            escreveTexto("Instrucoes", 200, 250, BRANCO);
            break;
        case 2:
            escreveTexto("Recordes", 200, 300, BRANCO);
            break;
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
                case SDLK_UP:
                    if (selecao > 0)
                        selecao--;
                    break;
                case SDLK_DOWN:
                    if (selecao < 2)
                        selecao++;
                    break;
                case SDLK_RETURN:
                    switch (selecao)
                    {
                    case 0:
                        inicial = 0;
                        break;
                    case 1:
                        telaInstrucoes();
                        break;
                    case 2:
                        telaRecordes();
                        break;
                    }
                    break;
                }
            }
        }
        SDL_RenderPresent(renderizador);
    }
}