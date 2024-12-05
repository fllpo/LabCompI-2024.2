#ifndef CENARIO_H
#define CENARIO_H
#include "utils.h"
typedef struct
{
    SDL_Texture *texture;
    SDL_Rect tiles[25][23];
} Tileset;

typedef struct
{
    int x, y, w, h;
} Plataforma;

static Tileset tileset;
void desenhaCenario();
#endif