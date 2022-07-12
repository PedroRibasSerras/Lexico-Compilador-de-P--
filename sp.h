#ifndef SP_H // guardas de cabeçalho, impedem inclusões cíclicas
#define SP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char **v;
    int n;
    int p;
} Conjunto;

Conjunto *pprograma;
Conjunto *pcorpo;
Conjunto *pdc;
Conjunto *pdcc;
Conjunto *pdcv;
Conjunto *pdcp;
Conjunto *ptipovar;
Conjunto *pvariaveis;
Conjunto *pmaisvar;
Conjunto *pparametros;
Conjunto *plistapar;
Conjunto *pmaispar;
Conjunto *pcorpop;
Conjunto *pdcloc;
Conjunto *plistaarg;
Conjunto *pargumentos;
Conjunto *pmaisident;
Conjunto *ppfalsa;
Conjunto *pcomandos;
Conjunto *pcmd;
Conjunto *pcondicao;
Conjunto *prelacao;
Conjunto *pexpressao;
Conjunto *popun;
Conjunto *poutrostermos;
Conjunto *popad;
Conjunto *ptermo;
Conjunto *pmaisfatores;
Conjunto *popmul;
Conjunto *pfator;
Conjunto *pnumero;

Conjunto *sprograma;
Conjunto *scorpo;
Conjunto *sdc;
Conjunto *sdcc;
Conjunto *sdcv;
Conjunto *sdcp;
Conjunto *stipovar;
Conjunto *svariaveis;
Conjunto *smaisvar;
Conjunto *sparametros;
Conjunto *slistapar;
Conjunto *smaispar;
Conjunto *scorpop;
Conjunto *sdcloc;
Conjunto *slistaarg;
Conjunto *sargumentos;
Conjunto *smaisident;
Conjunto *spfalsa;
Conjunto *scomandos;
Conjunto *scmd;
Conjunto *scondicao;
Conjunto *srelacao;
Conjunto *sexpressao;
Conjunto *sopun;
Conjunto *soutrostermos;
Conjunto *sopad;
Conjunto *stermo;
Conjunto *smaisfatores;
Conjunto *sopmul;
Conjunto *sfator;
Conjunto *snumero;

Conjunto *juntaConjuntos(Conjunto *, Conjunto *);
void printaConjunto(Conjunto *);
Conjunto *criaConjunto(int);
void freeConjunto(Conjunto *);
void addStr(Conjunto *, char *);
void initPrimeirosESeguidores();
void freePrimeirosESeguidores();

#endif