
#include <stdio.h>
#define MAXPILHA 50

struct TpPilha
{
    int        TOPO;
    TpElemento PILHA[MAXPILHA];
};

void       inicializar  (TpPilha &p);
void       PUSH         (TpPilha &p, TpElemento elemento);
TpElemento POP          (TpPilha &p);
TpElemento elementoTopo (TpPilha p);
char       vazia        (int topo);
char       cheia        (int topo);
void       exibe        (TpPilha p);

void inicializar(TpPilha &p)
{
    p.TOPO = -1;
}

void PUSH(TpPilha &p, TpElemento elemento)
{
    p.PILHA[++p.TOPO] = elemento;
}

TpElemento POP(TpPilha &p)
{
    return p.PILHA[p.TOPO--];
}

TpElemento elementoTopo(TpPilha p)
{
    return p.PILHA[p.TOPO];
}

char vazia(int topo)
{
    return topo == -1;
}

char cheia(int topo)
{
    return topo == MAXPILHA - 1;
}

void exibe(TpPilha p)
{
    while(!vazia(p.TOPO))
        printf("ID:%d Tipo:%d Prior:%d Tempo:%d\n",
               POP(p).id,
               POP(p).tipo,
               POP(p).Prioridade,
               POP(p).tempoExec);
}
