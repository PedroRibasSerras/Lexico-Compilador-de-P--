#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexico.h"

int numOutrosReconheciveis = 17;
char outrosReconheciveis[17] = {'.', ';', '/', '(', ')', '=', '*', ':', ',', '+', '-', '>', '<', '{', ' ', '\t', '\n'};

int **criaTabelaTransicao()
{

    int numEstados = 35;
    int **tabelaDeTrasicao = (int **)malloc(numEstados * sizeof(int *));
    for (int i = 0; i < numEstados; i++)
    {
        tabelaDeTrasicao[i] = (int *)malloc(256 * sizeof(int));
    }

    for (int i = 0; i < numEstados; i++)
    {
        for (int j = 0; j < 256; j++)
        {
            tabelaDeTrasicao[i][j] = -1;
        }
    }

    tabelaDeTrasicao[0]['.'] = 1;
    tabelaDeTrasicao[0][';'] = 2;
    tabelaDeTrasicao[0]['/'] = 3;
    tabelaDeTrasicao[0]['('] = 4;
    tabelaDeTrasicao[0]['='] = 5;
    tabelaDeTrasicao[0]['*'] = 6;

    // Dois pontos
    tabelaDeTrasicao[0][':'] = 7;
    for (int j = 0; j < 256; j++)
    {
        tabelaDeTrasicao[7][j] = 9;
    }
    tabelaDeTrasicao[7]['='] = 8;

    tabelaDeTrasicao[0][','] = 10;

    //+ e -
    tabelaDeTrasicao[0]['+'] = 11;
    tabelaDeTrasicao[0]['-'] = 12;

    // Maior
    tabelaDeTrasicao[0]['>'] = 13;
    for (int j = 0; j < 256; j++)
    {
        tabelaDeTrasicao[13][j] = 15;
    }
    tabelaDeTrasicao[13]['='] = 14;

    // Menor
    tabelaDeTrasicao[0]['<'] = 16;
    for (int j = 0; j < 256; j++)
    {
        tabelaDeTrasicao[16][j] = 17;
    }
    tabelaDeTrasicao[16]['='] = 18;
    tabelaDeTrasicao[16]['>'] = 19;

    // Letra - simolo reservado ou identificador
    for (int j = 0; j < 256; j++)
    {
        tabelaDeTrasicao[22][j] = 32;
    }
    for (int j = 0; j < numOutrosReconheciveis; j++)
    {
        tabelaDeTrasicao[22][outrosReconheciveis[j]] = 23;
    }
    for (int j = 'a'; j <= 'z'; j++)
    {
        tabelaDeTrasicao[0][j] = 22;
        tabelaDeTrasicao[22][j] = 22;
    }
    for (int j = 'A'; j <= 'Z'; j++)
    {
        tabelaDeTrasicao[0][j] = 22;
        tabelaDeTrasicao[22][j] = 22;
    }
    for (int j = '0'; j <= '9'; j++)
    {
        tabelaDeTrasicao[22][j] = 22;
    }

    // Coment??rio
    tabelaDeTrasicao[0]['{'] = 20;
    for (int j = 0; j < 256; j++)
    {
        tabelaDeTrasicao[20][j] = 20;
    }
    tabelaDeTrasicao[20]['\n'] = 31;
    tabelaDeTrasicao[20]['}'] = 21;

    // N??meros

    for (int j = 0; j < 256; j++)
    {
        tabelaDeTrasicao[24][j] = 33;
        tabelaDeTrasicao[26][j] = 27;
        tabelaDeTrasicao[28][j] = 34;
    }
    for (int j = 0; j < numOutrosReconheciveis; j++)
    {
        tabelaDeTrasicao[24][outrosReconheciveis[j]] = 25;
        tabelaDeTrasicao[28][outrosReconheciveis[j]] = 29;
    }
    for (int j = '0'; j <= '9'; j++)
    {
        tabelaDeTrasicao[0][j] = 24;
        tabelaDeTrasicao[24][j] = 24;
        tabelaDeTrasicao[26][j] = 28;
        tabelaDeTrasicao[28][j] = 28;
    }
    tabelaDeTrasicao[24]['.'] = 26;

    tabelaDeTrasicao[0][')'] = 30;

    return tabelaDeTrasicao;
}

Estado criaEstado(int final, int retrocede, char *msg, int erro)
{
    Estado e;
    e.final = final;
    e.retrocede = retrocede;
    e.mensagem = (char *)malloc(50 * sizeof(char));
    strcpy(e.mensagem, msg);
    e.erro = erro;

    return e;
}

