#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/inimigo.h"
#include "../include/cenario.h"

void criaPlataforma(int x, int y)
{
    SDL_Texture *tilesetTexture = IMG_LoadTexture(renderizador, "assets/img/Environments/SunnyLand/Layers/tileset.png");

    SDL_Rect tile[25][23];
    for (int x = 0; x < 25; x++)
    {
        for (int y = 0; y < 23; y++)
        {
            tile[x][y].x = x * 16;
            tile[x][y].y = y * 16;
            tile[x][y].w = 16;
            tile[x][y].h = 16;
        }
    }

    SDL_Rect rectPlataformaEsquerda = {x + jogador.scrollX, y, 50, 50};
    SDL_Rect rectPlataformaMeio = {x + 50 + jogador.scrollX, y, 50, 50};
    SDL_Rect rectPlataformaDireita = {x + 100 + jogador.scrollX, y, 50, 50};

    SDL_RenderCopy(renderizador, tilesetTexture, &tile[15][14], &rectPlataformaEsquerda);
    SDL_RenderCopy(renderizador, tilesetTexture, &tile[17][14], &rectPlataformaMeio);
    SDL_RenderCopy(renderizador, tilesetTexture, &tile[19][14], &rectPlataformaDireita);

    SDL_DestroyTexture(tilesetTexture);
}
void desenhaCenario()
{
    SDL_Texture *tilesetTexture = IMG_LoadTexture(renderizador, "assets/img/Environments/SunnyLand/Layers/tileset.png");
    SDL_Rect tile[25][23];
    for (int x = 0; x < 25; x++)
    {
        for (int y = 0; y < 23; y++)
        {
            tile[x][y].x = x * 16;
            tile[x][y].y = y * 16;
            tile[x][y].w = 16;
            tile[x][y].h = 16;
        }
    }

    SDL_Texture *fundo = IMG_LoadTexture(renderizador, "assets/img/Environments/SunnyLand/Layers/back.png");
    SDL_RenderCopy(renderizador, fundo, NULL, NULL);

    for (int i = 0; i < 500; i++)
    {
        SDL_Rect rectChao = {50 * i + jogador.scrollX, TELA_ALTURA - 50, 50, 50};
        SDL_RenderCopy(renderizador, tilesetTexture, &tile[3][1], &rectChao);
    }

    criaPlataforma(450, TELA_ALTURA - 200);
}
