#include <stdio.h>
#define MAXFILA 50

/* elemento que trafega na fila */
struct TpElemento
{
    int id;
    int tipo;       /* GRAV_INT, GRAV_EXT, LEITURA, IMPRESSAO */
    int Prioridade; /* 1=alta ... 4=baixa */
    int tempoExec;  /* ut necessarios para executar */
};

/* fila com prioridade */
struct TpFila
{
    int        FIM;
    TpElemento FILA[MAXFILA];
};

/* prototipos */
void inicializar(TpFila &F);
char filaVazia(int fim);
char filaCheia(int fim);
void inserir (TpFila &F, TpElemento elemento);
TpElemento retirar (TpFila &F);
TpElemento elementoInicio(TpFila F);
TpElemento elementoFim (TpFila F);
void exibir(TpFila F);

void inicializar(TpFila &F)
{
    F.FIM = -1;
}

char filaVazia(int fim)
{
    return fim == -1;
}

char filaCheia(int fim)
{
    return fim == MAXFILA - 1;
}

void inserir(TpFila &F, TpElemento elemento)
{
    int        i;
    TpElemento aux;

    F.FILA[++F.FIM] = elemento;
    i = F.FIM;

    while(i > 0 && F.FILA[i].Prioridade < F.FILA[i-1].Prioridade)
    {
        aux          = F.FILA[i];
        F.FILA[i]    = F.FILA[i-1];
        F.FILA[i-1]  = aux;
        i--;
    }
}

TpElemento retirar(TpFila &F)
{
    int        i;
    TpElemento elem = F.FILA[0];

    for(i = 0; i < F.FIM; i++)
        F.FILA[i] = F.FILA[i+1];

    F.FIM--;
    return elem;
}

TpElemento elementoInicio(TpFila F)
{
    return F.FILA[0];
}

TpElemento elementoFim(TpFila F)
{
    return F.FILA[F.FIM];
}

void exibir(TpFila F)
{
    int i;

    printf("\n  +-----+----------+----------+---------+-----------+");
    printf("\n  | Pos |    ID    |   Tipo   |  Prior  | Tempo(ut) |");
    printf("\n  +-----+----------+----------+---------+-----------+");

    if(filaVazia(F.FIM))
        printf("\n  |             (fila vazia)                     |");
    else
        for(i = 0; i <= F.FIM; i++)
            printf("\n  | %3d | Tar.%4d |  Tipo%d   |   [%d]   |   %2d ut   |",
                   i,
                   F.FILA[i].id,
                   F.FILA[i].tipo,
                   F.FILA[i].Prioridade,
                   F.FILA[i].tempoExec);

    printf("\n  +-----+----------+----------+---------+-----------+\n");
}
