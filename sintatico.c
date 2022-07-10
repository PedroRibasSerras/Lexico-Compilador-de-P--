#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"

void erro(char *erroMsg)
{
}
void programa()
{
    if (strcmp(token->classe, "program") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        erro("O programa deve ser iniciado com 'program'.");
        return;
    }

    if (strcmp(token->classe, "identificador") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        erro("programa sem identificador.");
        return;
    }

    if (strcmp(token->classe, "simb_ponto_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        erro("programa sem identificador.");
        return;
    }

    corpo();
}
void corpo()
{
}
void dc() {}
void dc_c() {}
void dc_v() {}
void tipo_var() {}
void vaiaveis() {}
void mais_var() {}
void dc_p() {}
void parametros() {}
void lista_par() {}
void mais_par() {}
void corpo_p() {}
void dc_loc() {}
void lista_arg() {}
void argumentos() {}
void mais_ident() {}
void pfalsa() {}
void comandos() {}
void cmd() {}
void condicao() {}
void relacao() {}
void expressao() {}
void op_un() {}
void outros_termos() {}
void op_ad() {}
void termo() {}
void mais_fatores() {}
void op_mul() {}
void fator() {}
void numero() {}
