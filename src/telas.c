#include "../include/utils.h"
#include "../include/jogador.h"

void telaJogo()
{

    processaEventosJogo(&jogador, &e);
    renderiza();
}

int telaSelecaoPersonagem()
{
    int menu = 1, selecao = 0;
    SDL_Texture *personagens[4];
    SDL_Rect molduraExterna = {145, 145, 310, 310};
    SDL_Rect molduraInterna = {150, 150, 300, 300};
    SDL_Rect imagemRect = {160, 160, 280, 280};

    // Carregando as imagens dos personagens
    personagens[0] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Foxy/Sprites/idle/player-idle-1.png");
    personagens[1] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Squirrel/Sprites/idle/player-idle-1.png");
    personagens[2] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/sunny-bunny/Sprites/idle/player-idle-1.png");
    personagens[3] = IMG_LoadTexture(renderizador, "assets/img/Characters/Players/Fiery Imp/Sprites/idle/player-idle-1.png");

    while (menu)
    {
        SDL_SetRenderDrawColor(renderizador, 150, 150, 150, 255);
        SDL_RenderClear(renderizador);

        // Desenhar a moldura externa (marrom)
        SDL_SetRenderDrawColor(renderizador, 139, 69, 19, 255); // Cor marrom
        SDL_RenderFillRect(renderizador, &molduraExterna);

        // Desenhar a moldura interna (fundo da imagem)
        SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255);
        SDL_RenderFillRect(renderizador, &molduraInterna);

        // Desenhar a imagem do personagem selecionado
        SDL_RenderCopy(renderizador, personagens[selecao], NULL, &imagemRect);

        escreveTexto("Raposa", 500, 200, PRETO);
        escreveTexto("Esquilo", 500, 250, PRETO);
        escreveTexto("Coelho", 500, 300, PRETO);
        escreveTexto("Charmander", 500, 350, PRETO);

        exibeFichas(jogador->fichas);

        switch (selecao)
        {
        case 0:
            escreveTexto("Raposa", 500, 200, BRANCO);
            break;
        case 1:
            escreveTexto("Esquilo", 500, 250, BRANCO);
            break;
        case 2:
            escreveTexto("Coelho", 500, 300, BRANCO);
            break;
        case 3:
            escreveTexto("Charmander", 500, 350, BRANCO);
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
                    if (selecao < 3)
                        selecao++;
                    break;
                case SDLK_RETURN:
                    menu = 0;
                    break;
                }
            }
        }
        SDL_RenderPresent(renderizador);
    }

    // Liberar as texturas dos personagens
    for (int i = 0; i < 4; i++) {
        SDL_DestroyTexture(personagens[i]);
    }

    return selecao;
}
void telaRecordes() // OK
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
            snprintf(textoRecorde, sizeof(textoRecorde), "%d. %s - %d", i + 1, recordes[i].nome, recordes[i].pontos);
            escreveTexto(textoRecorde, 10, 50 + i * ALTURA_LINHA, BRANCO);
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
                }
            }
        }
    }
}
void telaFinal(Player *jogador) // TODO
{
    jogador->fichas--;
    int final = 1;
    while (final)
    {
        SDL_RenderClear(renderizador);
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255);
        if (jogador->fichas == 0)
        {
            escreveTexto("Obrigado por jogar!", 200, 200, BRANCO);
            escreveTexto("Pressione F para adicionar mais fichas!", 200, 250, BRANCO);
            exibeFichas(jogador->fichas);
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
                    case SDLK_f:
                        jogador->fichas += 3;
                        exibeFichas(jogador->fichas);
                        SDL_Delay(500);
                        break;
                    case SDLK_RETURN:
                        final = 0;
                        break;
                    }
                }
            }
        }

        else
        {
            escreveTexto("Pressione Enter para jogar novamente", 200, 200, BRANCO);
            exibeFichas(jogador->fichas);
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
        }
        SDL_RenderPresent(renderizador);
    }
    if (jogador->recorde < jogador->pontos)
    {
        jogador->recorde = jogador->pontos;
        gravarRecordes("FEL", jogador->recorde);
    }
}
void telaApresentacao() // OK
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
void telaInicial(Player *jogador) // OK
{

    int inicial = 1, selecao = 0;
    jogador->fichas = 3;

    while (inicial)
    {
        SDL_SetRenderDrawColor(renderizador, 0, 0, 200, 255);
        SDL_RenderClear(renderizador);
        escreveTexto("Iniciar", 200, 200, PRETO);
        escreveTexto("Instrucoes", 200, 250, PRETO);
        escreveTexto("Recordes", 200, 300, PRETO);
        escreveTexto("Por Andre, Fellipe e Guilherme.", 10, TELA_ALTURA - 35, BRANCO);
        exibeFichas(jogador->fichas);

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