#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TADFilaPrioridade.h" 

#define GRAV_INT     1
#define GRAV_EXT     2
#define LEITURA      3
#define IMPRESSAO    4

#define UT_GRAV_INT  5
#define UT_GRAV_EXT  8
#define UT_LEITURA   4
#define UT_IMPRESSAO 3

struct TpProcessador
{
    int        id;
    int        ocupado;
    int        tempoRestante;
    int        totalTarefas;
    int        totalUt;
    TpElemento tarefaAtual;  
};

int LerArquivo(TpFila &F,char *nomeArquivo)
{
	TpElemento e;
	FILE *Ptr = fopen(nomeArquivo,"r");
	
	if(Ptr == NULL)
		return 0;
		
	while(fscanf(Ptr,"%d;%d;%d", &e.id,&e.tipo,&e.tempoExec)==3){
		e.Prioridade=e.tipo;
		
		if(!filaCheia(F.FIM))
			inserir(F,e);
	}
	fclose(Ptr);
	return 1;
}

void insereProcessador(TpFila &F,TpProcessador proc[], int &nProc)
{
	int i;
	
	do{
		printf("Quantos Processadores irá utilizar?(minimo 4, máximo 10) ");
		scanf("%d",&nProc);
		
		if(nProc<4)
			printf("Número Inferior a 4, Tente Novamente!");
		
		if(nProc>10)
			printf("Número Superior a 10, Tente Novamente!");
	}while(nProc<4 || nProc>10);
	
	for(i=0;i<nProc;i++)
	{
		proc[i].id = i+1;
		proc[i].ocupado =0;
		proc[i].tempoRestante=0;
		proc[i].totalTarefas=0;
		proc[i].totalUt=0;
	}
}

void alocarProcessador(TpFila &F,TpProcessador proc[], int nProc)
{
	int i;
	
	for(i=0;i<nProc;i++)
	{
		if(!proc[i].ocupado && !filaVazia(F.FIM))
		{
			proc[i].tarefaAtual = retirar(F);
			proc[i].ocupado = 1;
			proc[i].tempoRestante = proc[i].tarefaAtual.tempoExec;
			proc[i].totalTarefas++;
			proc[i].totalUt+=proc[i].tarefaAtual.tempoExec;
		}
	}
}

void simular()
{
	TpFila F;
	TpProcessador proc[10];
	int nProc,ut=0,i;
	char arq[] = "Tarefa.txt";
	
	inicializar(F);
	
	if(LerArquivo(F,arq) == 1)
	{
		insereProcessador(F,proc,nProc);
		
		while(!filaVazia(F.FIM))
		{
			if(ut % 4 == 0)
				alocaProcessador(F,proc,nProc);
			
			for(i=0;i<nProc;i++)
			{
				if(proc[i].ocupado)
				{
					proc[i].tempoRestante--;
					
					if(proc[i].tempoRestante == 0)
						proc[i].ocupado = 0;
				}
			}
			
			ut++;
		}
	}
}
