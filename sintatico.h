#ifndef SINTATICO_H // guardas de cabeçalho, impedem inclusões cíclicas
#define SINTATICO_H
#include <stdio.h>
#include "sp.h"

void printErro(char *);
int erro(char *, Conjunto *, Conjunto *);
void programa(Conjunto *);
void corpo(Conjunto *);
void dc(Conjunto *);
void dc_c(Conjunto *);
void dc_v(Conjunto *);
void tipo_var(Conjunto *);
void variaveis(Conjunto *);
void mais_var(Conjunto *);
void dc_p(Conjunto *);
void parametros(Conjunto *);
void lista_par(Conjunto *);
void mais_par(Conjunto *);
void corpo_p(Conjunto *);
void dc_loc(Conjunto *);
void lista_arg(Conjunto *);
void argumentos(Conjunto *);
void mais_ident(Conjunto *);
void pfalsa(Conjunto *);
void comandos(Conjunto *);
void cmd(Conjunto *);
void condicao(Conjunto *);
void relacao(Conjunto *);
void expressao(Conjunto *);
void op_un(Conjunto *);
void outros_termos(Conjunto *);
void op_ad(Conjunto *);
void termo(Conjunto *);
void mais_fatores(Conjunto *);
void op_mul(Conjunto *);
void fator(Conjunto *);
void numero(Conjunto *);

#endif