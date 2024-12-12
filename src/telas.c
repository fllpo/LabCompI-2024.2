#include "../include/utils.h"
#include "../include/recordes.h"
#include "../include/jogador.h"
#include "../include/estruturas.h"

void telaJogo()
{
    processaEventosJogo(&jogador, &e);
    renderiza();
}

int telaSelecaoPersonagem(Jogador *jogador)
{
    int menu = 1, selecao = 0, num_personagens = 2;
    jogador->recorde = 0;
    SDL_Texture *personagens[num_personagens];
    SDL_Rect molduraExterna = {145, 145, 310, 310};
    SDL_Rect molduraInterna = {150, 150, 300, 300};
    SDL_Rect imagemRect = {160, 160, 280, 280};

    personagens[0] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/idle/player-idle-1.png");
    personagens[1] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Squirrel/Sprites/idle/player-idle-1.png");

    while (menu)
    {
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
        SDL_RenderClear(renderizador);

        SDL_SetRenderDrawColor(renderizador, 139, 69, 19, 255);
        SDL_RenderFillRect(renderizador, &molduraExterna);

        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
        SDL_RenderFillRect(renderizador, &molduraInterna);

        SDL_RenderCopy(renderizador, personagens[selecao], NULL, &imagemRect);

        escreveTexto("Raposa", 500, 200, BRANCO);
        escreveTexto("Esquilo", 500, 250, BRANCO);

        exibeFichas(jogador->fichas);

        switch (selecao)
        {
        case 0:
            escreveTexto("Raposa", 500, 200, AMARELO);
            break;
        case 1:
            escreveTexto("Esquilo", 500, 250, AMARELO);
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
                    exit(0);
                case SDLK_UP:
                    if (selecao > 0)
                    {
                        Mix_PlayChannel(-1, seleciona_sfx, 0);
                        selecao--;
                    }
                    break;
                case SDLK_DOWN:
                    if (selecao < 1)
                    {
                        Mix_PlayChannel(-1, seleciona_sfx, 0);
                        selecao++;
                    }
                    break;
                case SDLK_RETURN:
                    Mix_PlayChannel(-1, seleciona_sfx, 0);
                    menu = 0;
                    break;
                }
            }
        }
        SDL_RenderPresent(renderizador);
    }

    for (int i = 0; i < num_personagens; i++)
    {
        SDL_DestroyTexture(personagens[i]);
    }
    jogador->fichas = 3;
    return selecao;
}
void telaRecordes()
{
    Recorde recordes[MAX_RECORDES];
    int numRecordes = 0, menu = 1;
    FILE *arquivo = fopen("bin/score.bin", "rb");
    if (arquivo != NULL)
    {
        while (fread(&recordes[numRecordes], sizeof(Recorde), 1, arquivo) == 1 && numRecordes < MAX_RECORDES)
        {
            numRecordes++;
        }
        fclose(arquivo);
    }
    else
    {
        perror("Erro ao abrir arquivo score.bin");
        return;
    }

    while (menu)
    {

        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
        SDL_RenderClear(renderizador);
        escreveTexto("Recordes", TELA_LARGURA / 2 - 50, 10, BRANCO);

        for (int i = 0; i < numRecordes; i++)
        {
            char textoRecorde[100];
            snprintf(textoRecorde, sizeof(textoRecorde), "%d. %s\t%d", i + 1, recordes[i].nome, recordes[i].pontos);
            escreveTexto(textoRecorde, TELA_LARGURA / 2 - 60, 50 + i * ALTURA_LINHA, BRANCO);
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
                Mix_PlayChannel(-1, seleciona_sfx, 0);
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

void telaFinal(Jogador *jogador)
{
    jogador->fichas--;
    char nome[4] = {0};
    int i = 0, final = 1;
    bool continuar = false;

    fadeOut();

    while (final)
    {
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);

        // o jogador termina o jogo ou não decide continuar
        if ((jogador->fichas == 0 && !continuar) || verificaFimDeJogo(jogador))
        {
            escreveTexto("Obrigado por jogar!", 200, 100, BRANCO);
            escreveTexto("Escreva seu nome:", 100, TELA_ALTURA - 50, BRANCO);
            escreveTexto(nome, TELA_LARGURA / 2, TELA_ALTURA - 50, BRANCO);
            exibePontos(jogador->pontos);
            fflush(stdin);

            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    destroi(janela);
                    exit(0);
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        destroi(janela);
                        exit(0);
                    }
                    else if (e.key.keysym.sym == SDLK_BACKSPACE && i > 0)
                    {
                        Mix_PlayChannel(-1, seleciona_sfx, 0);
                        i--;
                        nome[i] = '\0';
                    }
                    else if (e.key.keysym.sym == SDLK_RETURN && i > 0)
                    {
                        Mix_PlayChannel(-1, seleciona_sfx, 0);
                        final = 0;
                    }
                    else if (i < 3 && e.key.keysym.sym >= SDLK_a && e.key.keysym.sym <= SDLK_z)
                    {
                        Mix_PlayChannel(-1, seleciona_sfx, 0);
                        nome[i] = toupper(e.key.keysym.sym);
                        i++;
                    }
                }
            }

            if (i == 3 && final == 0)
            {
                if (jogador->recorde < jogador->pontos)
                {
                    jogador->recorde = jogador->pontos;
                }
                gravarRecordes(nome, jogador->recorde);
                escreveTexto(nome, TELA_LARGURA / 2, TELA_ALTURA - 50, BRANCO);
                SDL_RenderPresent(renderizador);
                SDL_Delay(1000);
                final = 0;
            }
            SDL_RenderPresent(renderizador);
        }
        // se o jogador nao tem ficha e nao termina o jogo
        else if (jogador->fichas == 0 && !verificaFimDeJogo(jogador))
        {
            // Contagem regressiva
            for (int contador_final = 10; contador_final >= 0; contador_final--)
            {
                SDL_RenderClear(renderizador);
                if (continuar)
                    break;

                char texto[10];
                sprintf(texto, "%d", contador_final);
                escreveTexto(texto, TELA_LARGURA / 2 - 10, TELA_ALTURA / 2 - 20, BRANCO);
                Mix_PlayChannel(-1, seleciona_sfx, 0);
                escreveTexto("RSHIFT para adicionar mais fichas", TELA_LARGURA / 2 - 200, TELA_ALTURA - 50, BRANCO);
                SDL_RenderPresent(renderizador);
                SDL_Delay(1000);
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
                        if (e.key.keysym.sym == SDLK_ESCAPE)
                        {
                            destroi(janela);
                            exit(0);
                        }
                        else if (e.key.keysym.sym == SDLK_RSHIFT)
                        {
                            jogador->fichas += 3;
                            continuar = true;
                            final = 0;
                            SDL_Delay(500);
                        }
                    }
                }
            }
        }
        // se o jogador tem ficha
        else if (jogador->fichas > 0 && !verificaFimDeJogo(jogador))
        {
            char texto[10];
            sprintf(texto, "x%d", jogador->fichas);
            escreveTexto(texto, TELA_ALTURA / 2 + 160, TELA_ALTURA / 2, BRANCO);
            SDL_Rect imagemRect = {TELA_ALTURA / 2, TELA_ALTURA / 2 - 160 / 2, 160, 160};
            SDL_RenderCopy(renderizador, idle[0], NULL, &imagemRect);

            jogador->resgatando = 0;
            SDL_RenderPresent(renderizador);
            SDL_Delay(2000);
            final = 0;

            if (jogador->recorde < jogador->pontos)
            {
                jogador->recorde = jogador->pontos;
            }
        }
    }
}
void telaApresentacao()
{
    SDL_Texture *logo_rural = IMG_LoadTexture(renderizador, "assets/img/rural_logo.png");
    SDL_SetTextureAlphaMod(logo_rural, 0);
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
            SDL_SetTextureAlphaMod(logo_rural, i * 2);
        }

        SDL_SetRenderDrawColor(renderizador, i, i, i, 255);
        SDL_RenderCopy(renderizador, logo_rural, NULL, &r);
        SDL_Delay(10);
        SDL_RenderPresent(renderizador);
    }

    SDL_Delay(1000);
    SDL_DestroyTexture(logo_rural);
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
                Mix_PlayChannel(-1, seleciona_sfx, 0);
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
void telaInicial(Jogador *jogador) // OK
{
    int inicial = 1, selecao = 0;

    while (inicial)
    {
        SDL_SetRenderDrawColor(renderizador, 0, 0, 200, 255);
        SDL_RenderClear(renderizador);
        escreveTexto("Iniciar", 200, 200, BRANCO);
        escreveTexto("Instrucoes", 200, 250, BRANCO);
        escreveTexto("Recordes", 200, 300, BRANCO);
        escreveTexto("Por Andre, Fellipe e Guilherme.", 10, TELA_ALTURA - 35, BRANCO);
        exibeFichas(jogador->fichas);

        switch (selecao)
        {
        case 0:
            escreveTexto("Iniciar", 200, 200, AMARELO);
            break;
        case 1:
            escreveTexto("Instrucoes", 200, 250, AMARELO);
            break;
        case 2:
            escreveTexto("Recordes", 200, 300, AMARELO);
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
                    {
                        Mix_PlayChannel(-1, seleciona_sfx, 0);
                        selecao--;
                    }
                    break;
                case SDLK_DOWN:
                    if (selecao < 2)
                    {
                        Mix_PlayChannel(-1, seleciona_sfx, 0);
                        selecao++;
                    }
                    break;
                case SDLK_RETURN:
                    Mix_PlayChannel(-1, seleciona_sfx, 0);
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