Estado *criaTabelaDeEstados()
{
    int numEstados = 35;
    Estado *tabelaDeEstados = (Estado *)malloc(numEstados * sizeof(Estado));

    tabelaDeEstados[0] = criaEstado(0, 0, "", 0);
    tabelaDeEstados[1] = criaEstado(1, 0, "simb_ponto", 0);
    tabelaDeEstados[2] = criaEstado(1, 0, "simb_ponto_virgula", 0);
    tabelaDeEstados[3] = criaEstado(1, 0, "sim_divider", 0);
    tabelaDeEstados[4] = criaEstado(1, 0, "simb_abre_parenteses", 0);
    tabelaDeEstados[5] = criaEstado(1, 0, "simb_igual", 0);
    tabelaDeEstados[6] = criaEstado(1, 0, "simb_mult", 0);
    tabelaDeEstados[7] = criaEstado(0, 0, "", 0);
    tabelaDeEstados[8] = criaEstado(1, 0, "simb_atrib", 0);
    tabelaDeEstados[9] = criaEstado(1, 1, "simb_dois_pontos", 0);
    tabelaDeEstados[10] = criaEstado(1, 0, "simb_virgula", 0);
    tabelaDeEstados[11] = criaEstado(1, 0, "simb_mais", 0);
    tabelaDeEstados[12] = criaEstado(1, 0, "simb_menos", 0);
    tabelaDeEstados[13] = criaEstado(0, 0, "", 0);
    tabelaDeEstados[14] = criaEstado(1, 0, "simb_maior_igual", 0);
    tabelaDeEstados[15] = criaEstado(1, 1, "simb_maior", 0);
    tabelaDeEstados[16] = criaEstado(0, 0, "", 0);
    tabelaDeEstados[17] = criaEstado(1, 1, "simb_menor", 0);
    tabelaDeEstados[18] = criaEstado(1, 0, "simb_menor_igual", 0);
    tabelaDeEstados[19] = criaEstado(1, 0, "simb_dif", 0);
    tabelaDeEstados[20] = criaEstado(0, 0, "", 0);
    tabelaDeEstados[21] = criaEstado(1, 0, "comentario", 0);
    tabelaDeEstados[22] = criaEstado(0, 0, "", 0);
    tabelaDeEstados[23] = criaEstado(1, 1, "identificador", 0); // deve ser tratado a parte
    tabelaDeEstados[24] = criaEstado(0, 0, "", 0);
    tabelaDeEstados[25] = criaEstado(1, 1, "n_inteiro", 0);
    tabelaDeEstados[26] = criaEstado(0, 0, "", 0);
    tabelaDeEstados[27] = criaEstado(1, 1, "Nao e aceito um real sem a parte decimal", 1); // Erro
    tabelaDeEstados[28] = criaEstado(0, 0, "", 0);
    tabelaDeEstados[29] = criaEstado(1, 1, "n_real", 0);
    tabelaDeEstados[30] = criaEstado(1, 0, "simb_fecha_parenteses", 0);
    tabelaDeEstados[31] = criaEstado(1, 1, "comentario deve ser de linha unica", 1); // Erro
    tabelaDeEstados[32] = criaEstado(1, 0, "identificador mal formado", 1);          // Erro
    tabelaDeEstados[33] = criaEstado(1, 0, "numero mal formado", 1);                 // Erro
    tabelaDeEstados[34] = criaEstado(1, 0, "real mal formado", 1);                   // Erro

    // Cria um vetor com todos os estados, marcando os finais com final = 1;
    // se tiver que retroceder retrocede = 1;
    // A mensagem ?? pode ser de erro ou de deu bom.

    return tabelaDeEstados;
}

char **criaTabelaSimbolosReservados()
{
    int numSimbolos = 17;
    char **tabelaDeSibolosReservados = (char **)malloc(numSimbolos * sizeof(char *));
    for (int i = 0; i < numSimbolos; i++)
    {
        tabelaDeSibolosReservados[i] = (char *)malloc(15 * sizeof(char));
    }

    strcpy(tabelaDeSibolosReservados[0], "program");
    strcpy(tabelaDeSibolosReservados[1], "begin");
    strcpy(tabelaDeSibolosReservados[2], "end");
    strcpy(tabelaDeSibolosReservados[3], "const");
    strcpy(tabelaDeSibolosReservados[4], "var");
    strcpy(tabelaDeSibolosReservados[5], "real");
    strcpy(tabelaDeSibolosReservados[6], "integer");
    strcpy(tabelaDeSibolosReservados[7], "procedure");
    strcpy(tabelaDeSibolosReservados[8], "else");
    strcpy(tabelaDeSibolosReservados[9], "read");
    strcpy(tabelaDeSibolosReservados[10], "write");
    strcpy(tabelaDeSibolosReservados[11], "while");
    strcpy(tabelaDeSibolosReservados[12], "do");
    strcpy(tabelaDeSibolosReservados[13], "if");
    strcpy(tabelaDeSibolosReservados[14], "then");
    strcpy(tabelaDeSibolosReservados[15], "for");
    strcpy(tabelaDeSibolosReservados[16], "to");

    return tabelaDeSibolosReservados;
}

