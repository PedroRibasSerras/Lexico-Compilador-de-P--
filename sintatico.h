#ifndef SINTATICO_H // guardas de cabeçalho, impedem inclusões cíclicas
#define SINTATICO_H
#include <stdio.h>

void erro(char *);
void programa();
void corpo();
void dc();
void dc_c();
void dc_v();
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
void comandos();
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