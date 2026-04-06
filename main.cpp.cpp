#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXFILA      50
#define MAXPROC      10
#define MAXREG       1000

/* tipos de tarefa */
#define GRAV_INT     1
#define GRAV_EXT     2
#define LEITURA      3
#define IMPRESSAO    4

/* tempo de cada tarefa em ut */
#define UT_GRAV_INT  5
#define UT_GRAV_EXT  8
#define UT_LEITURA   4
#define UT_IMPRESSAO 3

/* processador */
struct TpProcessador
{
    int id;
    int ocupado;
    int tempoRestante;
    int totalTarefas;
    int totalUt;
};
