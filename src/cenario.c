#include "../include/utils.h"
#include "../include/cenario.h"
#include "../include/estruturas.h"

extern Jogador jogador;
// mantenha y como multiplo de 200
Plataforma plataformas[] = {
    {-50, TELA_ALTURA - 50, 1000, 50},  // chão
    {1200, TELA_ALTURA - 50, 500, 50},  // chão
    {1900, TELA_ALTURA - 50, 5000, 50}, // chão
    {2500, TELA_ALTURA - 200, 400, 50}, // plataforma aerea
    {450, TELA_ALTURA - 200, 150, 50},  // plataforma aerea
    {750, TELA_ALTURA - 400, 250, 50}   // plataforma aerea
};

int qtd_plataformas = sizeof(plataformas) / sizeof(Plataforma);

void inicializaTileset()
{
    tileset.texture = IMG_LoadTexture(renderizador, "assets/img/Environments/SunnyLand/Layers/tileset.png");

    for (int x = 0; x < 25; x++)
    {
        for (int y = 0; y < 23; y++)
        {
            tileset.tiles[x][y] = (SDL_Rect){x * 16, y * 16, 16, 16};
        }
    }
}

void criaPlataformas()
{
    for (int i = 0; i < qtd_plataformas; i++)
    {
        for (int j = 0; j < plataformas[i].w / 50; j++)
        {
            SDL_Rect plataformasRect = {plataformas[i].x + (50 * j) + jogador.scrollX, plataformas[i].y, 50, 50};
            SDL_Rect *tilesPlataforma;
            if (j == plataformas[i].w / 50 - 1)
            {
                tilesPlataforma = &tileset.tiles[19][14];
            }
            else if (j == 0)
            {
                tilesPlataforma = &tileset.tiles[15][14];
            }
            else
            {
                tilesPlataforma = &tileset.tiles[17][14];
            }
            SDL_RenderCopy(renderizador, tileset.texture, tilesPlataforma, &plataformasRect);
        }
    }
}

void desenhaCenario()
{
    inicializaTileset();
    SDL_Texture *fundo = IMG_LoadTexture(renderizador, "assets/img/Environments/SunnyLand/Layers/back.png");
    SDL_RenderCopy(renderizador, fundo, NULL, NULL);

    criaPlataformas();

    SDL_DestroyTexture(fundo);
    SDL_DestroyTexture(tileset.texture);
}
