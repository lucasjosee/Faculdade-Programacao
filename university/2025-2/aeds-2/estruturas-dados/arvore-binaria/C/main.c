#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
	struct No* dir;
	struct No* esq;
	int elemento;
}No;

typedef struct Arvore
{
	struct No* root;
}Arvore;

No* newNo(int x);
Arvore* newArvore();
void inserir(int x, Arvore* arvore);
No* inserirRec(int x, No* root);
void  caminhamento(No* root);

No* newNo(int x)
{
	No* temp = (No*) malloc(sizeof(No));
	temp->dir = NULL;
	temp->esq = NULL;
	temp->elemento = x;
	return temp;
}

Arvore* newArvore()
{
	Arvore* temp = (Arvore*) malloc(sizeof(Arvore));
	temp->root = NULL;
	return temp;
}

void inserir(int x, Arvore* arvore)
{
	arvore->root = inserirRec(x, arvore->root);
}

No* inserirRec(int x, No* root)
{
	if(root == NULL)
	{
		root = newNo(x);
	}
	
	if(x < root->elemento)
	{
		root->esq = inserirRec(x, root->esq);
	}
	if(x > root->elemento)
	{
		root->dir = inserirRec(x, root->dir);
	}
	
	return root;
}

void  caminhamento(No* root)
{
	if(root != NULL)
	{
		printf("%d ", root->elemento);
		caminhamento(root->esq);
		caminhamento(root->dir);
	}
}

int main()
{
	Arvore* a1 = newArvore();
	inserir(4, a1);
	inserir(3, a1);
	inserir(5, a1);
	inserir(2, a1);
	inserir(1, a1);
	inserir(6, a1);
	
	caminhamento(a1->root);
	
}










