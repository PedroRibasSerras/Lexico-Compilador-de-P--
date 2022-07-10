#ifndef SINTATICO_H // guardas de cabeçalho, impedem inclusões cíclicas
#define SINTATICO_H
#include <stdio.h>
#include "lexico.h"

void programa(FILE *, int*, RetornoLexical);
void corpo(FILE *, int*, RetornoLexical);
void dc(FILE *, int*, RetornoLexical);
void dc_c(FILE *, int*, RetornoLexical);
void dc_v(FILE *, int*, RetornoLexical);
void tipo_var(FILE *, int*, RetornoLexical);
void vaiaveis(FILE *, int*, RetornoLexical);
void mais_var(FILE *, int*, RetornoLexical);
void dc_p(FILE *, int*, RetornoLexical);
void parametros(FILE *, int*, RetornoLexical);
void lista_par(FILE *, int*, RetornoLexical);
void mais_par(FILE *, int*, RetornoLexical);
void corpo_p(FILE *, int*, RetornoLexical);
void dc_loc(FILE *, int*, RetornoLexical);
void lista_arg(FILE *, int*, RetornoLexical);
void argumentos(FILE *, int*, RetornoLexical);
void mais_ident(FILE *, int*, RetornoLexical);
void pfalsa(FILE *, int*, RetornoLexical);
void comandos(FILE *, int*, RetornoLexical);
void cmd(FILE *, int*, RetornoLexical);
void condicao(FILE *, int*, RetornoLexical);
void relacao(FILE *, int*, RetornoLexical);
void expressao(FILE *, int*, RetornoLexical);
void op_un(FILE *, int*, RetornoLexical);
void outros_termos(FILE *, int*, RetornoLexical);
void op_ad(FILE *, int*, RetornoLexical);
void termo(FILE *, int*, RetornoLexical);
void mais_fatores(FILE *, int*, RetornoLexical);
void op_mul(FILE *, int*, RetornoLexical);
void fator(FILE *, int*, RetornoLexical);
void numero(FILE *, int*, RetornoLexical);



#endif