#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "TADFilaPrioridade.h"
#include "TADMoldura.h"
 
#define GRAV_INT     1
#define GRAV_EXT     2
#define LEITURA      3
#define IMPRESSAO    4
#define UT_GRAV_INT  5
#define UT_GRAV_EXT  8
#define UT_LEITURA   4
#define UT_IMPRESSAO 3
 
#define POS_LOG_Y    38
#define POS_LOG_MAX  6
 
struct TpProcessador
{
    int        id;
    int        ocupado;
    int        tempoRestante;
    int        totalTarefas;
    int        totalUt;
    TpElemento tarefaAtual;
};
 
int linhaLog = POS_LOG_Y;
 
void adicionaLog(int corTexto, char *msg)
{
    if(linhaLog >= POS_LOG_Y + POS_LOG_MAX)
    {
        limparArea(3, POS_LOG_Y, 74, POS_LOG_MAX);
        linhaLog = POS_LOG_Y;
    }
    gotoxy(3, linhaLog);
    cor(corTexto);
    printf("%-72s", msg);
    cor(7);
    linhaLog++;
}
 
void exibeFila(TpFila F)
{
    int  i;
    char tipos[][12]  = {"", "GravInt", "GravExt", "Leitura", "Impressao"};
    char prior[][12]  = {"", "[1]CRITICO", "[2]ALTO  ", "[3]MEDIO ", "[4]BAIXO "};
 
    desenhaMolduraFila();
 
    for(i = 0; i < 10; i++)
    {
        gotoxy(3, 10 + i);
        printf("|      |        |                |            |          |");
    }
 
    if(filaVazia(F.FIM))
    {
        gotoxy(5, 10);
        cor(8);
        printf("               (fila vazia)                        ");
        cor(7);
    }
    else
    {
        for(i = 0; i <= F.FIM && i < 10; i++)
        {
            gotoxy(3, 10 + i);
            cor(i == 0 ? 10 : 7);
            printf("| %3d  | %5d  | %-14s | %-10s | %3d ut   |",
                   i + 1,
                   F.FILA[i].id,
                   tipos[F.FILA[i].tipo],
                   prior[F.FILA[i].Prioridade],
                   F.FILA[i].tempoExec);
            cor(7);
        }
 
        if(F.FIM >= 10)
        {
            gotoxy(5, 19);
            cor(8);
            printf(" ... e mais %d tarefas aguardando ...", F.FIM - 9);
            cor(7);
        }
    }
}
 
void exibeProcessadores(TpProcessador proc[], int nProc)
{
    int  i;
    char tipos[][12] = {"", "GravInt   ", "GravExt   ", "Leitura   ", "Impressao "};
 
    desenhaMolduraProc(nProc);
 
    for(i = 0; i < nProc; i++)
    {
        gotoxy(3, 25 + i);
 
        if(proc[i].ocupado)
        {
            cor(10);
            printf("| P%-3d | OCUPADO  | %-16s |  %5d  |  %3d ut  | %3d ut | %4d   |",
                   proc[i].id,
                   tipos[proc[i].tarefaAtual.tipo],
                   proc[i].tarefaAtual.id,
                   proc[i].tempoRestante,
                   proc[i].tarefaAtual.tempoExec,
                   proc[i].totalTarefas);
        }
        else
        {
            cor(8);
            printf("| P%-3d |  LIVRE   | ---------------- |  -----  | -------- | ------ | %4d   |",
                   proc[i].id,
                   proc[i].totalTarefas);
        }
        cor(7);
    }
}
 
