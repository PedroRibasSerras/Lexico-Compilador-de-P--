#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexico.h"
#include "sintatico.h"

int main()
{
    // Open the "meu_programa" file
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

    contadorLinha = (int *)malloc(1 * sizeof(int));
    *contadorLinha = 1;
    TT = criaTabelaTransicao();
    TE = criaTabelaDeEstados();
    TSR = criaTabelaSimbolosReservados();

    char inicioErroMsg[100];

    // carry the pointer to the file beginer
    fseek(arquivo, 0, SEEK_SET);
    if (getc(arquivo) == EOF)
    {
        printf("Arquivo vazio! Compilado com sucesso.");
    }
    else
    {
        initPrimeirosESeguidores();

        fseek(arquivo, -1, SEEK_CUR);

        token = (RetornoLexical *)malloc(1 * sizeof(RetornoLexical));

        *token = analiseLexical();

        programa(criaConjunto(0));

        if (getc(arquivo) != EOF)
        {
            sprintf(inicioErroMsg, "Erro sintatico na linha %d: ", *contadorLinha);
            fputs(inicioErroMsg, saida);
            // fputs(token.token, saida);
            // fputs(", ", saida);
            fputs("programa não finalizado corretamente", saida);
            fputc('\n', saida);
        }
        else
        {
            fputs("Programa compilado com sucesso!", saida);
        }
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