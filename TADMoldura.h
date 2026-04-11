#ifndef TADMOLDURA_H
#define TADMOLDURA_H
 
#include <stdio.h>
#include <windows.h>
 
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
 
void cor(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
 
void limparTela()
{
    system("cls");
}
 
void limparArea(int x, int y, int largura, int altura)
{
    int i, j;
    for(i = 0; i < altura; i++)
    {
        gotoxy(x, y + i);
        for(j = 0; j < largura; j++)
            printf(" ");
    }
}
 
void desenhaHeader()
{
    int i;
    cor(11);
    gotoxy(1, 1);
    printf("+");
    for(i = 0; i < 76; i++) printf("=");
    printf("+");
    gotoxy(1, 2);
    printf("|");
    cor(15);
    printf("%*s%s%*s", 10, "", "SIMULADOR DE FILAS DE PROCESSADORES", 31, "");
    cor(11);
    printf("|");
    gotoxy(1, 3);
    printf("|");
    cor(14);
    printf("%*s%s%*s", 18, "", "ED I  -  FIPP / UNOESTE  -  2026", 26, "");
    cor(11);
    printf("|");
    gotoxy(1, 4);
    printf("+");
    for(i = 0; i < 76; i++) printf("=");
    printf("+");
    cor(7);
}
 
void desenhaMolduraFila()
{
    int i;
    cor(14);
    gotoxy(3, 7);
    printf("+------+------ FILA DE TAREFAS ------+-----------+----------+");
    gotoxy(3, 8);
    printf("| Pos  |   ID   |      Tipo      | Prioridade | Tempo(ut)|");
    gotoxy(3, 9);
    printf("+------+--------+----------------+------------+----------+");
    for(i = 0; i < 10; i++)
    {
        gotoxy(3, 10 + i);
        printf("|      |        |                |            |          |");
    }
    gotoxy(3, 20);
    printf("+------+--------+----------------+------------+----------+");
    cor(7);
}
 
void desenhaMolduraProc(int nProc)
{
    int i;
    cor(13);
    gotoxy(3, 22);
    printf("+------+----------+------ PROCESSADORES ------+----------+--------+--------+");
    gotoxy(3, 23);
    printf("| Proc |  Estado  |      Tarefa      |  ID T.  | T.Rest.  | T.Exec | Total  |");
    gotoxy(3, 24);
    printf("+------+----------+------------------+---------+----------+--------+--------+");
    for(i = 0; i < nProc; i++)
    {
        gotoxy(3, 25 + i);
        printf("|      |          |                  |         |          |        |        |");
    }
    gotoxy(3, 25 + nProc);
    printf("+------+----------+------------------+---------+----------+--------+--------+");
    cor(7);
}
 
void desenhaMolduraLog(int posLogY, int posLogMax)
{
    cor(9);
    gotoxy(3, posLogY - 1);
    printf("+----------------------- LOG DE EVENTOS --------------------------------+");
    gotoxy(3, posLogY + posLogMax);
    printf("+------------------------------------------------------------------------+");
    cor(7);
}
 
void desenhaMolduraRelatorio(int nProc)
{
    int i;
    cor(14);
    gotoxy(5, 6);
    printf("+====================================================================+");
    gotoxy(5, 7);
    printf("|                      RELATORIO FINAL                              |");
    gotoxy(5, 8);
    printf("+====================================================================+");
    gotoxy(5, 11);
    printf("+-------+------------------+------------------+");
    gotoxy(5, 12);
    printf("| Proc  |  Total Tarefas   |   Tempo Medio    |");
    gotoxy(5, 13);
    printf("+-------+------------------+------------------+");
    for(i = 0; i < nProc; i++)
    {
        gotoxy(5, 14 + i);
        printf("|       |                  |                  |");
    }
    gotoxy(5, 14 + nProc);
    printf("+-------+------------------+------------------+");
    gotoxy(5, 17 + nProc);
    printf("+-----------+------------------+------------------+");
    gotoxy(5, 18 + nProc);
    printf("| Tipo      |  Total Execucoes |   Tempo Medio    |");
    gotoxy(5, 19 + nProc);
    printf("+-----------+------------------+------------------+");
    for(i = 1; i <= 4; i++)
    {
        gotoxy(5, 20 + nProc + (i-1));
        printf("|           |                  |                  |");
    }
    gotoxy(5, 24 + nProc);
    printf("+-----------+------------------+------------------+");
    gotoxy(5, 26 + nProc);
    printf("+====================================================================+");
    gotoxy(5, 27 + nProc);
    printf("|              Pressione qualquer tecla para sair...                |");
    gotoxy(5, 28 + nProc);
    printf("+====================================================================+");
    cor(7);
}
 
#endif
