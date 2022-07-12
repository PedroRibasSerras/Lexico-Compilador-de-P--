#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"

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

//---------------------------------------------
int erro(char *erroMsg, Conjunto *cd, Conjunto *cp) // 0 - seguidor direto, 1 - seguidor do pai, 2- arquivo acabou
{
    if (erroMsg[0] != '\0')
    {
        printErro(erroMsg);
    }

    while (getc(arquivo) != EOF)
    {
        fseek(arquivo, -1, SEEK_CUR);
        // procura entre seus seguidores direto
        for (int i = 0; i <= cd->p; i++)
        {
            if (strcmp(token->classe, cd->v[i]) == 0)
            {
                return 0;
            }
        }
        // caso não tenha encontrado, procura nos seguidores dos pais
        for (int i = 0; i <= cp->p; i++)
        {
            if (strcmp(token->classe, cp->v[i]) == 0)
            {
                return 1;
            }
        }
        *token = analiseLexical();
        printf("%s\n", token->classe);
    }

    return 2;
}

int tokenExisteNoConjunto(Conjunto *c) // 0 - não exite, 1 - existe
{

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

        if (erro("Token \"program\" esperado.@1", proximo, S) == 1)
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

        if (erro("Identificador de programa esperado.@2", proximo, S) == 1)
            return;
    }

    if (strcmp(token->classe, "simb_ponto_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        if (erro("Token ; esperado.@3", pcorpo, S) == 1)
            return;
    }

    corpo(juntaConjuntos(scorpo, S));

    if (strcmp(token->classe, "simb_ponto") == 0)
    {
        return;
    }
    else
    {
        printErro("Ponto (.) esperado no final do codigo.@4");
        return;
    }
}
void corpo(Conjunto *S)
{

    dc(juntaConjuntos(sdc, S));

    if (strcmp(token->classe, "begin") == 0)
    {
        *token = analiseLexical();
    }
    else
    {

        if (erro("Token \"begin\" esperado.@5", pcomandos, S) == 1)
            return;
    }

    comandos(juntaConjuntos(scomandos, S));

    if (strcmp(token->classe, "end") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        erro("Token \"end\" esperado.@6", criaConjunto(0), S);
    }
}

