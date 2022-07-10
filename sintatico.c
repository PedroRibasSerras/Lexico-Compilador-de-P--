#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"

void erro(FILE * saida, int* contadorLinha, char* erroMsg){

}
void programa(FILE * saida, int* contadorLinha, RetornoLexical* token){

    if(strcmp(token->classe, "program") == 0){
        *token = analiseLexical(arquivo, TT, TE, TSR, saida, contadorLinha);
    }
    else{
        erro(FILE * saida, int* contadorLinha, "O programa deve ser iniciado com 'program'.");
        return;
    }

    if(strcmp(token->classe, "identificador") == 0){
        *token = analiseLexical(arquivo, TT, TE, TSR, saida, contadorLinha);
    }
    else{
        erro(FILE * saida, int* contadorLinha, "programa sem identificador.");
        return;
    }

    if(strcmp(token->classe, "simb_ponto_virgula") == 0){
        *token = analiseLexical(arquivo, TT, TE, TSR, saida, contadorLinha);
    }
    else{
        erro(FILE * saida, int* contadorLinha, "programa sem identificador.");
        return;
    }

    corpo(saida, contadorLinha, token);

}
void corpo(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void dc(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void dc_c(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void dc_v(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void tipo_var(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void vaiaveis(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void mais_var(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void dc_p(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void parametros(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void lista_par(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void mais_par(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void corpo_p(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void dc_loc(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void lista_arg(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void argumentos(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void mais_ident(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void pfalsa(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void comandos(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void cmd(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void condicao(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void relacao(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void expressao(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void op_un(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void outros_termos(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void op_ad(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void termo(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void mais_fatores(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void op_mul(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void fator(FILE * saida, int* contadorLinha, RetornoLexical* token){}
void numero(FILE * saida, int* contadorLinha, RetornoLexical* token){}

