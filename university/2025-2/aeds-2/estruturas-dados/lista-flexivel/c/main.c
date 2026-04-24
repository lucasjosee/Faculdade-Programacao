#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
	struct No* prox;
	int valor;
}No;

No* novoNo(int valor)
{
	No* temp = (No*) malloc(sizeof(No));
	temp->valor = valor;
	temp->prox = NULL;
	return temp;
}

typedef struct Lista
{
	No* primeiro;
	No* ultimo;
}Lista;

Lista* criarLista()
{
	Lista* temp = (Lista*) malloc(sizeof(Lista));
	No* noCabeca = (No*) malloc(sizeof(No));
	noCabeca->prox = NULL;
	temp->primeiro = noCabeca;
	temp->ultimo = noCabeca;
	return temp;
}

void inserirLista(Lista* lista, int valor)
{
	No* temp = novoNo(valor);
	
	lista->ultimo->prox = temp;
	lista->ultimo = temp;
	temp = NULL;
}
