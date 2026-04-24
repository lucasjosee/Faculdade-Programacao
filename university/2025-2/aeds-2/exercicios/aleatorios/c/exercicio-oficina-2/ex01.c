#include <stdio.h>

# define MAX_EMERGENCIA 5
# define MAX_PERIODICA 6
# define MAX_BACKGROUND 30

typedef struct  
{
    int id;
    int prioridade;
}Tarefa;

typedef struct 
{
    Tarefa pilha[MAX_EMERGENCIA];
    int n;
}PilhaEmergencia;

typedef struct 
{
    Tarefa fila[MAX_PERIODICA];
    int primeiro;
    int ultimo;
}FilaPeriodica;

typedef struct
{
    Tarefa lista[MAX_BACKGROUND];
    int n;
}ListaBackground;

int main()
{
    PilhaEmergencia p;
    p.n = - 1;

    FilaPeriodica f;
    f.primeiro = f.ultimo = 0;

    ListaBackground l;
    l.n = -1;




}

//Fila Circular
void enfileirarPeriodica(Tarefa t, FilaPeriodica f)
{
    if(((f.ultimo + 1) % MAX_PERIODICA) == f.primeiro)
    {
        printf("Lista periodica Cheia!!!\n");
        exit(1);
    }

    f.fila[f.ultimo] = t;
    f.ultimo = (f.ultimo + 1) % MAX_PERIODICA;
}

Tarefa desinfileirasPeriodica(FilaPeriodica f)
{
    if(f.ultimo == f.primeiro)
    {
        printf("Lista vazia!!!\n");
        exit(1);
    }
    
    Tarefa resp = f.lista[f.primeiro];
    f.primeiro = (f.primeiro + 1) % MAX_PERIODICA;
    return resp;
}
//


}