int eReservado(char *s, char **TSR)
{
    int numSimbolos = 17;
    for (int i = 0; i < numSimbolos; i++)
    {
        if (strcmp(s, TSR[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

RetornoLexical analiseLexical()
{
    char inicioErroMsg[50];
    int it = 0;
    int si = 0;
    RetornoLexical result;
    result.classe = (char *)malloc(50 * sizeof(char));
    result.token = (char *)malloc(50 * sizeof(char));

    char simb = getc(arquivo);

    while (simb != EOF)
    {
        si = TT[si][(int)simb];

        // caso a analise tenha encontrado o comentario, ele deve ser ignorado e o proximo tolken deve ser enviado
        if (si == 21)
        {
            return analiseLexical();
        }

        if (si == -1)
        {

            if (simb != '\n' && simb != '\t' && simb != ' ')
            {
                result.token[it] = simb;
                result.token[it + 1] = '\0';
                strcpy(result.classe, "Caractere invalido");

                if (TE[si].erro)
                {
                    sprintf(inicioErroMsg, "Erro lexico na linha %d:", *contadorLinha);
                    fputs(inicioErroMsg, saida);
                    // fputs(result.token, saida);
                    // fputs(", ", saida);
                    fputs(result.classe, saida);
                    fputc('\n', saida);
                }
                return result;
            }
            si = 0;
        }
        else if (TE[si].final)
        {
            strcpy(result.classe, TE[si].mensagem);
            if (TE[si].retrocede)
            {
                fseek(arquivo, -1, SEEK_CUR);
                result.token[it] = '\0';
                if (eReservado(result.token, TSR))
                {
                    strcpy(result.classe, result.token);
                }
                return result;
            }
            result.token[it] = simb;
            result.token[it + 1] = '\0';

            if (TE[si].erro)
            {
                sprintf(inicioErroMsg, "Erro lexico na linha %d:", *contadorLinha);
                fputs(inicioErroMsg, saida);
                // fputs(result.token, saida);
                // fputs(", ", saida);
                fputs(result.classe, saida);
                fputc('\n', saida);
            }

            return result;
        }

        if ((simb != '\n' && simb != '\t' && simb != ' ') || si == 20)
        {
            result.token[it] = simb;
            it++;
        }
        if (simb == '\n')
            *contadorLinha = *contadorLinha + 1;
        simb = getc(arquivo);
    }
    if (it > 0)
    {
        printf("%i ", si);
        si = TT[si][(int)' '];
        if (TE[si].final)
        {
            strcpy(result.classe, TE[si].mensagem);
            if (TE[si].retrocede)
            {
                result.token[it] = '\0';
                if (eReservado(result.token, TSR))
                {
                    strcpy(result.classe, result.token);
                }

                if (TE[si].erro)
                {
                    sprintf(inicioErroMsg, "Erro lexico na linha %d:", *contadorLinha);
                    fputs(inicioErroMsg, saida);
                    // fputs(result.token, saida);
                    // fputs(", ", saida);
                    fputs(result.classe, saida);
                    fputc('\n', saida);
                }

                return result;
            }
            result.token[it] = simb;
            result.token[it + 1] = '\0';

            if (TE[si].erro)
            {
                sprintf(inicioErroMsg, "Erro lexico na linha %d:", *contadorLinha);
                fputs(inicioErroMsg, saida);
                // fputs(result.token, saida);
                // fputs(", ", saida);
                fputs(result.classe, saida);
                fputc('\n', saida);
            }

            return result;
        }
    }
    strcpy(result.classe, "estado final nao reconhecido");

    sprintf(inicioErroMsg, "Erro lexico na linha %d:", *contadorLinha);
    fputs(inicioErroMsg, saida);
    // fputs(result.token, saida);
    // fputs(", ", saida);
    fputs(result.classe, saida);
    fputc('\n', saida);

    return result;
}