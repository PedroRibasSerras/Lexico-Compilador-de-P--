#include "sp.h"

Conjunto *juntaConjuntos(Conjunto *c1, Conjunto *c2)
{
    Conjunto *novoConjunto = (Conjunto *)malloc((1) * sizeof(Conjunto));
    novoConjunto->v = (char **)malloc((c1->n + c2->n) * sizeof(char *));
    for (int i = 0; i <= c1->p; i++)
    {
        novoConjunto->v[i] = (char *)malloc((strlen(c1->v[i]) + 1) * sizeof(char)); // era sizeof(c1->v[i]), mas estava dando errado por algum motivo maluco
        strcpy(novoConjunto->v[i], c1->v[i]);
    }
    for (int i = 0; i <= c2->p; i++)
    {
        novoConjunto->v[c1->p + 1 + i] = (char *)malloc((strlen(c2->v[i]) + 1) * sizeof(char)); // era sizeof(c1->v[i]), mas estava dando errado por algum motivo maluco
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

void freeConjunto(Conjunto *c)
{
    for (int i = 0; i <= c->p; i++)
    {
        free(c->v[i]);
    }
    free(c->v);
    free(c);
}

void addStr(Conjunto *c, char *str)
{
    c->p = c->p + 1;
    c->v[c->p] = (char *)malloc((strlen(str) + 1) * sizeof(char));
    strcpy(c->v[c->p], str);
}

void initPrimeirosESeguidores()
{
    pprograma = criaConjunto(1);
    addStr(pprograma, "program");

    pcorpo = criaConjunto(4);
    addStr(pcorpo, "const");
    addStr(pcorpo, "var");
    addStr(pcorpo, "procedure");
    addStr(pcorpo, "begin");

    pdc = criaConjunto(3);
    addStr(pdc, "const");
    addStr(pdc, "var");
    addStr(pdc, "procedure");

    pdcc = criaConjunto(1);
    addStr(pdcc, "const");

    pdcv = criaConjunto(1);
    addStr(pdcv, "var");

    pdcp = criaConjunto(1);
    addStr(pdcp, "procedure");

    ptipovar = criaConjunto(2);
    addStr(ptipovar, "integer");
    addStr(ptipovar, "real");

    pvariaveis = criaConjunto(2);
    addStr(pvariaveis, "identificador");
    addStr(pvariaveis, "identificador mal formado");

    pmaisvar = criaConjunto(1);
    addStr(pmaisvar, "simb_virgula");

    pparametros = criaConjunto(1);
    addStr(pparametros, "simb_abre_parenteses");

    plistapar = criaConjunto(2);
    addStr(plistapar, "identificador");
    addStr(plistapar, "identificador mal formado");

    pmaispar = criaConjunto(1);
    addStr(pmaispar, "simb_ponto_virgula");

    pcorpop = criaConjunto(2);
    addStr(pcorpop, "var");
    addStr(pcorpop, "begin");

    pdcloc = criaConjunto(1);
    addStr(pdcloc, "var");

    plistaarg = criaConjunto(1);
    addStr(plistaarg, "simb_abre_parenteses");

    pargumentos = criaConjunto(2);
    addStr(pargumentos, "identificador");
    addStr(pargumentos, "identificador mal formado");

    pmaisident = criaConjunto(1);
    addStr(pmaisident, "simb_ponto_virgula");

    ppfalsa = criaConjunto(1);
    addStr(ppfalsa, "else");

    pcomandos = criaConjunto(8);
    addStr(pcomandos, "read");
    addStr(pcomandos, "write");
    addStr(pcomandos, "while");
    addStr(pcomandos, "if");

    addStr(pcomandos, "identificador"); // duas regras - deve ser tratado
    addStr(pcomandos, "identificador mal formado");

    addStr(pcomandos, "begin");
    addStr(pcomandos, "for");

    pcmd = criaConjunto(8);
    addStr(pcmd, "read");
    addStr(pcmd, "write");
    addStr(pcmd, "while");
    addStr(pcmd, "if");

    addStr(pcmd, "identificador"); // duas regras - deve ser tratado
    addStr(pcmd, "identificador mal formado");

    addStr(pcmd, "begin");
    addStr(pcmd, "for");

    pcondicao = criaConjunto(7);
    addStr(pcondicao, "simb_mais");
    addStr(pcondicao, "simb_menos");

    addStr(pcondicao, "identificador");
    addStr(pcondicao, "identificador mal formado");

    addStr(pcondicao, "n_real");
    addStr(pcondicao, "n_inteiro");
    addStr(pcondicao, "simb_abre_parenteses");

    prelacao = criaConjunto(6);
    addStr(prelacao, "simb_igual");
    addStr(prelacao, "simb_dif");
    addStr(prelacao, "simb_maior_igual");
    addStr(prelacao, "simb_menor_igual");
    addStr(prelacao, "simb_maior");
    addStr(prelacao, "simb_menor");

    pexpressao = criaConjunto(7);
    addStr(pexpressao, "simb_mais");
    addStr(pexpressao, "simb_menos");

    addStr(pexpressao, "identificador");
    addStr(pexpressao, "identificador mal formado");

    addStr(pexpressao, "n_real");
    addStr(pexpressao, "n_inteiro");
    addStr(pexpressao, "simb_abre_parenteses");

    popun = criaConjunto(2);
    addStr(popun, "simb_mais");
    addStr(popun, "simb_menos");

    poutrostermos = criaConjunto(2);
    addStr(poutrostermos, "simb_mais");
    addStr(poutrostermos, "simb_menos");

    popad = criaConjunto(2);
    addStr(popad, "simb_mais");
    addStr(popad, "simb_menos");

    ptermo = criaConjunto(7);
    addStr(ptermo, "simb_mais");
    addStr(ptermo, "simb_menos");

    addStr(ptermo, "identificador");
    addStr(ptermo, "identificador mal formado");

    addStr(ptermo, "n_real");
    addStr(ptermo, "n_inteiro");
    addStr(ptermo, "simb_abre_parenteses");

    pmaisfatores = criaConjunto(2);
    addStr(pmaisfatores, "simb_mult");   // *
    addStr(pmaisfatores, "sim_divider"); // /

    popmul = criaConjunto(2);
    addStr(popmul, "simb_mult");   // *
    addStr(popmul, "sim_divider"); // /

    pfator = criaConjunto(5);
    addStr(pfator, "identificador");
    addStr(pfator, "identificador mal formado");

    addStr(pfator, "n_real");
    addStr(pfator, "n_inteiro");
    addStr(pfator, "simb_abre_parenteses");

    pnumero = criaConjunto(2);
    addStr(pnumero, "n_real");
    addStr(pnumero, "n_inteiro");

    // Seguidores

    sprograma = criaConjunto(0);

    scorpo = criaConjunto(1);
    addStr(scorpo, "simb_ponto");

    sdc = criaConjunto(1);
    addStr(sdc, "begin");

    sdcc = criaConjunto(3);
    addStr(sdcc, "var");
    addStr(sdcc, "procedure");
    addStr(sdcc, "begin");

    sdcv = criaConjunto(2);
    addStr(sdcv, "procedure");
    addStr(sdcv, "begin");

    sdcp = criaConjunto(1);
    addStr(sdcp, "begin");

    stipovar = criaConjunto(2);
    addStr(stipovar, "simb_ponto_virgula");
    addStr(stipovar, "simb_fecha_parenteses");

    svariaveis = criaConjunto(2);
    addStr(svariaveis, "simb_dois_pontos");
    addStr(svariaveis, "simb_fecha_parenteses");

    smaisvar = criaConjunto(2);
    addStr(smaisvar, "simb_dois_pontos");
    addStr(smaisvar, "simb_fecha_parenteses");

    sparametros = criaConjunto(1);
    addStr(sparametros, "simb_ponto_virgula");

    slistapar = criaConjunto(1);
    addStr(slistapar, "simb_fecha_parenteses");

    smaispar = criaConjunto(1);
    addStr(smaispar, "simb_fecha_parenteses");

    scorpop = criaConjunto(2);
    addStr(scorpop, "procedure");
    addStr(scorpop, "begin");

    sdcloc = criaConjunto(1);
    addStr(sdcloc, "begin");

    slistaarg = criaConjunto(2);
    addStr(slistaarg, "simb_ponto_virgula");
    addStr(slistaarg, "else");

    sargumentos = criaConjunto(1);
    addStr(sargumentos, "simb_fecha_parenteses");

    smaisident = criaConjunto(1);
    addStr(smaisident, "simb_fecha_parenteses");

    spfalsa = criaConjunto(2);
    addStr(spfalsa, "simb_ponto_virgula");
    addStr(spfalsa, "else");

    scomandos = criaConjunto(1);
    addStr(scomandos, "end");

    scmd = criaConjunto(2);
    addStr(scmd, "simb_ponto_virgula");
    addStr(scmd, "else");

    scondicao = criaConjunto(2);
    addStr(scondicao, "simb_fecha_parenteses");
    addStr(scondicao, "then");

    srelacao = criaConjunto(7);
    addStr(srelacao, "simb_mais");
    addStr(srelacao, "simb_menos");

    addStr(srelacao, "identificador");
    addStr(srelacao, "identificador mal formado");

    addStr(srelacao, "n_real");
    addStr(srelacao, "n_inteiro");
    addStr(srelacao, "simb_abre_parenteses");

    sexpressao = criaConjunto(12);
    addStr(sexpressao, "simb_ponto_virgula");
    addStr(sexpressao, "else");
    addStr(sexpressao, "simb_igual");
    addStr(sexpressao, "simb_dif");
    addStr(sexpressao, "simb_maior_igual");
    addStr(sexpressao, "simb_menor_igual");
    addStr(sexpressao, "simb_maior");
    addStr(sexpressao, "simb_menor");
    addStr(sexpressao, "simb_fecha_parenteses");
    addStr(sexpressao, "then");
    addStr(sexpressao, "to");
    addStr(sexpressao, "do");

    sopun = criaConjunto(5);
    addStr(sopun, "identificador");
    addStr(sopun, "identificador mal formado");

    addStr(sopun, "n_real");
    addStr(sopun, "n_inteiro");
    addStr(sopun, "simb_abre_parenteses");

    soutrostermos = criaConjunto(12);
    addStr(soutrostermos, "simb_ponto_virgula");
    addStr(soutrostermos, "else");
    addStr(soutrostermos, "simb_igual");
    addStr(soutrostermos, "simb_dif");
    addStr(soutrostermos, "simb_maior_igual");
    addStr(soutrostermos, "simb_menor_igual");
    addStr(soutrostermos, "simb_maior");
    addStr(soutrostermos, "simb_menor");
    addStr(soutrostermos, "simb_fecha_parenteses");
    addStr(soutrostermos, "then");
    addStr(soutrostermos, "to");
    addStr(soutrostermos, "do");

    sopad = criaConjunto(7);
    addStr(sopad, "simb_mais");
    addStr(sopad, "simb_menos");

    addStr(sopad, "identificador");
    addStr(sopad, "identificador mal formado");

    addStr(sopad, "n_real");
    addStr(sopad, "n_inteiro");
    addStr(sopad, "simb_abre_parenteses");

    stermo = criaConjunto(14);
    addStr(stermo, "simb_mais");
    addStr(stermo, "simb_menos");
    addStr(stermo, "simb_ponto_virgula");
    addStr(stermo, "else");
    addStr(stermo, "simb_igual");
    addStr(stermo, "simb_dif");
    addStr(stermo, "simb_maior_igual");
    addStr(stermo, "simb_menor_igual");
    addStr(stermo, "simb_maior");
    addStr(stermo, "simb_menor");
    addStr(stermo, "simb_fecha_parenteses");
    addStr(stermo, "then");
    addStr(stermo, "to");
    addStr(stermo, "do");

    smaisfatores = criaConjunto(14);
    addStr(smaisfatores, "simb_mais");
    addStr(smaisfatores, "simb_menos");
    addStr(smaisfatores, "simb_ponto_virgula");
    addStr(smaisfatores, "else");
    addStr(smaisfatores, "simb_igual");
    addStr(smaisfatores, "simb_dif");
    addStr(smaisfatores, "simb_maior_igual");
    addStr(smaisfatores, "simb_menor_igual");
    addStr(smaisfatores, "simb_maior");
    addStr(smaisfatores, "simb_menor");
    addStr(smaisfatores, "simb_fecha_parenteses");
    addStr(smaisfatores, "then");
    addStr(smaisfatores, "to");
    addStr(smaisfatores, "do");

    sopmul = criaConjunto(5);
    addStr(sopmul, "identificador");
    addStr(sopmul, "identificador mal formado");

    addStr(sopmul, "n_real");
    addStr(sopmul, "n_inteiro");
    addStr(sopmul, "simb_abre_parenteses");

    sfator = criaConjunto(16);
    addStr(sfator, "simb_mult");   // *
    addStr(sfator, "sim_divider"); // /
    addStr(sfator, "simb_mais");
    addStr(sfator, "simb_menos");
    addStr(sfator, "simb_ponto_virgula");
    addStr(sfator, "else");
    addStr(sfator, "simb_igual");
    addStr(sfator, "simb_dif");
    addStr(sfator, "simb_maior_igual");
    addStr(sfator, "simb_menor_igual");
    addStr(sfator, "simb_maior");
    addStr(sfator, "simb_menor");
    addStr(sfator, "simb_fecha_parenteses");
    addStr(sfator, "then");
    addStr(sfator, "to");
    addStr(sfator, "do");

    snumero = criaConjunto(16);
    addStr(snumero, "simb_mult");   // *
    addStr(snumero, "sim_divider"); // /
    addStr(snumero, "simb_mais");
    addStr(snumero, "simb_menos");
    addStr(snumero, "simb_ponto_virgula");
    addStr(snumero, "else");
    addStr(snumero, "simb_igual");
    addStr(snumero, "simb_dif");
    addStr(snumero, "simb_maior_igual");
    addStr(snumero, "simb_menor_igual");
    addStr(snumero, "simb_maior");
    addStr(snumero, "simb_menor");
    addStr(snumero, "simb_fecha_parenteses");
    addStr(snumero, "then");
    addStr(snumero, "to");
    addStr(snumero, "do");
}

void freePrimeirosESeguidores()
{
    freeConjunto(pprograma);
    freeConjunto(pcorpo);
    freeConjunto(pdc);
    freeConjunto(pdcc);
    freeConjunto(pdcv);
    freeConjunto(pdcp);
    freeConjunto(ptipovar);
    freeConjunto(pvariaveis);
    freeConjunto(pmaisvar);
    freeConjunto(pparametros);
    freeConjunto(plistapar);
    freeConjunto(pmaispar);
    freeConjunto(pcorpop);
    freeConjunto(pdcloc);
    freeConjunto(plistaarg);
    freeConjunto(pargumentos);
    freeConjunto(pmaisident);
    freeConjunto(ppfalsa);
    freeConjunto(pcomandos);
    freeConjunto(pcmd);
    freeConjunto(pcondicao);
    freeConjunto(prelacao);
    freeConjunto(pexpressao);
    freeConjunto(popun);
    freeConjunto(poutrostermos);
    freeConjunto(popad);
    freeConjunto(ptermo);
    freeConjunto(pmaisfatores);
    freeConjunto(popmul);
    freeConjunto(pfator);
    freeConjunto(pnumero);

    freeConjunto(sprograma);
    freeConjunto(scorpo);
    freeConjunto(sdc);
    freeConjunto(sdcc);
    freeConjunto(sdcv);
    freeConjunto(sdcp);
    freeConjunto(stipovar);
    freeConjunto(svariaveis);
    freeConjunto(smaisvar);
    freeConjunto(sparametros);
    freeConjunto(slistapar);
    freeConjunto(smaispar);
    freeConjunto(scorpop);
    freeConjunto(sdcloc);
    freeConjunto(slistaarg);
    freeConjunto(sargumentos);
    freeConjunto(smaisident);
    freeConjunto(spfalsa);
    freeConjunto(scomandos);
    freeConjunto(scmd);
    freeConjunto(scondicao);
    freeConjunto(srelacao);
    freeConjunto(sexpressao);
    freeConjunto(sopun);
    freeConjunto(soutrostermos);
    freeConjunto(sopad);
    freeConjunto(stermo);
    freeConjunto(smaisfatores);
    freeConjunto(sopmul);
    freeConjunto(sfator);
    freeConjunto(snumero);
}