void insereProcessador(TpFila &F, TpProcessador proc[], int &nProc)
{
    int i;
 
    limparTela();
    desenhaHeader();
 
    cor(11);
    gotoxy(10, 7);
    printf("+----------------------------------------------------------+");
    gotoxy(10, 8);
    printf("|         CONFIGURACAO INICIAL DA SIMULACAO                |");
    gotoxy(10, 9);
    printf("+----------------------------------------------------------+");
    gotoxy(10, 10);
    printf("|                                                          |");
    gotoxy(10, 11);
    printf("|  Quantos processadores deseja utilizar?                  |");
    gotoxy(10, 12);
    printf("|  (minimo: 4  /  maximo: 10)                              |");
    gotoxy(10, 13);
    printf("|                                                          |");
    gotoxy(10, 14);
    printf("|  Digite: ");
    cor(7);
 
    do{
        gotoxy(20, 14);
        printf("   ");
        gotoxy(20, 14);
        scanf("%d", &nProc);
 
        gotoxy(10, 16);
        if(nProc < 4)
        {
            cor(12);
            printf("|  ERRO: numero inferior a 4! Tente novamente.            |");
            cor(11);
        }
        else if(nProc > 10)
        {
            cor(12);
            printf("|  ERRO: numero superior a 10! Tente novamente.           |");
            cor(11);
        }
        else
        {
            printf("|                                                          |");
        }
 
    }while(nProc < 4 || nProc > 10);
 
    gotoxy(10, 17);
    printf("+----------------------------------------------------------+");
    cor(7);
 
    for(i = 0; i < nProc; i++)
    {
        proc[i].id            = i + 1;
        proc[i].ocupado       = 0;
        proc[i].tempoRestante = 0;
        proc[i].totalTarefas  = 0;
        proc[i].totalUt       = 0;
    }
 
    Sleep(1000);
}
 
void alocarProcessador(TpFila &F, TpProcessador proc[], int nProc)
{
    int  i;
    char nomeTipo[20];
    char msg[100];
 
    for(i = 0; i < nProc; i++)
    {
        if(!proc[i].ocupado && !filaVazia(F.FIM))
        {
            proc[i].tarefaAtual   = retirar(F);
            proc[i].ocupado       = 1;
            proc[i].tempoRestante = proc[i].tarefaAtual.tempoExec;
            proc[i].totalTarefas++;
            proc[i].totalUt      += proc[i].tarefaAtual.tempoExec;
 
            if(proc[i].tarefaAtual.tipo == GRAV_INT)
                strcpy(nomeTipo, "GravInt");
            else if(proc[i].tarefaAtual.tipo == GRAV_EXT)
                strcpy(nomeTipo, "GravExt");
            else if(proc[i].tarefaAtual.tipo == LEITURA)
                strcpy(nomeTipo, "Leitura");
            else
                strcpy(nomeTipo, "Impressao");
 
            sprintf(msg, "[->] P%d recebeu Tarefa %d (%s) por %d ut",
                    proc[i].id,
                    proc[i].tarefaAtual.id,
                    nomeTipo,
                    proc[i].tarefaAtual.tempoExec);
            adicionaLog(10, msg);
            Sleep(300);
        }
    }
}
 
void relatorio(TpProcessador proc[], int nProc,
               int contTipo[], int tempoTipo[])
{
    int   i;
    float media;
    char  nomes[][12] = {"", "GravInt", "GravExt", "Leitura", "Impressao"};
 
    limparTela();
    desenhaHeader();
 
    gotoxy(5, 10);
    cor(11);
    printf(">> Por Processador:");
    cor(7);
 
    desenhaMolduraRelatorio(nProc);
 
    for(i = 0; i < nProc; i++)
    {
        media = 0;
        if(proc[i].totalTarefas > 0)
            media = (float)proc[i].totalUt / proc[i].totalTarefas;
 
        gotoxy(5, 14 + i);
        cor(proc[i].totalTarefas > 0 ? 10 : 8);
        printf("| P%-4d |       %4d       |    %6.2f ut    |",
               proc[i].id,
               proc[i].totalTarefas,
               media);
        cor(7);
    }
 
    gotoxy(5, 16 + nProc);
    cor(11);
    printf(">> Por Tipo de Tarefa:");
    cor(7);
 
    for(i = 1; i <= 4; i++)
    {
        media = 0;
        if(contTipo[i] > 0)
            media = (float)tempoTipo[i] / contTipo[i];
 
        gotoxy(5, 20 + nProc + (i-1));
        cor(contTipo[i] > 0 ? 10 : 8);
        printf("| %-9s |       %4d       |    %6.2f ut    |",
               nomes[i],
               contTipo[i],
               media);
        cor(7);
    }
 
    getch();
}
 
