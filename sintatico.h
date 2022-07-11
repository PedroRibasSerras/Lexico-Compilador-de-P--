#ifndef SINTATICO_H // guardas de cabeçalho, impedem inclusões cíclicas
#define SINTATICO_H
#include <stdio.h>

typedef struct
{
    char **v;
    int n;
    int p;
} Conjunto;

Conjunto juntaConjuntos(Conjunto, Conjunto);
Conjunto criaConjunto(int);
void addStr(Conjunto, char *);
void printErro(char *);
int erro(char *, Conjunto);
void programa(Conjunto);
void corpo(Conjunto);
void dc(Conjunto);
int dc_c();
int dc_v();
void tipo_var();
void vaiaveis();
void mais_var();
void dc_p();
void parametros();
void lista_par();
void mais_par();
void corpo_p();
void dc_loc();
void lista_arg();
void argumentos();
void mais_ident();
void pfalsa();
void comandos(Conjunto S);
void cmd();
void condicao();
void relacao();
void expressao();
void op_un();
void outros_termos();
void op_ad();
void termo();
void mais_fatores();
void op_mul();
void fator();
void numero();

#endif