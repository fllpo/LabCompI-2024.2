#include "../include/utils_recordes.h"
void gravarRecordes(char *nomeJogador, int maiorPonto)
{
    Recorde recordes[MAX_REGISTROS];
    int numRecordes = carregarRecordes(recordes);

    if (numRecordes < MAX_REGISTROS)
    {
        adicionarNovoRecorde(recordes, &numRecordes, nomeJogador, maiorPonto);
    }

    ordenarRecordes(recordes, numRecordes);
    salvarRecordes(recordes, numRecordes);
}

int carregarRecordes(Recorde *recordes)
{
    int numRecordes = 0;
    FILE *arquivo = fopen("bin/score.bin", "rb");
    if (arquivo != NULL)
    {
        while (fread(&recordes[numRecordes], sizeof(Recorde), 1, arquivo) == 1 && numRecordes < MAX_REGISTROS)
        {
            numRecordes++;
        }
        fclose(arquivo);
    }
    return numRecordes;
}

void adicionarNovoRecorde(Recorde *recordes, int *numRecordes, char *nomeJogador, int maiorPonto)
{
    strncpy(recordes[*numRecordes].nome, nomeJogador, sizeof(recordes[*numRecordes].nome) - 1);
    recordes[*numRecordes].nome[sizeof(recordes[*numRecordes].nome) - 1] = '\0';
    recordes[*numRecordes].pontos = maiorPonto;
    (*numRecordes)++;
}

void ordenarRecordes(Recorde *recordes, int numRecordes)
{
    for (int i = 0; i < numRecordes - 1; i++)
    {
        for (int j = 0; j < numRecordes - i - 1; j++)
        {
            if (recordes[j].pontos < recordes[j + 1].pontos)
            {
                Recorde temp = recordes[j];
                recordes[j] = recordes[j + 1];
                recordes[j + 1] = temp;
            }
        }
    }
}

void salvarRecordes(Recorde *recordes, int numRecordes)
{
    FILE *arquivo = fopen("bin/score.bin", "wb");
    if (arquivo != NULL)
    {
        for (int i = 0; i < numRecordes; i++)
        {
            fwrite(&recordes[i], sizeof(Recorde), 1, arquivo);
        }
        fclose(arquivo);
    }
    else
    {
        perror("Erro ao abrir arquivo score.bin para escrita");
    }
}