void simular()
{
    TpFila        F;
    TpProcessador proc[10];
    TpElemento    e;
    FILE         *Ptr;
    int           nProc, ut = 0, i;
    int           intervalo   = 4;
    int           contTipo[5]  = {0, 0, 0, 0, 0};
    int           tempoTipo[5] = {0, 0, 0, 0, 0};
    char          arq[] = "tarefas.txt";
    char          resp;
    char          msg[100];
 
    inicializar(F);
 
    Ptr = fopen(arq, "r");
    if(Ptr == NULL)
    {
        limparTela();
        cor(12);
        gotoxy(5, 5);
        printf("ERRO: Arquivo '%s' nao encontrado!", arq);
        cor(7);
        Sleep(2000);
        return;
    }
 
    insereProcessador(F, proc, nProc);
 
    limparTela();
    desenhaHeader();
    desenhaMolduraLog(POS_LOG_Y, POS_LOG_MAX);
    exibeFila(F);
    exibeProcessadores(proc, nProc);
 
    while(!feof(Ptr))
    {
        if(_kbhit())
        {
            if(_getch() == 27)
                break;
        }
 
        gotoxy(3, 5);
        cor(15);
        printf("+--------------------------------------------+");
        gotoxy(3, 6);
        printf("| UT: %4d  |  Intervalo: %2d ut  | ESC=sair |", ut, intervalo);
        gotoxy(3, 7);
        printf("+--------------------------------------------+");
        cor(7);
 
        Sleep(300);
 
        if(ut % intervalo == 0)
        {
            if(fscanf(Ptr, "%d;%d;%d",
                      &e.id, &e.tipo, &e.tempoExec) == 3)
            {
                e.Prioridade = e.tipo;
 
                if(!filaCheia(F.FIM))
                    inserir(F, e);
 
                sprintf(msg, "[+] UT=%d Tarefa %d (%s) inserida na fila",
                        ut, e.id,
                        e.tipo == GRAV_INT ? "GravInt" :
                        e.tipo == GRAV_EXT ? "GravExt" :
                        e.tipo == LEITURA  ? "Leitura" : "Impressao");
                adicionaLog(14, msg);
                Sleep(300);
            }
        }
 
        alocarProcessador(F, proc, nProc);
 
        exibeFila(F);
        exibeProcessadores(proc, nProc);
        Sleep(300);
 
        for(i = 0; i < nProc; i++)
        {
            if(proc[i].ocupado)
            {
                proc[i].tempoRestante--;
 
                if(proc[i].tempoRestante == 0)
                {
                    sprintf(msg, "[OK] P%d concluiu Tarefa %d (%s)!",
                            proc[i].id,
                            proc[i].tarefaAtual.id,
                            proc[i].tarefaAtual.tipo == GRAV_INT ? "GravInt" :
                            proc[i].tarefaAtual.tipo == GRAV_EXT ? "GravExt" :
                            proc[i].tarefaAtual.tipo == LEITURA  ? "Leitura" : "Impressao");
                    adicionaLog(12, msg);
                    Sleep(300);
 
                    contTipo [proc[i].tarefaAtual.tipo]++;
                    tempoTipo[proc[i].tarefaAtual.tipo] +=
                        proc[i].tarefaAtual.tempoExec;
 
                    proc[i].ocupado = 0;
                }
            }
        }
 
        exibeProcessadores(proc, nProc);
 
        if(ut % intervalo == 0)
        {
            gotoxy(50, 6);
            cor(11);
            printf("Alterar intervalo? (S/N): ");
            cor(7);
            fflush(stdin);
            scanf("%c", &resp);
 
            gotoxy(50, 6);
            printf("                          ");
 
            if(resp == 'S' || resp == 's')
            {
                gotoxy(50, 6);
                cor(11);
                printf("Novo intervalo: ");
                cor(7);
                scanf("%d", &intervalo);
                fflush(stdin);
 
                gotoxy(50, 6);
                printf("                ");
 
                sprintf(msg, "[*] Intervalo alterado para %d ut", intervalo);
                adicionaLog(13, msg);
            }
        }
 
        ut++;
        Sleep(300);
    }
 
    fclose(Ptr);
    relatorio(proc, nProc, contTipo, tempoTipo);
}
 
int main()
{
    simular();
    return 0;
}
