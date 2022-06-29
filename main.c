#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexico.h"

int main()
{
    // Open the "meu_programa" file
    FILE *arquivo, *saida;
    arquivo = fopen("meu_programa.txt", "rt");
    saida = fopen("saida.txt", "w");

    // test if the file opened
    if (arquivo == NULL)
    {
        printf("The file could not be open!!");
        return 0;
    }
    if (saida == NULL)
    {
        printf("The file could not be open!!");
        return 0;
    }

    int **TT = criaTabelaTransicao();
    Estado *TE = criaTabelaDeEstados();
    char **TSR = criaTabelaSimbolosReservados();

    // carry the pointer to the file beginer
    fseek(arquivo, 0, SEEK_SET);
    RetornoLexical token;
    while (getc(arquivo) != EOF)
    {
        fseek(arquivo, -1, SEEK_CUR);

        token = analiseLexical(arquivo, TT, TE, TSR);

        fputs(token.token, saida);
        fputs(", ", saida);
        fputs(token.classe, saida);
        fputc('\n', saida);
    }
    fclose(saida);
    fclose(arquivo);

    for (int i = 0; i < 0; i++)
    {
        free(TT[i]);
        free(TSR[i]);
    }
    free(TT);
    free(TSR);
    free(TE);

    return 0;
}