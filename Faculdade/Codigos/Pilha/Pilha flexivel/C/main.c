#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
	struct No* prox;
	int elemento;
}No;

typedef struct Pilha
{
	No* topo;
}Pilha;

No* newNo(int x);
Pilha* newPilha();
void inserirPilha(int x, Pilha* p);
void mostrar(No* topo);
int somar(No* topo);
int maior(No* topo);
int maiorRec(No* topo);

No* newNo(int x)
{
	No* temp = (No*) malloc(sizeof(No));
	temp->elemento = x;
	temp->prox = NULL;
	return temp;
}

Pilha* newPilha()
{
	Pilha* temp = (Pilha*) malloc(sizeof(Pilha));
	temp->topo = NULL;
	return temp;
}

void inserirPilha(int x, Pilha* p)
{
    No* novo = newNo(x);
    novo->prox = p->topo;
    p->topo = novo;
}

void mostrar(No* topo)
{
	if(topo != NULL)
	{
		printf("%d ", topo->elemento);
		mostrar(topo->prox);	
	}
}

int somar(No* topo)
{
	int resp = 0;
	
	if(topo != NULL)
	{
		resp += topo->elemento + somar(topo->prox);
	}
	return resp;
}

int maior(No* topo)
{
	int maior = topo->elemento;
	for(No* i = topo->prox; i != NULL; i = i->prox)
	{
		if(maior < i->elemento)
		{
			maior = i->elemento;
		}
	}
	return maior;
}

int maiorRec(No* topo)
{
	if(topo == NULL)
	{
		return -1;
	}
	
	int maior = maiorRec(topo->prox);
	
	if(topo->elemento > maior)
	{
		return topo->elemento;
	}
	else
	{
		return maior;
	}			
}

int main()
{
	Pilha* p = newPilha();
	
	inserirPilha(1000, p);
	inserirPilha(10, p);
	inserirPilha(7, p);
	inserirPilha(100, p);
	mostrar(p->topo);
	printf("%d ", somar(p->topo));
	printf("%d", maiorRec(p->topo
	));
	
}










