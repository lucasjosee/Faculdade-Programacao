#include <stio.h>
#include <stdlib.h>



typedef struct No
{
	int num;
	Lista* nomes;
}No;

typedef struct Arvore
{
	No* raiz;
}ArvoreInterna;

typedef struct Celula;
{
	struct No* prox;
	char nome[];
}Celula;

typedef struct Lista
{
	Celula* primeiro;
	Celula* ultimo;
}Lista;

No* newCelula(char nome[], 
