#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lexico.h"
#include "sintatico.h"

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
    int *contadorLinha = 1;

    // carry the pointer to the file beginer
    fseek(arquivo, 0, SEEK_SET);
    RetornoLexical token;
    if(getc(arquivo) == EOF){
        printf("Arquivo vazio! Compilado com sucesso.");
        
    }
    else{
        fseek(arquivo, -1, SEEK_CUR);

        token = analiseLexical(arquivo, TT, TE, TSR, saida, contadorLinha);
        programa(saida, contadorLinha, token);
        
        if(getc(arquivo) != EOF){
            sprintf(inicioErroMsg, "Erro sintatico na linha %d: ", contadorLinha);
            fputc(inicioErroMsg, saida);
            // fputs(token.token, saida);
            // fputs(", ", saida);
            fputs(token.classe, saida);
            fputc('\n', saida);
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