void dc(Conjunto *S)
{
    dc_c(juntaConjuntos(sdcc, S));

    dc_v(juntaConjuntos(sdcv, S));

    dc_p(juntaConjuntos(sdcp, S));
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

        int erroRes = erro("", proximo, S);
        if (erroRes == 1) // caso seja lambda não deve dar erro
        {
            return;
        }
        else if (erroRes == 0)
        {
            printErro("Token \"const\" esperado.@7");
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

        if (erro("Identificador esperado.@8", proximo, S) == 1) //"Token \"=\" esperado."
            return;
    }

    if (strcmp(token->classe, "simb_igual") == 0)
    {
        *token = analiseLexical();
    }
    else
    {

        if (erro("Token \"=\" esperado.@9", pnumero, S) == 1)
            return;
    }

    numero(juntaConjuntos(snumero, S));

    if (strcmp(token->classe, "simb_ponto_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {

        if (erro("Token \";\" esperado.@10", pdcc, S) == 1)
            return;
    }

    dc_c(juntaConjuntos(sdcc, S));
}

void dc_v(Conjunto *S)
{
    if (strcmp(token->classe, "var") == 0)
    {
        *token = analiseLexical();
    }
    else
    {

        int erroRes = erro("", pvariaveis, S);
        if (erroRes == 1) // caso seja lambda não deve dar erro
        {
            return;
        }
        else if (erroRes == 0)
        {
            printErro("Token \"var\" esperado.@11");
        }
    }

    variaveis(juntaConjuntos(svariaveis, S));

    if (strcmp(token->classe, "simb_dois_pontos") == 0)
    {
        *token = analiseLexical();
    }
    else
    {

        if (erro("Token \":\" esperado.@12", ptipovar, S) == 1)
            return;
    }

    tipo_var(juntaConjuntos(stipovar, S));

    if (strcmp(token->classe, "simb_ponto_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {

        if (erro("Token \";\" esperado.@13", pdcv, S) == 1)
            return;
    }

    dc_v(juntaConjuntos(sdcv, S));
}

void tipo_var(Conjunto *S)
{
    if (strcmp(token->classe, "real") == 0 || strcmp(token->classe, "integer") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        erro("Tipo da variável esperado.@14", criaConjunto(0), S);
    }
}

void variaveis(Conjunto *S)
{
    if (strcmp(token->classe, "identificador") == 0 || strcmp(token->classe, "identificador mal formado") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        if (erro("Identificador esperado.@15", pmaisvar, S) == 1) //"Token \"=\" esperado."
            return;
    }

    mais_var(juntaConjuntos(smaisvar, S));
}

void mais_var(Conjunto *S)
{
    if (strcmp(token->classe, "simb_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        int erroRes = erro("", pvariaveis, S);
        if (erroRes == 1) // caso seja lambda não deve dar erro
        {
            return;
        }
        else if (erroRes == 0)
        {
            printErro("Token \",\" esperado.@16");
        }
    }

    // Como mais_variaveis só existe dentro de variaveis, é apenas necessário passar os seguidores dos pais que já incluem os de variaveis.
    variaveis(juntaConjuntos(svariaveis, S));
}
void dc_p(Conjunto *S)
{
    if (strcmp(token->classe, "procedure") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto *proximo = criaConjunto(2);
        addStr(proximo, "identificador");
        addStr(proximo, "identificador mal formado");

        int erroRes = erro("", proximo, S);
        if (erroRes == 1) // caso seja lambda não deve dar erro
        {
            return;
        }
        else if (erroRes == 0)
        {
            printErro("Token \"procedure\" esperado.@17");
        }
    }

    if (strcmp(token->classe, "identificador") == 0 || strcmp(token->classe, "identificador mal formado") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        if (erro("Identificador esperado.@18", pparametros, S) == 1) //"Token \"=\" esperado."
            return;
    }

    parametros(juntaConjuntos(sparametros, S));

    if (strcmp(token->classe, "simb_ponto_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        if (erro("Token \";\" esperado.@19", pcorpop, S) == 1)
            return;
    }

    corpo_p(juntaConjuntos(scorpop, S));

    dc_p(juntaConjuntos(sdcp, S));
}

void parametros(Conjunto *S)
{
    if (strcmp(token->classe, "simb_abre_parenteses") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        int erroRes = erro("", plistapar, S);
        if (erroRes == 1) // caso seja lambda não deve dar erro
        {
            return;
        }
        else if (erroRes == 0)
        {
            printErro("Token \"(\" esperado.@20");
        }
    }

    lista_par(juntaConjuntos(slistapar, S));

    if (strcmp(token->classe, "simb_fecha_parenteses") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        erro("Token \")\" esperado.@21", criaConjunto(0), S);
    }
}

void lista_par(Conjunto *S)
{
    variaveis(juntaConjuntos(svariaveis, S));

    if (strcmp(token->classe, "simb_dois_pontos") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        if (erro("Token \":\" esperado.@22", ptipovar, S) == 1)
            return;
    }

    tipo_var(juntaConjuntos(stipovar, S));

    mais_par(juntaConjuntos(smaispar, S));
}

void mais_par(Conjunto *S)
{
    if (strcmp(token->classe, "simb_ponto_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {

        int erroRes = erro("", plistapar, S);
        if (erroRes == 1) // caso seja lambda não deve dar erro
        {
            return;
        }
        else if (erroRes == 0)
        {
            printErro("Token \";\" esperado.@23");
        }
    }

    // Como mais_par só existe dentro de lista_par, é apenas necessário passar os seguidores dos pais que já incluem o de lista_par.
    lista_par(juntaConjuntos(slistapar, S));
}

void corpo_p(Conjunto *S)
{
    dc_loc(juntaConjuntos(sdcloc, S));

    if (strcmp(token->classe, "begin") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        if (erro("Token \"begin\" esperado.@24", pcomandos, S) == 1)
            return;
    }

    comandos(juntaConjuntos(scomandos, S));

    if (strcmp(token->classe, "end") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        Conjunto *proximo = criaConjunto(1);
        addStr(proximo, "simb_ponto_virgula");

        if (erro("Token \"end\" esperado.@25", proximo, S) == 1)
            return;
    }

    if (strcmp(token->classe, "simb_ponto_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        erro("Token \";\" esperado.@26", criaConjunto(0), S);
    }
}

void dc_loc(Conjunto *S)
{
    dc_v(juntaConjuntos(sdcv, S));
}

void lista_arg(Conjunto *S)
{
    if (strcmp(token->classe, "simb_abre_parenteses") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        int erroRes = erro("", pargumentos, S);
        if (erroRes == 1) // caso seja lambda não deve dar erro
        {
            return;
        }
        else if (erroRes == 0)
        {
            printErro("Token \"(\" esperado.@27");
        }
    }

    argumentos(juntaConjuntos(sargumentos, S));

    if (strcmp(token->classe, "simb_fecha_parenteses") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        erro("Token \")\" esperado.@28", criaConjunto(0), S);
    }
}

void argumentos(Conjunto *S)
{
    if (strcmp(token->classe, "identificador") == 0 || strcmp(token->classe, "identificador mal formado") == 0)
    {
        *token = analiseLexical();
    }
    else
    {
        if (erro("Identificador esperado.@29", pmaisident, S) == 1) //"Token \"=\" esperado."
            return;
    }

    mais_ident(juntaConjuntos(smaisident, S));
}

void mais_ident(Conjunto *S)
{
    if (strcmp(token->classe, "simb_ponto_virgula") == 0)
    {
        *token = analiseLexical();
    }
    else
    {

        int erroRes = erro("", pargumentos, S);
        if (erroRes == 1) // caso seja lambda não deve dar erro
        {
            return;
        }
        else if (erroRes == 0)
        {
            printErro("Token \";\" esperado.@30");
        }
    }

    // Como mais_par só existe dentro de lista_par, é apenas necessário passar os seguidores dos pais que já incluem o de lista_par.
    argumentos(juntaConjuntos(sargumentos, S));
}

void pfalsa(Conjunto *S)
{
    if (strcmp(token->classe, "else") == 0)
    {
        *token = analiseLexical();
    }
    else
    {

        int erroRes = erro("", pcmd, S);
        if (erroRes == 1) // caso seja lambda não deve dar erro
        {
            return;
        }
        else if (erroRes == 0)
        {
            printErro("Token \"else\" esperado.@31");
        }
    }

    // Como mais_par só existe dentro de lista_par, é apenas necessário passar os seguidores dos pais que já incluem o de lista_par.
    cmd(juntaConjuntos(scmd, S));
}

void comandos(Conjunto *S)
{
    if (tokenExisteNoConjunto(pcmd) || !tokenExisteNoConjunto(S))
    {
        cmd(juntaConjuntos(scmd, S));

        if (strcmp(token->classe, "simb_ponto_virgula") == 0)
        {
            *token = analiseLexical();
        }
        else
        {
            if (erro("Identificador esperado.@32", pcomandos, S) == 1) //"Token \"=\" esperado."
                return;
        }

        comandos(juntaConjuntos(scomandos, S));
    }
}
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
