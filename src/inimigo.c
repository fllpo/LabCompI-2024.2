#include "../include/utils.h"
#include "../include/jogador.h"
#include "../include/inimigo.h"

Inimigo *inimigos = NULL;
int num_inimigos = 0;

bool criaInimigos(int quantidade)
{
    if (inimigos != NULL)
    {
        free(inimigos);
    }

    inimigos = (Inimigo *)calloc(quantidade, sizeof(Inimigo));
    if (inimigos == NULL)
    {
        return false;
    }

    num_inimigos = quantidade;

    for (int i = 0; i < num_inimigos; i++)
    {
        iniciaInimigo(&inimigos[i], i);
    }

    return true;
}

bool iniciaInimigo(Inimigo *inimigo, int index)
{
    inimigo->vida = 1;
    inimigo->h = 100;
    inimigo->w = 100;
    inimigo->x = TELA_LARGURA - (200 * (index + 1));
    inimigo->y = TELA_ALTURA - inimigo->h - 50;
    inimigo->viradoParaEsquerda = 0;
    inimigo->pulando = true;
    inimigo->velocidadeY = 0;
    inimigo->velocidade_movimento = 200;
    inimigo->nochao = true;

    char caminho[256];
    inimigo_textura = (SDL_Texture **)calloc(4, sizeof(SDL_Texture *));
    for (int i = 0; i < 4; i++)
    {
        snprintf(caminho, sizeof(caminho), "assets/img/Characters/Enemies and NPC/Dog/Sprites/Dog/dog%d.png", i + 1);

        inimigo_textura[i] = IMG_LoadTexture(renderizador, caminho);
        if (inimigo_textura[i] == NULL)
        {
            printf("Erro ao carregar textura %d para dog: %s\n", i + 1, IMG_GetError());
            return false;
        }
    }

    return true;
}

void atualizaTodosInimigos(Jogador *jogador)
{
    for (int i = 0; i < num_inimigos; i++)
    {
        atualizaInimigo(&inimigos[i], jogador);
    }
}

void desenhaTodosInimigos()
{
    for (int i = 0; i < num_inimigos; i++)
    {
        desenhaInimigo(&inimigos[i]);
    }
}

void verificaTodasColisoesInimigo(Jogador *jogador)
{
    for (int i = 0; i < num_inimigos; i++)
    {
        colisaoJogadorInimigo(jogador, &inimigos[i]);
    }
}

void liberaInimigos()
{
    if (inimigos != NULL)
    {
        free(inimigos);
        inimigos = NULL;
        num_inimigos = 0;
    }
}

void movimentoHorizontalInimigo(Inimigo *inimigo, Jogador *jogador)
{
    int direcao = inimigo->viradoParaEsquerda ? -1 : 1;
    float distancia = abs(inimigo->x - jogador->x);

    if (distancia > 400)
    {
        if (inimigo->x < jogador->x)
        {
            direcao = 1;
            inimigo->viradoParaEsquerda = 0;
        }
        else if (inimigo->x > jogador->x)
        {
            direcao = -1;
            inimigo->viradoParaEsquerda = 1;
        }
    }

    inimigo->x += inimigo->velocidade_movimento * deltaTime * direcao;
}
bool verificarColisaoChaoInimigo(Inimigo *inimigo)
{
    if (inimigo->y >= TELA_ALTURA - inimigo->h - 50)
    {
        inimigo->y = TELA_ALTURA - inimigo->h - 50;
        inimigo->nochao = true;
        inimigo->velocidadeY = 0;
        return true;
    }
    return false;
}
void movimentoVerticalInimigo(Inimigo *inimigo)
{
    if (!inimigo->nochao)
    {
        inimigo->y += inimigo->velocidadeY;
        inimigo->velocidadeY += GRAVIDADE;
        if (inimigo->vida > 0)
        {
            verificarColisaoChaoInimigo(inimigo);
        }
    }
}
void atualizaInimigo(Inimigo *inimigo, Jogador *jogador)
{
    movimentoHorizontalInimigo(inimigo, jogador);
    movimentoVerticalInimigo(inimigo);
}

void desenhaInimigo(Inimigo *inimigo)
{
    SDL_Rect rectInimigo = {inimigo->x + jogador.scrollX, inimigo->y, inimigo->w, inimigo->h};
    SDL_Texture *texturaAtual;

    if (inimigo->velocidade_movimento != 0)
    {
        texturaAtual = inimigo_textura[SDL_GetTicks() / 150 % 4];
    }

    !inimigo->viradoParaEsquerda ? SDL_RenderCopyEx(renderizador, texturaAtual, NULL, &rectInimigo, 0, NULL, SDL_FLIP_HORIZONTAL) : SDL_RenderCopy(renderizador, texturaAtual, NULL, &rectInimigo);
}

// Função chamada quando o temporizador expira para desativar a imunidade
Uint32 tornaJogadorMortal(Uint32 interval, void *param)
{
    Jogador *jogador = (Jogador *)param;
    jogador->imune = false; // Desativa imunidade
    return 0;               // Para que o temporizador seja chamado apenas uma vez
}

void colisaoJogadorInimigo(Jogador *jogador, Inimigo *inimigo)
{
    // Verifica colisão geral entre jogador e inimigo com tolerância para laterais
    if (jogador->x + jogador->w >= inimigo->x - 10 && jogador->x <= inimigo->x + inimigo->w + 10 &&
        jogador->y + jogador->h >= inimigo->y && jogador->y <= inimigo->y + inimigo->h)
    {
        // Verifica se o jogador está acima do inimigo e em movimento descendente
        if (jogador->y + jogador->h <= inimigo->y + inimigo->h / 2 && jogador->velocidadeY > 0)
        {
            // Jogador pula no inimigo
            inimigo->vida--;
            inimigo->nochao = false;
            jogador->pontos += 100;

            jogador->velocidadeY = -15;
        }
        else
        {
            // Jogador colidiu com o inimigo, mas não por cima
            if (!jogador->resgatando)
            {
                // jogador->vida--;
            }
            else
            {
                jogador->resgatando = false;
                jogador->imune = true;
                SDL_AddTimer(2000, tornaJogadorMortal, jogador); // Configura imunidade por 2 segundos
            }
        }
    }
}
