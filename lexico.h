#ifndef LEXICO_H // guardas de cabeçalho, impedem inclusões cíclicas
#define LEXICO_H

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
RetornoLexical analiseLexical();

FILE *arquivo, *saida;

int **TT;
Estado *TE;
char **TSR;
int *contadorLinha;
RetornoLexical *token;

#endif