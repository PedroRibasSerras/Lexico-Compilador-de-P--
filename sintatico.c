#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"

Conjunto *juntaConjuntos(Conjunto *c1, Conjunto *c2)
{
    Conjunto *novoConjunto = (Conjunto *)malloc((1) * sizeof(Conjunto));
    novoConjunto->v = (char **)malloc((c1->n + c2->n) * sizeof(char *));
    for (int i = 0; i <= c1->p; i++)
    {
        novoConjunto->v[i] = (char *)malloc(sizeof(c1->v[i]));
        strcpy(novoConjunto->v[i], c1->v[i]);
    }
    for (int i = 0; i <= c2->p; i++)
    {
        novoConjunto->v[c1->p + 1 + i] = (char *)malloc(sizeof(c2->v[i]));
        strcpy(novoConjunto->v[c1->p + 1 + i], c2->v[i]);
    }
    novoConjunto->n = c1->n + c2->n;
    novoConjunto->p = c1->p + c2->p + 1;

    return novoConjunto;
}

void printaConjunto(Conjunto *c)
{
    for (int i = 0; i <= c->p; i++)
    {
        printf("%s\n", c->v[i]);
    }
}

Conjunto *criaConjunto(int n)
{
    Conjunto *c = (Conjunto *)malloc((1) * sizeof(Conjunto));
    c->v = (char **)malloc((n) * sizeof(char *));
    c->n = n;
    c->p = -1;

    return c;
}

void addStr(Conjunto *c, char *str)
{
    c->p = c->p + 1;
    c->v[c->p] = str;
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

int erro(char *erroMsg, Conjunto *c)
{
    if (erroMsg[0] != '\0')
    {
        printErro(erroMsg);
    }

    for (int i = 0; i <= c->p; i++)
    {
        if (strcmp(token->classe, c->v[i]) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void programa(Conjunto *S)
{
    if (strcmp(token->classe, "program") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto *proximo = criaConjunto(2);
        addStr(proximo, "identficador");
        addStr(proximo, "identificador mal formado");

        if (!erro("Token \"program\" esperado.", proximo))
            if (erro("", S))
            {
                return;
            }
    }

    if (strcmp(token->classe, "identificador") == 0 || strcmp(token->classe, "identificador mal formado") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto *proximo = criaConjunto(1);
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
        Conjunto *proximo = criaConjunto(3);
        addStr(proximo, "const");
        addStr(proximo, "var");
        addStr(proximo, "procedure");

        if (!erro("Token ; esperado.", proximo))
            if (erro("", S))
            {
                return;
            }
    }

    Conjunto *seguidorCorpo = criaConjunto(1);
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
void corpo(Conjunto *S)
{
    Conjunto *seguidorDc = criaConjunto(1);
    addStr(seguidorDc, "begin");

    dc(juntaConjuntos(seguidorDc, S));

    if (strcmp(token->classe, "begin") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto *proximo = criaConjunto(7);
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

    Conjunto *seguidorComandos = criaConjunto(1);
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

void dc(Conjunto *S)
{

    Conjunto *seguidorDcc = criaConjunto(2);
    addStr(seguidorDcc, "var");
    addStr(seguidorDcc, "procedure");
    // addStr(seguidorDcc, "begin"); não é necessário pq já existe no S

    dc_c(juntaConjuntos(seguidorDcc, S));

    Conjunto *seguidorDcv = criaConjunto(1);
    addStr(seguidorDcv, "procedure");

    dc_v(juntaConjuntos(seguidorDcv, S));

    dc_p(S);
}

void dc_c(Conjunto *S)
{
    if (strcmp(token->classe, "const") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto *proximo = criaConjunto(2);
        addStr(proximo, "identificador");
        addStr(proximo, "identificador mal formado");

        if (!erro("", proximo)) // caso seja lambda não deve dar erro
        {
            if (erro("", S))
            {
                return;
            }
        }
        else
        {
            printErro("Token \"const\" esperado.");
        }
    }

    if (strcmp(token->classe, "identificador") == 0 || strcmp(token->classe, "identificador mal formado") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto *proximo = criaConjunto(1);
        addStr(proximo, "simb_igual");

        if (!erro("Identificador esperado.", proximo)) //"Token \"=\" esperado."
            if (erro("", S))
            {
                return;
            }
    }

    if (strcmp(token->classe, "simb_igual") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto *proximo = criaConjunto(2);
        addStr(proximo, "n_inteiro");
        addStr(proximo, "n_real");

        if (!erro("Token \"=\" esperado.", proximo))
            if (erro("", S))
            {
                return;
            }
    }

    Conjunto *seguidorNumero = criaConjunto(14);
    addStr(seguidorNumero, "simb_mult");   // *
    addStr(seguidorNumero, "sim_divider"); // /
    addStr(seguidorNumero, "simb_mais");
    addStr(seguidorNumero, "simb_menos");
    addStr(seguidorNumero, "simb_ponto_virgula");
    addStr(seguidorNumero, "else");
    addStr(seguidorNumero, "simb_igual");
    addStr(seguidorNumero, "simb_dif");
    addStr(seguidorNumero, "simb_maior_igual");
    addStr(seguidorNumero, "simb_menor_igual");
    addStr(seguidorNumero, "simb_maior");
    addStr(seguidorNumero, "simb_menor");
    addStr(seguidorNumero, "simb_fecha_parenteses");
    addStr(seguidorNumero, "then");

    numero(juntaConjuntos(seguidorNumero, S));

    if (strcmp(token->classe, "simb_ponto_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto *proximo = criaConjunto(1);
        addStr(proximo, "const");

        if (!erro("Token \"=\" esperado.", proximo))
            if (erro("", S))
            {
                return;
            }
    }

    dc_c(S);
}

void dc_v(Conjunto *S)
{
}
void tipo_var(Conjunto *S)
{
}

void vaiaveis(Conjunto *S)
{
}

void mais_var(Conjunto *S)
{
}
void dc_p(Conjunto *S) {}

void parametros(Conjunto *S) {}

void lista_par(Conjunto *S) {}

void mais_par(Conjunto *S)
{
}

void corpo_p(Conjunto *S) {}

void dc_loc(Conjunto *S) {}

void lista_arg(Conjunto *S) {}

void argumentos(Conjunto *S) {}

void mais_ident(Conjunto *S) {}

void pfalsa(Conjunto *S) {}

void comandos(Conjunto *S) {}

void cmd(Conjunto *S) {}

void condicao(Conjunto *S) {}

void relacao(Conjunto *S) {}

void expressao(Conjunto *S) {}

void op_un(Conjunto *S) {}

void outros_termos(Conjunto *S) {}

void op_ad(Conjunto *S) {}

void termo(Conjunto *S) {}

void mais_fatores(Conjunto *S) {}

void op_mul(Conjunto *S) {}

void fator(Conjunto *S) {}

void numero(Conjunto *S) {}
