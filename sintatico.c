#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"

Conjunto juntaConjuntos(Conjunto c1, Conjunto c2)
{
    Conjunto novoConjunto;
    novoConjunto.v = (char **)malloc((c1.n + c2.n) * sizeof(char *));
    for (int i = 0; i <= c1.p; i++)
    {
        novoConjunto.v[i] = (char *)malloc(sizeof(c1.v[i]));
        strcpy(novoConjunto.v[i], c1.v[i]);
    }
    for (int i = 0; i <= c2.p; i++)
    {
        novoConjunto.v[c1.p + 1 + i] = (char *)malloc(sizeof(c2.v[i]));
        strcpy(novoConjunto.v[c1.p + 1 + i], c2.v[i]);
    }
    novoConjunto.n = c1.n + c2.n;
    novoConjunto.p = c1.p + c2.p + 1;

    return novoConjunto;
}

Conjunto criaConjunto(int n)
{
    Conjunto c;
    c.v = (char **)malloc((n) * sizeof(char *));
    c.n = n;
    c.p = -1;

    return c;
}

void addStr(Conjunto c, char *str)
{
    c.v[++c.p] = str;
}

void printErro(char *erroMsg)
{
    char inicioErroMsg[50];
    sprintf(inicioErroMsg, "Erro sintatico na linha %d: ", *contadorLinha);
    fputs(inicioErroMsg, saida);
    // fputs(token.token, saida);
    // fputs(", ", saida);
    fputs(erroMsg, saida);
    fputc('\n', saida);
}

int erro(char *erroMsg, Conjunto c)
{
    if (erroMsg[0] != '\0')
    {
        printErro(erroMsg);
    }

    for (int i = 0; i <= c.p; i++)
    {
        if (strcmp(token->classe, c.v[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void programa(Conjunto S)
{
    if (strcmp(token->classe, "program") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto proximo = criaConjunto(2);
        addStr(proximo, "identficador");
        addStr(proximo, "identificador mal formado");

        if (!erro("Token \"program\" esperado.", proximo))
            if (erro("", S))
            {
                return;
            }
    }

    if (strcmp(token->classe, "identificador") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto proximo = criaConjunto(1);
        addStr(proximo, ";");

        if (!erro("Identificador de programa esperado.", proximo))
            if (erro("", S))
            {
                return;
            }
    }

    if (strcmp(token->classe, "simb_ponto_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto proximo = criaConjunto(3);
        addStr(proximo, "const");
        addStr(proximo, "var");
        addStr(proximo, "procedure");

        if (!erro("Identificador de programa esperado.", proximo))
            if (erro("", S))
            {
                return;
            }
    }

    Conjunto seguidorCorpo = criaConjunto(1);
    addStr(seguidorCorpo, ".");

    corpo(juntaConjuntos(seguidorCorpo, S));

    if (strcmp(token->classe, "simb_ponto") == 0)
    {
        return;
    }
    else
    {
        printErro("Ponto (.) esperado no final do codigo.");
        return;
    }
}
void corpo(Conjunto S)
{

    Conjunto seguidorDc = criaConjunto(1);
    addStr(seguidorDc, "begin");

    dc(juntaConjuntos(seguidorDc, S));

    if (strcmp(token->classe, "begin") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto proximo = criaConjunto(7);
        addStr(proximo, "read");
        addStr(proximo, "write");
        addStr(proximo, "if");
        addStr(proximo, "identificador"); // duas regras - deve ser tratado
        addStr(proximo, "begin");
        addStr(proximo, "for");

        if (!erro("Token \"begin\" esperado.", proximo))
            if (erro("", S))
            {
                return;
            }
    }

    Conjunto seguidorComandos = criaConjunto(1);
    addStr(seguidorComandos, "end");

    comandos(juntaConjuntos(seguidorComandos, S));

    if (strcmp(token->classe, "end") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        erro("Token \"end\" esperado.", S);
    }
}

void dc(Conjunto S)
{
}

int dc_c()
{
}

int dc_v()
{
}
void tipo_var()
{
    // if (strcmp(token->classe, "n_real") == 0 || strcmp(token->classe, "n_inteiro") == 0)
    // {
    //     *token = analiseLexical();
    // }
    // else
    // {
    //     erro("Tipo da variavel nao reconhecido.");
    //     return;
    // }
}

void vaiaveis()
{
    // if (strcmp(token->classe, "identificador") == 0)
    // {
    //     *token = analiseLexical();
    // }
    // else
    // {
    //     erro("Identificador nao reconhecido.");
    //     return;
    // }

    // *token = analiseLexical();
    // mais_var();
}

void mais_var()
{
}
void dc_p() {}

void parametros() {}

void lista_par() {}

void mais_par()
{
}

void corpo_p() {}

void dc_loc() {}

void lista_arg() {}

void argumentos() {}

void mais_ident() {}

void pfalsa() {}

void comandos(Conjunto S) {}

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
