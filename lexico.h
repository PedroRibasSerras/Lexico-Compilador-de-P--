#ifndef LEXICO_H // guardas de cabeçalho, impedem inclusões cíclicas
#define LEXICO_H
#include <stdio.h>

typedef struct
{
    int final;
    int retrocede;
    char *mensagem;
    int erro;
} Estado;

typedef struct
{
    char *token;
    char *classe;
} RetornoLexical;

int **criaTabelaTransicao();
Estado *criaTabelaDeEstados();
char **criaTabelaSimbolosReservados();
RetornoLexical analiseLexical(FILE *, int **, Estado *, char **,FILE *,int *);

#endif